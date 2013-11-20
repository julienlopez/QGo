#include "treemodel.hpp"

TreeModel::TreeModel(QObject* p) : QAbstractItemModel(p), m_tree()
{
}

Qt::ItemFlags TreeModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if(index.isValid()) flags |= Qt::ItemIsSelectable;
    return flags;
}

QVariant TreeModel::data(const QModelIndex& index, int role) const
{
    if(index.isValid() && index.column() == 0 && index.row() == 0)
    {
        type_tree::vertex_descriptor id = index.internalId();
        if(role == Qt::ToolTipRole)
            return QString::number(m_tree(id).position().x()) + ", " + QString::number(m_tree(id).position().x());
        else if(role == Qt::DisplayRole)
            return m_tree(id).color() == QGo::BLACK;
    }
    return QVariant();
}

QVariant TreeModel::headerData(int /*section*/, Qt::Orientation /*orientation*/, int /*role*/) const
{
    return QVariant();
}

int TreeModel::rowCount(const QModelIndex& parent) const
{
    if(parent.isValid())
        return m_tree.nbChildren(parent.internalId());
    return m_tree.nbRoots();
}

int TreeModel::columnCount(const QModelIndex&) const
{
    return 1;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if(row >= rowCount()) return QModelIndex();
    type_tree::vertex_descriptor id = m_tree.child(parent.internalId(), row);
    return createIndex(row, column,(int) id);
}

QModelIndex TreeModel::parent(const QModelIndex &child) const
{
    if(!child.isValid()) return QModelIndex();
    type_tree::vertex_descriptor id = m_tree.parent(child.internalId());
    return createIndex(m_tree.positionFromParent(id), 0, (uint32_t)m_tree.parent(id));
}

void TreeModel::setTree(const type_tree& tree)
{
    beginResetModel();
    m_tree = tree;
    endResetModel();
}
