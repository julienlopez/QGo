#ifndef SGFREADER_HPP
#define SGFREADER_HPP

#include <list>
#include <string>
#include <map>
#include <functional>
#include <stdexcept>

class Game;
class Point;

class SGFReader
{
public:
    /**
    * \brief parse a .sgf file given in the form of a list of lines.
    * \throws InvalidLine if a line has an unreckognized form.
    *
    * each line can consist of several instructions;
    */
    static Game parse(const std::list<std::string>& lst);

    struct InvalidLine : public std::invalid_argument
    {
        InvalidLine(const std::string& line);
    };

    struct UnreckognizedCommand : public std::invalid_argument
    {
        UnreckognizedCommand(const std::string& line);
    };

private:
    class Dispatch
    {
    public:
        typedef std::map<std::string, std::function<void(Game&, std::string)>> type_map;

        Dispatch();
        const type_map& map() const;

    private:
        type_map s_map;
    };

    /**
    * \brief parse a single line (which may consist of several instructions).
    * \throws InvalidLine if a line has an unreckognized form.
    */
    static void parseLine(Game& game, std::string line);

    //command specific methods
    /**
    *
    */
    static void parseGC(Game& game, std::string line);

    /**
    * \brief GN: defines game name
    */
    static void parseGN(Game& game, std::string line);

    /**
    * \brief HA: defines the number of handicap stones
    */
    static void parseHA(Game& game, std::string line);

    /**
    * \brief KM: defines the komi
    */
    static void parseKM(Game& game, std::string line);

    /**
    * \brief TB: defines black territory or area
    *
    * Depends on the rule set used
    */
    static void parseTB(Game& game, std::string line);

    /**
    * \brief TW: defines white territory or area
    *
    * Depends on the rule set used
    */
    static void parseTW(Game& game, std::string line);

    /**
    * \brief DT: defines the date of the game
    */
    static void parseDT(Game& game, std::string line);

    /**
    * \brief PB: defines the name of the black player
    */
    static void parsePB(Game& game, std::string line);

    /**
    * \brief PW: defines the name of the white player
    */
    static void parsePW(Game& game, std::string line);

    /**
    * \brief PB: defines the rank of the black player
    */
    static void parseBR(Game& game, std::string line);

    /**
    * \brief PW: defines the rank of the white player
    */
    static void parseWR(Game& game, std::string line);

    /**
    * \brief OT: defines the overtime system
    */
    static void parseOT(Game& game, std::string line);

    /**
    * \brief CR: defines the copyright
    */
    static void parseCP(Game& game, std::string line);

    /**
    * \brief EV: defines the name of the event
    */
    static void parseEV(Game& game, std::string line);

    /**
    * \brief SZ: defines the size of the board
    */
    static void parseSZ(Game& game, std::string line);

    /**
    * \brief RU: defines the size of the board
    */
    static void parseRU(Game& game, std::string line);

    /**
    * \brief FF: defines the file format
    */
    static void parseFF(Game& game, std::string line);

    /**
    * \brief GM: defines the type of game (1 fo go)
    */
    static void parseGM(Game& game, std::string line);

    /**
    * \brief PC: defines the place where the game was played
    */
    static void parsePC(Game& game, std::string line);

    /**
    * \brief B: defines a black move
    */
    static void parseB(Game& game, std::string line);

    /**
    * \brief W: defines a white move
    */
    static void parseW(Game& game, std::string line);

    /**
    * \brief AP: defines the application used to create this sgf file
    */
    static void parseAP(Game& game, std::string line);

    //helper functions

    static uint8_t parseUInt8(const std::string& line);

    static double parseDouble(const std::string& line);

    static Point parsePoint(const std::string& line) throw(InvalidLine);

    static uint8_t parsePosition(char c) throw(InvalidLine);

    const static Dispatch s_dispatch;
};

#endif // SGFREADER_HPP
