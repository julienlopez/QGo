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

    class Player
    {
    public:
        const std::string& name() const;
        const std::string& rank() const;

        void setName(const std::string& n);
        void setRank(const std::string& r);

    private:
        std::string m_name;
        std::string m_rank;
    };

    typedef utils::BoostTree<Move> type_tree;

    Game();

    //getters
    double komi() const;
    uint8_t nbHandicapStones() const;
    const std::string& name() const;

    const std::string& blackName() const;
    const std::string& blackRank() const;
    const std::string& whiteName() const;
    const std::string& whiteRank() const;

    const std::string& overtimeSystem() const;
    const std::string& copyright() const;
    const std::string& eventName() const;

    uint8_t boardSize() const;

    const std::string& ruleSet() const;
    const std::string& gamePlace() const;

    const std::string& date() const;
    const std::string& information() const;

    const std::string& application() const;

    //setters
    void setKomi(double k);
    void setNbHandicapStones(uint8_t n);
    void setName(const std::string& name);

    void setBlackName(const std::string& bn);
    void setBlackRank(const std::string& br);
    void setWhiteName(const std::string& wn);
    void setWhiteRank(const std::string& wr);

    void setOvertimeSystem(const std::string& ots);
    void setCopyright(const std::string& cr);
    void setEventName(const std::string& en);

    void setBoardSize(uint8_t size);

    void setRuleSet(const std::string& rs);
    void setGamePlace(const std::string& gp);

    void setDate(const std::string& date);
    void setInformation(const std::string& information);

    void setApplication(const std::string& application);

    //moves related methods:
    void addMove(const Point& position, QGo::Case color);

    //utility methods
    std::string report() const;

    void loadMovesOnto(QGo::goban_wp goban) const;

    bool hasAlternativeMoves() const;

    void startAlternativePath();

    void endAlternativePath();

    const type_tree& tree() const;

private:
    double m_komi;
    uint8_t m_nbHandicapStones;
    std::string m_name;
    Player m_black;
    Player m_white;
    std::string m_overtimeSystem;
    std::string m_copyright;
    std::string m_eventName;
    uint8_t m_boardSize;
    std::string m_ruleSet;
    std::string m_gamePlace;
    std::string m_date;
    std::string m_information;
    std::string m_application;

    type_tree m_gameTree;
    type_tree::vertex_descriptor m_currentNodeInGameTree;
    std::queue<type_tree::vertex_descriptor> m_parentNodesOfAlternativePath;
};

#endif // GAME_HPP
