#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <ui/imainwindow.hpp>

#include <QMainWindow>

class GobanWidget;
class GameTreeWidget;

class MainWindow : public QMainWindow, public iMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual void popUpInt(const std::string& title, const std::string& message, int value) override;

    virtual void markGroup(const std::list<Point>& points) override;

private:
    GobanWidget* m_screen;
    GameTreeWidget* m_gameTree;
    QAction* m_actionOpenFile;

    void createActions();
    void createMenuBars();
    void createToolBar();

private slots:
    void onActionOpenFile();
};

#endif // MAINWINDOW_HPP
