#ifndef GOBANWIDGET_HPP
#define GOBANWIDGET_HPP

#include <point.hpp>

#include <QWidget>

#include <memory>
#include <tuple>

class Goban;

class GobanWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GobanWidget(QWidget *parent = 0);

    void markGroup(const QGo::type_list_point& points);

protected:
    void mouseMoveEvent(QMouseEvent * evt);
    void mousePressEvent(QMouseEvent* evt);
    void paintEvent(QPaintEvent* evt);

    constexpr static double c_marge = 10;
    const static QColor c_colorBackground;

private:
    /**
    * \brief Hold various size information use to convert position and draw on screen
    *
    * get(0) holds the goban size (uint8_t)
    * get(1) holds the ratio for scaling coordinates (double)
    * get(2) holds the size of the margin to the left (double)
    * get(3) holds the size of the margin to the top (double)
    */
    typedef std::tuple<uint8_t, double, double, double> type_tuple_sizes;
    type_tuple_sizes computeScreenSizes(QGo::goban_sp goban);

    QPoint m_mousePosition;
    std::list<QGo::type_list_point> m_markedGroups;

    void drawBackground(QPainter& p, uint8_t gobanSize) const;
    void drawStones(QPainter& p, QGo::goban_sp goban);
    void drawMarkedGroups(QPainter& p, QGo::goban_sp goban);
    void drawGroup(QPainter& p, QGo::goban_sp goban, const QGo::type_list_point& group);
    void drawShape(QPainter& p, const Point& point);

signals:

public slots:

};

#endif // GOBANWIDGET_HPP
