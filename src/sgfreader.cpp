#include "sgfreader.hpp"
#include "game.hpp"
#include "point.hpp"

#include <sstream>

#include <QDebug>

QDebug operator<<(QDebug dbg, const std::string& str)
 {
     dbg.nospace() << QString::fromStdString(str);
     return dbg.space();
 }

const SGFReader::Dispatch SGFReader::s_dispatch;

SGFReader::Dispatch::Dispatch()
{
    s_map.insert(make_pair("GC", &SGFReader::parseGC));
    s_map.insert(make_pair("GN", &SGFReader::parseGN));
    s_map.insert(make_pair("HA", &SGFReader::parseHA));
    s_map.insert(make_pair("KM", &SGFReader::parseKM));
    s_map.insert(make_pair("TB", &SGFReader::parseTB));
    s_map.insert(make_pair("TW", &SGFReader::parseTW));
    s_map.insert(make_pair("DT", &SGFReader::parseDT));
    s_map.insert(make_pair("PB", &SGFReader::parsePB));
    s_map.insert(make_pair("PW", &SGFReader::parsePW));
    s_map.insert(make_pair("BR", &SGFReader::parseBR));
    s_map.insert(make_pair("WR", &SGFReader::parseWR));
    s_map.insert(make_pair("OT", &SGFReader::parseOT));
    s_map.insert(make_pair("CP", &SGFReader::parseCP));
    s_map.insert(make_pair("EV", &SGFReader::parseEV));
    s_map.insert(make_pair("SZ", &SGFReader::parseSZ));
    s_map.insert(make_pair("RU", &SGFReader::parseRU));
    s_map.insert(make_pair("FF", &SGFReader::parseFF));
    s_map.insert(make_pair("GM", &SGFReader::parseGM));
    s_map.insert(make_pair("PC", &SGFReader::parsePC));
    s_map.insert(make_pair(";B", &SGFReader::parseB));
    s_map.insert(make_pair(";W", &SGFReader::parseW));
//    s_map.insert(make_pair("B", &SGFReader::parseB));
//    s_map.insert(make_pair("W", &SGFReader::parseW));
}

const SGFReader::Dispatch::type_map& SGFReader::Dispatch::map() const
{
    return s_map;
}

SGFReader::InvalidLine::InvalidLine(const std::string& line): std::invalid_argument("Invalid line: "+line)
{}

SGFReader::UnreckognizedCommand::UnreckognizedCommand(const std::string& line): std::invalid_argument("Unreckognized command: "+line)
{}

Game SGFReader::parse(const std::list<std::string>& lst)
{
    Game res;
    std::for_each(lst.begin(), lst.end(), [&](const std::string& line)
        {
            SGFReader::parseLine(res, line);
        });
    return res;
}

void SGFReader::parseLine(Game& game, std::string line)
{
    while(!line.empty() && isspace(*line.begin())) line.erase(0, 1);
    if(line.empty()) return;

    for(Dispatch::type_map::const_iterator i = s_dispatch.map().begin(); i != s_dispatch.map().end(); ++i)
    {
        if(!startsWith(line, i->first)) continue;
        line.erase(0, i->first.size());

        if(line.size() < 3 || *line.begin() != '[' || *(--line.end()) != ']')
            throw InvalidLine(line);
        line.erase(0, 1);
        line.pop_back();
        std::size_t pos_bracket = line.find(']');
        if(pos_bracket != std::string::npos) //several instructions on a single line!!
        {
            std::string leftOver = line.substr(pos_bracket + 1) + ']';
            line = line.substr(0, pos_bracket);
            parseLine(game, leftOver);
        }
        i->second(game, line);
        return;

    }
    throw UnreckognizedCommand(line);
}

void SGFReader::parseGC(Game& game, std::string line)
{
    game.setInformation(line);
}

void SGFReader::parseGN(Game& game, std::string line)
{
    game.setName(line);
}

void SGFReader::parseHA(Game& game, std::string line)
{
    game.setNbHandicapStones(parseUInt8(line));
}

void SGFReader::parseKM(Game& game, std::string line)
{
    game.setKomi(parseDouble(line));
}

void SGFReader::parseTB(Game& game, std::string line)
{
    qDebug() << "TB => " << line;
}

void SGFReader::parseTW(Game& game, std::string line)
{
    qDebug() << "TW => " << line;
}

void SGFReader::parseDT(Game& game, std::string line)
{
    game.setDate(line);
}

void SGFReader::parsePB(Game& game, std::string line)
{
    game.setBlackName(line);
}

void SGFReader::parsePW(Game& game, std::string line)
{
    game.setWhiteName(line);
}

void SGFReader::parseBR(Game& game, std::string line)
{
    game.setBlackRank(line);
}

void SGFReader::parseWR(Game& game, std::string line)
{
    game.setWhiteRank(line);
}

void SGFReader::parseOT(Game& game, std::string line)
{
    game.setOvertimeSystem(line);
}

void SGFReader::parseCP(Game& game, std::string line)
{
    game.setCopyright(line);
}

void SGFReader::parseEV(Game& game, std::string line)
{
    game.setEventName(line);
}

void SGFReader::parseSZ(Game& game, std::string line)
{
    game.setBoardSize(parseUInt8(line));
}

void SGFReader::parseRU(Game& game, std::string line)
{
    game.setRuleSet(line);
}

void SGFReader::parseFF(Game& /*game*/, std::string line)
{
    if(line != "4") throw InvalidLine("SGF" + line + " not supported");
}

void SGFReader::parseGM(Game& /*game*/, std::string line)
{
    if(line != "1") throw InvalidLine("Impossible to parsing anything other than a game of go.");
}

void SGFReader::parsePC(Game& game, std::string line)
{
    game.setGamePlace(line);
}

void SGFReader::parseB(Game& game, std::string line)
{
    Point p = parsePoint(line);
    game.addMove(p, Goban::BLACK);
}

void SGFReader::parseW(Game& game, std::string line)
{
    Point p = parsePoint(line);
    game.addMove(p, Goban::WHITE);
}

bool SGFReader::startsWith(const std::string& str, const std::string& begin)
{
    if(str.size() < begin.size()) return false;
    for(size_t i = 0; i < begin.size(); i++)
        if(str[i] != begin[i]) return false;
    return true;
}

uint8_t SGFReader::parseUInt8(const std::string& line)
{
    std::istringstream iss(line);
    unsigned int n;
    iss >> n;
    return (uint8_t)n;
}

double SGFReader::parseDouble(const std::string& line)
{
    std::istringstream iss(line);
    double d;
    iss >> d;
    return d;
}

Point SGFReader::parsePoint(const std::string& line) throw(InvalidLine)
{
    if(line.size() != 2) throw InvalidLine(line + " isn't a valid position for a move");
    return Point(parsePosition(line.front()), parsePosition(line.back()));
}

uint8_t SGFReader::parsePosition(char c) throw(InvalidLine)
{
    if(c >= 'a' && c < 'z')
    {
        return (uint8_t)(c - 'a');
    }
    if(c >= 'A' && c < 'Z')
    {
        return (uint8_t)(c - 'A' + 27);
    }
    std::ostringstream oss;
    oss << c << " isn't a valid position";
    throw InvalidLine(oss.str());
    return -1;
}
