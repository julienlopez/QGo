#ifndef GAMETREEWIDGET_HPP
#define GAMETREEWIDGET_HPP

#include <QAbstractItemView>

#include <globals.hpp>

class GameTreeWidget : public QAbstractItemView
{
    Q_OBJECT
public:
    explicit GameTreeWidget(QWidget *parent = 0);

    virtual QModelIndex indexAt(const QPoint& point) const override;

    virtual bool isIndexHidden(const QModelIndex& index) const override;

    virtual void scrollTo(const QModelIndex& index, ScrollHint hint = EnsureVisible) override;

    virtual void setModel(QAbstractItemModel* model) override;

    virtual QRect visualRect(const QModelIndex& index) const override;

public slots:
    virtual void reset() override;
    
protected:
    virtual int horizontalOffset() const override;
    virtual QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;
    virtual void paintEvent(QPaintEvent* evt) override;
    virtual void scrollContentsBy(int dx, int dy) override;
    virtual void setSelection(const QRect& rect, QItemSelectionModel::SelectionFlags flags) override;
    virtual int verticalOffset() const override;
    virtual QRegion visualRegionForSelection(const QItemSelection& selection) const override;
    
protected slots:
    virtual void dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight);
    virtual void rowsAboutToBeRemoved(const QModelIndex& parent, int start, int end) override;
    virtual void rowsInserted(const QModelIndex& parent, int start, int end) override;

private:
    struct Square{
        QRect rect;
        QGo::Case color;
    };
    using type_container_squares = QMap<QModelIndex, Square>;

    mutable bool m_isUpToDate;
    mutable int m_idealWidth;
    mutable int m_idealHeight;
    mutable type_container_squares m_squares;

    static constexpr uint8_t s_SquareWidth = 50;

    void updatePositionsIfNecessary() const;
    
};

#endif // GAMETREEWIDGET_HPP
