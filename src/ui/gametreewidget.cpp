#include "gametreewidget.hpp"

#include <functional>
#include <cassert>

#include <QScrollBar>
#include <QPainter>

#include <QDebug>

GameTreeWidget::GameTreeWidget(QWidget* p) : QAbstractItemView(p), m_isUpToDate(true), m_idealWidth(0), m_idealHeight(0)
{
    setFocusPolicy(Qt::WheelFocus);
    horizontalScrollBar()->setRange(0, 0);
    verticalScrollBar()->setRange(0, 0);
}

QModelIndex GameTreeWidget::indexAt(const QPoint& point) const
{
    QPoint actualPosition = point;
    actualPosition.rx() += horizontalScrollBar()->value();
    actualPosition.ry() += verticalScrollBar()->value();
    updatePositionsIfNecessary();
    type_container_squares::const_iterator i = std::find_if(m_squares.begin(), m_squares.end(),
        [&point](const Square& s) { return s.rect.contains(point.x(), point.y()); });
    if(i != m_squares.end()) return QModelIndex();
    return i.key();
}

bool GameTreeWidget::isIndexHidden(const QModelIndex& index) const
{
    Q_UNUSED(index);
    return false;
}

void GameTreeWidget::scrollTo(const QModelIndex& index, ScrollHint hint)
{
    Q_UNUSED(hint);

    QRect viewRect = viewport()->rect();
    QRect itemRect = visualRect(index);

    if(itemRect.left() < viewRect.left())
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() + itemRect.left() - viewRect.left());
    else if(itemRect.right() > viewRect.right())
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() + qMin(itemRect.right() - viewRect.right(), itemRect.left() - viewRect.left()));

    if(itemRect.top() < viewRect.top())
        verticalScrollBar()->setValue(verticalScrollBar()->value() + itemRect.top() - viewRect.top());
    else if(itemRect.bottom() > viewRect.bottom())
        verticalScrollBar()->setValue(verticalScrollBar()->value() + qMin(itemRect.bottom() - viewRect.bottom(), itemRect.top() - viewRect.top()));
    viewport()->update();
}

void GameTreeWidget::setModel(QAbstractItemModel* model)
{
    m_isUpToDate = false;
    QAbstractItemView::setModel(model);
}

QRect GameTreeWidget::visualRect(const QModelIndex& index) const
{
    if(!index.isValid()) return QRect();
    updatePositionsIfNecessary();
    type_container_squares::const_iterator i = m_squares.find(index);
//    assert(i != m_squares.end());
    if(i == m_squares.end())
    {
        qDebug() << "no square for " << index;
        assert(false);
    }
    return i.value().rect;
}

void GameTreeWidget::reset()
{
    qDebug() << "GameTreeWidget::reset()";
    m_isUpToDate = false;
    QAbstractItemView::reset();
}

int GameTreeWidget::horizontalOffset() const
{
    return horizontalScrollBar()->value();
}

QModelIndex GameTreeWidget::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(cursorAction);
    Q_UNUSED(modifiers);
    return QModelIndex();
}

void GameTreeWidget::paintEvent(QPaintEvent* evt)
{
    Q_UNUSED(evt);
    QPainter p(viewport());
    for(const Square& square : m_squares)
    {
        p.setBrush(square.color==QGo::BLACK?Qt::black:Qt::white);
        p.drawEllipse(square.rect);
    }
}

void GameTreeWidget::scrollContentsBy(int dx, int dy)
{
    scrollDirtyRegion(dx, dy);
    viewport()->scroll(dx, dy);
}

void GameTreeWidget::setSelection(const QRect& rect, QItemSelectionModel::SelectionFlags flags)
{
    //TODO here
}

int GameTreeWidget::verticalOffset() const
{
    return verticalScrollBar()->value();
}

QRegion GameTreeWidget::visualRegionForSelection(const QItemSelection& selection) const
{
    //TODO here
}

void GameTreeWidget::dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight)
{
    qDebug() << "GameTreeWidget::dataChanged()";
    m_isUpToDate = false;
    QAbstractItemView::dataChanged(topLeft, bottomRight);
}

void GameTreeWidget::rowsAboutToBeRemoved(const QModelIndex& parent, int start, int end)
{
    m_isUpToDate = false;
    QAbstractItemView::rowsAboutToBeRemoved(parent, start, end);
}

void GameTreeWidget::rowsInserted(const QModelIndex& parent, int start, int end)
{
    m_isUpToDate = false;
    QAbstractItemView::rowsInserted(parent, start, end);
}

void GameTreeWidget::updatePositionsIfNecessary() const
{
    if(m_isUpToDate) return;
    qDebug() << "GameTreeWidget::updatePositions";

    QModelIndex parent;
    int currentHeight = 0;
    while(true)
    {
        int nbChildren = model()->rowCount(parent);
//        qDebug() << "nbChildren = " << nbChildren;
        assert(nbChildren < 2);
        if(nbChildren == 0) break;
        int i = 0;
//        for(int i = 0; i < nbChildren; i++)
//        {
            QModelIndex index = model()->index(i, 0, parent);
            QRect r(i*s_SquareWidth, currentHeight, s_SquareWidth, s_SquareWidth);
//            qDebug() << "creating a square for " << index << " in " << r;
            m_squares[index] = {r, model()->data(index).toBool()?QGo::BLACK:QGo::WHITE};
//        }
        parent = index;
        currentHeight += s_SquareWidth;
    }
}
