#include "gobanwidget.hpp"
#include "engine.hpp"
#include "goban.hpp"

#include <states/statemanager.hpp>

#include <QPainter>
#include <QMouseEvent>
#include <QPen>

const QColor GobanWidget::c_colorBackground = QColor(242, 176, 109);

GobanWidget::GobanWidget(QWidget* p) : QWidget(p)
{
    setMinimumSize(800,800);
    setMouseTracking(true);
}

void GobanWidget::markGroup(const QGo::type_list_point& points)
{
    if(points.empty()) return;
    for(std::list<QGo::type_list_point>::iterator i = m_markedGroups.begin(); i != m_markedGroups.end(); ++i)
    {
        if(std::find(i->begin(), i->end(), points.front()) != i->end())
        {
            //the group is already marked, remove it.
            m_markedGroups.erase(i);
            update();
            return;
        }
    }
    m_markedGroups.push_back(points);
    update();
}

void GobanWidget::mouseMoveEvent(QMouseEvent * evt)
{
    QGo::goban_wp g = Engine::instance().goban();
    QGo::goban_sp goban = g.lock();
    if(!goban.get()) return;

    uint8_t gobanSize;
    double ratio, dx, dy;
    std::tie(gobanSize, ratio, dx, dy) = computeScreenSizes(goban);

    QPoint position = QPointF(((evt->pos().x() - dx) / ratio) + .5, ((evt->pos().y() - dy) / ratio) + .5).toPoint();
    if(position.x() > gobanSize || position.y() > gobanSize) return;
    if(position == m_mousePosition) return;

    m_mousePosition = position;
    update();
}

void GobanWidget::mousePressEvent(QMouseEvent* evt)
{
    Q_UNUSED(evt);
    try {
        const StateManager::state_up& currentState = StateManager::currentState();
        QGo::goban_wp g = Engine::instance().goban();
        QGo::goban_sp goban = g.lock();
        if(!goban.get()) return;
        currentState->leftClick(goban, (uint8_t)m_mousePosition.x(), (uint8_t)m_mousePosition.y());
    }
    catch(std::logic_error& err) {
        return;
    }
}

void GobanWidget::paintEvent(QPaintEvent* evt)
{
    Q_UNUSED(evt);
    QGo::goban_wp g = Engine::instance().goban();
    QGo::goban_sp goban = g.lock();
    if(!goban.get()) return;

    type_tuple_sizes sizes = computeScreenSizes(goban);
    uint8_t gobanSize = std::get<0>(sizes);
    double ratio = std::get<1>(sizes);

    QPainter p(this);
    p.translate(std::get<2>(sizes), std::get<3>(sizes));
    p.scale(ratio, ratio);

    drawBackground(p, gobanSize);
    drawStones(p, goban);
    drawMarkedGroups(p, goban);

    //drawing current mouse position
    p.drawEllipse(QPointF(m_mousePosition), 0.5, 0.5);
}

GobanWidget::type_tuple_sizes GobanWidget::computeScreenSizes(QGo::goban_sp goban)
{
    uint8_t gobanSize = goban->size();
    double ratio = (double)std::min(width()-c_marge, height()-c_marge) / (gobanSize+2);
    double tx = (width() - ratio * gobanSize) / 2;
    double ty = (height() - ratio * gobanSize) / 2;
    return std::make_tuple(gobanSize, ratio, tx, ty);
}

void GobanWidget::drawBackground(QPainter& p, uint8_t gobanSize) const
{
    p.save();
    p.setBrush(QBrush(c_colorBackground));
    p.drawRect(-1, -1, gobanSize+2, gobanSize+2);
    p.restore();
}

void GobanWidget::drawStones(QPainter& p, QGo::goban_sp goban)
{
    p.save();
    uint8_t gobanSize = goban->size();
    for(uint8_t i = 0; i <= gobanSize; i++)
    {
        p.drawLine(i, 0, i, gobanSize);
        p.drawLine(0, i, gobanSize, i);
    }

    for(uint8_t px = 0; px < gobanSize; px++)
        for(uint8_t py = 0; py < gobanSize; py++)
        {
            Goban::Case c = (*goban)(px, py);
            if(c != Goban::EMPTY)
            {
                if(c == Goban::BLACK) p.setBrush(QBrush(Qt::black));
                else p.setBrush(QBrush(Qt::white));
                p.drawEllipse(QPointF(px, py), 0.5, 0.5);
            }
        }
    p.restore();
}

void GobanWidget::drawMarkedGroups(QPainter& p, QGo::goban_sp goban)
{
    for(const QGo::type_list_point& lst : m_markedGroups)
    {
        drawGroup(p, goban, lst);
    }
}
void GobanWidget::drawGroup(QPainter& p, QGo::goban_sp goban, const QGo::type_list_point& group)
{
    if(group.empty()) return;

    p.save();
    QPen pen = p.pen();
    Goban::Case c = (*goban)(group.front().x(), group.front().y());
    if(c == Goban::EMPTY || c == Goban::WHITE)
        pen.setColor(Qt::black);
    else pen.setColor(Qt::white);
    pen.setWidthF(.1);
    p.setPen(pen);
    for(const Point& point : group)
    {
        drawShape(p, point);
    }
    p.restore();
}

void GobanWidget::drawShape(QPainter& p, const Point& point)
{
    double d = .3;
    p.drawLine(QPointF(point.x() - d, point.y() - d), QPointF(point.x() + d, point.y() + d));
    p.drawLine(QPointF(point.x() + d, point.y() - d), QPointF(point.x() - d, point.y() + d));
}
