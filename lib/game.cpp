#include "game.hpp"
#include "goban.hpp"

#include <sstream>
#include <cassert>

Game::Move::Move(): m_pass(true), m_position(0, 0)
{}

Game::Move::Move(const Point& p, QGo::Case c): m_pass(false), m_position(p), m_color(c)
{}

const Point& Game::Move::position() const
{
    return m_position;
}

QGo::Case Game::Move::color() const
{
    return m_color;
}

Game::Game()
{}

const std::string& Game::blackName() const
{
    return m_black.m_name;
}

const std::string& Game::blackRank() const
{
    return m_black.m_rank;
}

const std::string& Game::whiteName() const
{
    return m_white.m_name;
}

const std::string& Game::whiteRank() const
{
    return m_white.m_rank;
}

void Game::setBlackName(const std::string& bn)
{
    m_black.m_name = bn;
}

void Game::setBlackRank(const std::string& br)
{
    m_black.m_rank = br;
}

void Game::setWhiteName(const std::string& wn)
{
    m_white.m_name = wn;
}

void Game::setWhiteRank(const std::string& wr)
{
    m_white.m_rank = wr;
}

void Game::addMove(const Point& position, QGo::Case color)
{
    if(m_gameTree.roots().empty())
    {
        m_currentNodeInGameTree = m_gameTree.addNode(Move(position, color));
        return;
    }
    m_currentNodeInGameTree = m_gameTree.addNode(Move(position, color), m_currentNodeInGameTree);
}

std::string Game::report() const
{
    std::ostringstream oss;

    oss << "Game Name: " << m_name << "\n";
    oss << "Komi: " << m_komi << "\n";
    oss << "Handicap stones: " << (unsigned int)m_nbHandicapStones << "\n";
    oss << "Black: \n" << "\tname: " << m_black.m_name << "\n\trank: " << m_black.m_rank << "\n";
    oss << "White: \n" << "\tname: " << m_white.m_name << "\n\trank: " << m_white.m_rank << "\n";
    oss << "Overtime System: " << m_overtimeSystem << "\n";
    oss << "Copyright System: " << m_copyright << "\n";
    oss << "Event Name: " << m_eventName << "\n";
    oss << "Board Size: " << (unsigned int)m_boardSize << "\n";
    oss << "Rule Set: " << m_ruleSet << "\n";
    oss << "Game Place: " << m_gamePlace << "\n";

    return oss.str();
}

void Game::loadMovesOnto(QGo::goban_wp g) const
{
    QGo::goban_sp goban = g.lock();
    assert(goban);

    goban->clear();

    if(goban->size() != m_boardSize)
        goban->resize(m_boardSize);

    if(m_gameTree.roots().empty())
        return;

    assert(!hasAlternativeMoves()); //alternative moves not handled for now
    type_tree::list_vertex_descriptor children = m_gameTree.roots();
    while(!children.empty())
    {
        assert(children.size() == 1);
        const Move& m = m_gameTree(children.front());
        goban->placeStone(m.position().x(), m.position().y(), m.color());
        children = m_gameTree.children(children.front());
    }
}

bool Game::hasAlternativeMoves() const
{
    const type_tree::list_vertex_descriptor& roots = m_gameTree.roots();
    if(roots.empty()) return false;
    if(roots.size() > 1) return true;
    type_tree::list_vertex_descriptor children = m_gameTree.children(m_gameTree.roots().front());
    while(!children.empty())
    {
        if(children.size() > 1) return true;
        children = m_gameTree.children(children.front());
    }
    return false;
}

void Game::startAlternativePath()
{
    m_parentNodesOfAlternativePath.push(m_currentNodeInGameTree);
}

void Game::endAlternativePath()
{
    assert(!m_parentNodesOfAlternativePath.empty());
    m_currentNodeInGameTree = m_parentNodesOfAlternativePath.front();
    m_parentNodesOfAlternativePath.pop();
}

const Game::type_tree& Game::tree() const
{
    return m_gameTree;
}
