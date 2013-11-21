#include "mainwindow.hpp"
#include "gobanwidget.hpp"
#include "sgfreader.hpp"
#include "game.hpp"
#include "engine.hpp"
#include "statelesstooltipsingleton.hpp"
#include "statetooltipsingleton.hpp"
#include "statetoolbaraction.hpp"
#include <states/statemanager.hpp>
#include "gametreewidget.hpp"
#include <treemodel.hpp>

#include <QFileDialog>
#include <QMenuBar>
#include <QTextStream>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QActionGroup>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget* p)
    : QMainWindow(p)
{
    QWidget* w = new QWidget;

    QHBoxLayout* vbLayout = new QHBoxLayout;
    m_screen = new GobanWidget;
    vbLayout->addWidget(m_screen);

    m_model = new TreeModel;

    m_gameTree = new GameTreeWidget;
    m_gameTree->setModel(m_model);
    vbLayout->addWidget(m_gameTree);

    w->setLayout(vbLayout);
    setCentralWidget(w);

    createActions();
    createMenuBars();
    createToolBar();

    StateManager::changeStatusBarMessage().connect([this](const std::string& message){ this->statusBar()->showMessage(QString::fromStdString(message)); });

    setInstance(this);
}

MainWindow::~MainWindow()
{}

void MainWindow::popUpInt(const std::string& title, const std::string& message, int value)
{
    QMessageBox::information(this, QString::fromStdString(title), QString::fromStdString(message + std::to_string(value)));
}

void MainWindow::markGroup(const std::list<Point>& points)
{
    m_screen->markGroup(points);
}

void MainWindow::createActions()
{
    m_actionOpenFile = new QAction(tr("&Open"), this);
    m_actionOpenFile->setShortcut(tr("Ctrl+O"));
    connect(m_actionOpenFile, SIGNAL(triggered()), this, SLOT(onActionOpenFile()));
}

void MainWindow::createMenuBars()
{
    QMenu* file = menuBar()->addMenu(tr("&File"));
    file->addAction(m_actionOpenFile);
}

void MainWindow::createToolBar()
{
    QToolBar *toolBarStates = addToolBar(tr("Actions with state"));

    QActionGroup* group = new QActionGroup(this);
    StateToolTipSingleton::for_each([toolBarStates, group](std::size_t stateId, const std::string& tooltip, const std::string& icon)
    {
        QAction* action = new StateToolBarAction(stateId, QIcon("icons/"+QString::fromStdString(icon)), QString::fromStdString(tooltip));
        toolBarStates->addAction(action);
        group->addAction(action);
    });

    QToolBar* toolBarStateless = addToolBar(tr("Action with no state"));
    StatelessToolTipSingleton::for_each([this, toolBarStateless](const std::string& tooltip, const std::string& icon, std::function<void()> callback)
    {
        QAction* action = new QAction(QIcon("icons/"+QString::fromStdString(icon)), QString::fromStdString(tooltip), nullptr);
        QObject::connect(action, &QAction::triggered, callback);
        toolBarStateless->addAction(action);
    });
}

#include <QDebug>

void MainWindow::onActionOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select a game to open"), QString(),"*.sgf");
    if(fileName.isEmpty()) return;
    if(!QFile::exists(fileName)) return;

    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&file);
    QString line;
    std::list<std::string> lines;
    while(!flux.atEnd())
    {
        line = flux.readLine();
        lines.push_back(line.toStdString());
    }

    //preliminary checks on overall file structure
    while(!lines.empty() && lines.back().empty()) lines.pop_back();
    if(lines.empty())
    {
        qDebug() << "no line to read";
        return;
    }

    if(lines.front().empty() || *lines.front().begin() != '(')
    {
        qDebug() << "no parenthesis to open the file";
        return;
    }
    lines.front().erase(0,1);

    if(lines.back().empty() || *(--lines.back().end()) != ')')
    {
        qDebug() << "no parenthesis to close the file";
        return;
    }
    lines.back().pop_back();
    while(!lines.empty() && lines.back().empty()) lines.pop_back();

    if(!lines.front().empty() && *lines.front().begin() == ';') {
        lines.front().erase(0, 1);
    }

    try {
        Game g = SGFReader::parse(lines);
        qDebug() << QString::fromStdString(g.report());
        g.loadMovesOnto(Engine::instance().goban());
        m_model->setTree(g.tree());
        m_gameTree->update();
    }
    catch(SGFReader::InvalidLine& ex)
    {
        QMessageBox::critical(this, tr("Unable to parse file: invalid file format"), ex.what());
    }
    catch(SGFReader::UnreckognizedCommand& ex)
    {
        QMessageBox::critical(this, tr("Unable to parse file: sgf command not taken care of"), ex.what());
    }
}
