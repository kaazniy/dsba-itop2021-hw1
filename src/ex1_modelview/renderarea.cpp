#include "renderarea.h"
#include <QPainter>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{

}

void RenderArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QColor color(0, 0, 0);
    painter.setBrush(color);
    static const QPointF points[4] =
    {
        QPointF(40, 40),
        QPointF(100, 100),
        QPointF(40, 100),
        QPointF(100, 40),




    };
    painter.drawConvexPolygon(points, 4);
}
