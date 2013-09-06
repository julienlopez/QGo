#ifndef STATETOOLBARACTION_HPP
#define STATETOOLBARACTION_HPP

#include <QAction>

class StateToolBarAction : public QAction
{
    Q_OBJECT
public:
    explicit StateToolBarAction(std::size_t stateId, const QIcon& icon, const QString& title, QObject *parent = 0);
    
private:
    std::size_t m_stateId;

private slots:
    void onClick();
};

#endif // STATETOOLBARACTION_HPP
