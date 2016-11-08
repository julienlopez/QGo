#include "mainwindow.hpp"

#include "treemodel.hpp"

#include "gametreewidget.hpp"
#include "gobanwidget.hpp"
#include "statelesstooltipsingleton.hpp"
#include "statetooltipsingleton.hpp"
#include "statetoolbaraction.hpp"

#include "states/statemanager.hpp"

#include "sgfreader.hpp"
#include "game.hpp"
#include "engine.hpp"

#include "neuralnetworks/cntkwriter.hpp"
#include "neuralnetworks/neuralnetwork.hpp"

#include <QApplication>
#include <QFileDialog>
#include <QMenuBar>
#include <QTextStream>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QActionGroup>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <iostream>

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

    StatelessToolTipSingleton::addToolButton("show GoNet guess", "ask_gonet.png", [](){
        std::cout << "GoNet" << std::endl;
        auto goban = Engine::instance().goban().lock();
        const auto encoded_goban = encode(*goban, (goban->lastStonePlayed() == QGo::Case::BLACK ? QGo::Case::WHITE : QGo::Case::BLACK));
        std::vector<float> inputs(encoded_goban.size());
        std::copy(begin(encoded_goban), end(encoded_goban), begin(inputs));

        //std::vector<QString> suffixes{/*".0",*/ ".1", ".2", ".3", ".4", ".5", ".6", ".7", ".8", ".9", ""};
        std::vector<QString> suffixes{".1"};
        for(const auto& n : suffixes)
        {
            std::cout << ("ConvBatchNorm1"+n).toStdString() << std::endl;
            NeuralNetworks::NeuralNetwork nn(QDir(qApp->applicationDirPath()).filePath("../neural_network/trained_nets/ConvBatchNorm1"+n).toStdString());
            //for(const auto s : inputs)
            //{
            //    std::cout << s << " ";
            //}
            //std::cout << std::endl;
            const auto outputs = nn(inputs);
            for(const auto s : outputs)
            {
                std::cout << s << " ";
            }
            std::cout << std::endl;
        }
    });

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
    const auto lines = SGFReader::parseFileIntoLines(fileName.toStdWString());
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
