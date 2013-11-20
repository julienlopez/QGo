#ifndef TREEMODEL_HPP
#define TREEMODEL_HPP

#include <game.hpp>

#include <QAbstractItemModel>

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    typedef utils::BoostTree<Game::Move> type_tree;

    explicit TreeModel(QObject *parent = 0);

    virtual Qt::ItemFlags flags(const QModelIndex& index) const;

    virtual QVariant data(const QModelIndex& index, int role) const;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    virtual QModelIndex parent(const QModelIndex &child) const;

    void setTree(const type_tree& tree);
    
signals:
    
public slots:

private:
    type_tree m_tree;
};

#endif // TREEMODEL_HPP
