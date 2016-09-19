#include "game.hpp"
#include "goban.hpp"
#include "sgfreader.hpp"

#include <iostream>

#include <QCoreApplication>

#include <QDir>
#include <QFileInfo>
#include <QTimer>

#include <QDebug>

std::size_t total_nb_of_files = 0;
std::size_t nb_of_games_with_variations = 0;
std::size_t total_nb_of_games = 0;

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
        qDebug() << file_name;
        parse(file_name, is_recursive);
    }
    qDebug() << total_nb_of_files << " files read";
    qDebug() << total_nb_of_games << " games parsed";
    qDebug() << nb_of_games_with_variations << " games with variations found";
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

void display(const std::shared_ptr<Goban>& goban)
{
    for(uint8_t x = 0; x < goban->size() + 2; x++)
        std::cout << "=";
    std::cout << "\n";
    for(uint8_t y = 0; y < goban->size(); y++)
    {
        std::cout << "|";
        for(uint8_t x = 0; x < goban->size(); x++)
        {
            std::cout << printStone((*goban)(x, y));
        }
        std::cout << "|\n";
    }
    for(uint8_t x = 0; x < goban->size() + 2; x++)
        std::cout << "=";
    std::cout << std::endl;
}

void parseFile(const QFileInfo& path)
{
    Q_ASSERT(path.isFile() && path.isReadable());
    qDebug() << "parsing " << path.filePath();
    total_nb_of_files++;
    try
    {
        const auto game = SGFReader::parse(SGFReader::parseFileIntoLines(path.filePath().toStdWString()));
        total_nb_of_games++;
        if(game.hasAlternativeMoves())
        {
            qDebug() << "Unable to parse games with variations";
            nb_of_games_with_variations++;
        }
        auto goban = std::make_shared<Goban>(19);
        game.loadMovesOnto(goban);
        display(goban);
    }
    catch(...)
    {
        qDebug() << "Unable to parse " << path.filePath();
    }
}

void parse(const QFileInfo& path, const bool recursive)
{
    if(recursive && path.isDir())
        parseDir(path);
    if(path.isFile() && path.isReadable())
        parseFile(path);
}
