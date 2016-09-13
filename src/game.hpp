#ifndef GAME_HPP
#define GAME_HPP

#include <point.hpp>

#include <utils/boosttree.hpp>

#include <string>
#include <queue>

class Game
{
public:
    class Move
    {
    public:
        Move();
        Move(const Point& position, QGo::Case color);

        const Point& position() const;
        QGo::Case color() const;

    private:
        bool m_pass;
        Point m_position;
        QGo::Case m_color;
    };

    struct Player
    {
        std::string m_name;
        std::string m_rank;
    };

    typedef utils::BoostTree<Move> type_tree;

    Game();

    //getters
    const std::string& blackName() const;
    const std::string& blackRank() const;
    const std::string& whiteName() const;
    const std::string& whiteRank() const;

    //setters
    void setBlackName(const std::string& bn);
    void setBlackRank(const std::string& br);
    void setWhiteName(const std::string& wn);
    void setWhiteRank(const std::string& wr);

    //moves related methods:
    void addMove(const Point& position, QGo::Case color);

    //utility methods
    std::string report() const;

    void loadMovesOnto(QGo::goban_wp goban) const;

    bool hasAlternativeMoves() const;

    void startAlternativePath();

    void endAlternativePath();

    const type_tree& tree() const;

    double m_komi;
    uint8_t m_nbHandicapStones;
    std::string m_name;
    std::string m_overtimeSystem;
    std::string m_copyright;
    std::string m_eventName;
    uint8_t m_boardSize;
    std::string m_ruleSet;
    std::string m_gamePlace;
    std::string m_date;
    std::string m_information;
    std::string m_application;
    std::string m_user;

private:
    Player m_black;
    Player m_white;

    type_tree m_gameTree;
    type_tree::vertex_descriptor m_currentNodeInGameTree;
    std::queue<type_tree::vertex_descriptor> m_parentNodesOfAlternativePath;
};

#endif // GAME_HPP
