#ifndef TREEMODEL_HPP
#define TREEMODEL_HPP

#include <utils/boosttree.hpp>

#include "game.hpp"

#include <QAbstractItemModel>

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit TreeModel(QObject *parent = 0);
    
signals:
    
public slots:

private:
    utils::BoostTree<Game::Move> m_tree;
};

#endif // TREEMODEL_HPP
