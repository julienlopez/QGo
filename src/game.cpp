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

const std::string& Game::Player::name() const
{
    return m_name;
}

const std::string& Game::Player::rank() const
{
    return m_rank;
}

void Game::Player::setName(const std::string& n)
{
    m_name = n;
}

void Game::Player::setRank(const std::string& r)
{
    m_rank = r;
}

Game::Game()
{}

double Game::komi() const
{
    return m_komi;
}

uint8_t Game::nbHandicapStones() const
{
    return m_nbHandicapStones;
}

const std::string& Game::name() const
{
    return m_name;
}
const std::string& Game::blackName() const
{
    return m_black.name();
}

const std::string& Game::blackRank() const
{
    return m_black.rank();
}

const std::string& Game::whiteName() const
{
    return m_white.name();
}

const std::string& Game::whiteRank() const
{
    return m_white.rank();
}

const std::string& Game::overtimeSystem() const
{
    return m_overtimeSystem;
}

const std::string& Game::copyright() const
{
    return m_copyright;
}

const std::string& Game::eventName() const
{
    return m_eventName;
}

uint8_t Game::boardSize() const
{
    return m_boardSize;
}

const std::string& Game::ruleSet() const
{
    return m_ruleSet;
}

const std::string& Game::gamePlace() const
{
    return m_gamePlace;
}

const std::string& Game::date() const
{
    return m_date;
}

const std::string& Game::information() const
{
    return m_information;
}

const std::string& Game::application() const
{
    return m_application;
}

void Game::setKomi(double k)
{
    m_komi = k;
}

void Game::setNbHandicapStones(uint8_t n)
{
    m_nbHandicapStones = n;
}

void Game::setName(const std::string& n)
{
    m_name = n;
}

void Game::setBlackName(const std::string& bn)
{
    m_black.setName(bn);
}

void Game::setBlackRank(const std::string& br)
{
    m_black.setRank(br);
}

void Game::setWhiteName(const std::string& wn)
{
    m_white.setName(wn);
}

void Game::setWhiteRank(const std::string& wr)
{
    m_white.setRank(wr);
}

void Game::setOvertimeSystem(const std::string& ots)
{
    m_overtimeSystem = ots;
}

void Game::setCopyright(const std::string& cr)
{
    m_copyright = cr;
}

void Game::setEventName(const std::string& en)
{
    m_eventName = en;
}

void Game::setBoardSize(uint8_t n)
{
    m_boardSize = n;
}

void Game::setRuleSet(const std::string& rs)
{
    m_ruleSet = rs;
}

void Game::setGamePlace(const std::string& gp)
{
    m_gamePlace = gp;
}

void Game::setDate(const std::string& d)
{
    m_date = d;
}

void Game::setInformation(const std::string& info)
{
    m_information = info;
}

void Game::setApplication(const std::string& app)
{
    m_application = app;
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
    oss << "Black: \n" << "\tname: " << m_black.name() << "\n\trank: " << m_black.rank() << "\n";
    oss << "White: \n" << "\tname: " << m_white.name() << "\n\trank: " << m_white.rank() << "\n";
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
