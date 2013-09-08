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

    virtual Qt::ItemFlags flags(const QModelIndex& index) const;

    virtual QVariant data(const QModelIndex& index, int role) const;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    virtual int rowCount(const QModelIndex &parent) const;

    virtual int columnCount(const QModelIndex &parent) const;

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;

    virtual QModelIndex parent(const QModelIndex &child) const;
    
signals:
    
public slots:

private:
    typedef utils::BoostTree<Game::Move> type_tree;
    type_tree m_tree;
};

#endif // TREEMODEL_HPP
