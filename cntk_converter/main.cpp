#include "neuralnetworks/cntkwriter.hpp"

#include "game.hpp"
#include "sgfreader.hpp"

#include <fstream>
#include <iostream>

#include <QCoreApplication>

#include <QDir>
#include <QFileInfo>
#include <QTimer>

std::size_t total_nb_of_files = 0;
std::size_t nb_of_games_with_variations = 0;
std::size_t total_nb_of_games = 0;

CntkWriter writer("train.txt", "test.txt", 0.2);

std::ostream& operator<<(std::ostream& o, const QString& str)
{
    o << str.toStdString();
    return o;
}

QGo::Case colorToPlay(const Goban& g)
{
    return g.nbStonesPlaced()?QGo::WHITE:QGo::BLACK;
}

void parse(const QFileInfo& path, const bool recursive);

int main(int argc, char* argv[])
{
	QCoreApplication app(argc, argv);
    auto arguments = app.arguments();
    arguments.pop_front();

    const auto it = std::find(arguments.begin(), arguments.end(), "-r");
    const auto is_recursive = it != arguments.end();
    if(it != arguments.end())
        arguments.erase(it);

    for(const auto& file_name : arguments)
    {
        std::cout << file_name << std::endl;
        parse(file_name, is_recursive);
    }
    std::cout << total_nb_of_files << " files read" << std::endl;
    std::cout << total_nb_of_games << " games parsed" << std::endl;
    std::cout << nb_of_games_with_variations << " games with variations found" << std::endl;
    QTimer::singleShot(100, &app, SLOT(quit()));
	return app.exec();
}

void parseDir(const QFileInfo& path)
{
    Q_ASSERT(path.isDir());
    QDir dir(path.filePath());
    for(const auto& entry : dir.entryInfoList())
    {
        if(entry.isRoot() || entry.isSymLink() || entry.fileName() == "." || entry.fileName() == "..") continue;
        parse(entry, true);
    }
}

std::string printStone(QGo::Case c)
{
    switch(c)
    {
    case QGo::BLACK:
        return "B";
    case QGo::WHITE:
        return "W";
    case QGo::EMPTY:
        return " ";
    }
    assert(false);
    return "";
}

void display(const Goban& goban)
{
    std::cout << goban.nbStonesPlaced() << " moves : " << printStone(colorToPlay(goban)) << " to play" << std::endl;
    for(uint8_t x = 0; x < goban.size() + 2; x++)
        std::cout << "=";
    std::cout << "\n";
    for(uint8_t y = 0; y < goban.size(); y++)
    {
        std::cout << "|";
        for(uint8_t x = 0; x < goban.size(); x++)
        {
            std::cout << printStone(goban(x, y));
        }
        std::cout << "|\n";
    }
    for(uint8_t x = 0; x < goban.size() + 2; x++)
        std::cout << "=";
    std::cout << std::endl;
}

void parseFile(const QFileInfo& path)
{
    Q_ASSERT(path.isFile() && path.isReadable());
    std::cout << "parsing " << path.filePath() << std::endl;
    total_nb_of_files++;
    try
    {
        const auto game = SGFReader::parse(SGFReader::parseFileIntoLines(path.filePath().toStdWString()));
        total_nb_of_games++;
        if(game.boardSize() != 19)
        {
            std::cout << "Unable to parse games of size " << (int)game.boardSize() << std::endl;
            return;
        }
        if(game.hasAlternativeMoves())
        {
            std::cout << "Unable to parse games with variations" << std::endl;
            nb_of_games_with_variations++;
            return;
        }
        //auto goban = std::make_shared<Goban>(19);
        //game.loadMovesOnto(goban);
        //display(goban);
        const auto moves = game.generateAllMoves();
        Goban goban(game.boardSize());
        for(const auto& move : moves)
        {
            //display(goban);
            //std::cout << "next move is " << printStone(move.color()) << " on {" << (uint)move.position().x() << ", " << (uint)move.position().y() << "}\n";
            const auto encoded_goban = encode(goban, move.color());
            //std::copy(begin(encoded_goban), end(encoded_goban), std::ostream_iterator<int>(std::cout, ",")); std::cout << std::endl;
            Goban next_move(game.boardSize());
            next_move.placeStone(move.position().x(), move.position().y(), move.color());
            const auto encoded_next_move = encode(next_move, move.color());
            //std::copy(begin(encoded_next_move), end(encoded_next_move), std::ostream_iterator<int>(std::cout, ",")); std::cout << std::endl;
            //display(next_move);
            //std::cout << std::endl;
            goban.placeStone(move.position().x(), move.position().y(), move.color());
            writer.addLine(encoded_goban, encoded_next_move);
        }
    }
    catch(...)
    {
        std::cout << "Unable to parse " << path.filePath() << std::endl;
    }
}

void parse(const QFileInfo& path, const bool recursive)
{
    if(recursive && path.isDir())
        parseDir(path);
    if(path.isFile() && path.isReadable())
        parseFile(path);
}
