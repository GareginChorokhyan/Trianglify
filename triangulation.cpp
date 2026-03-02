#include "triangulation.hpp"
#include <cmath>
#include <algorithm>

TriangulationWidget::TriangulationWidget(QWidget* parent)
    : QWidget(parent) {}

void TriangulationWidget::addPoint(const QPoint& point)
{
    points.push_back({point.x(), point.y()});
    incrementalTriangulation = computeTriangulationInc(points);
    update();
}

void TriangulationWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::black);
    for (const auto& point : points)
        painter.drawPoint(point.x, point.y);

    painter.setPen(QPen(Qt::blue, 1));
    for (size_t i = 0; i < incrementalTriangulation.size(); ++i)
        for (size_t j : incrementalTriangulation[i])
            painter.drawLine(points[i].x, points[i].y, points[j].x, points[j].y);
}

void TriangulationWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        addPoint(event->pos());
}

bool TriangulationWidget::isIntersect(const Point& p1, const Point& p2, const Point& p3, const Point& p4)
{
    auto direction = [](const Point& pi, const Point& pj, const Point& pk)
    {
        return (pk.x - pi.x) * (pj.y - pi.y) - (pj.x - pi.x) * (pk.y - pi.y);
    };

    int d1 = direction(p3, p4, p1);
    int d2 = direction(p3, p4, p2);
    int d3 = direction(p1, p2, p3);
    int d4 = direction(p1, p2, p4);

    return ((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
           ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0));
}

GraphMatrix TriangulationWidget::computeTriangulationInc(const PointSet& points)
{
    GraphMatrix result(points.size());
    for (size_t i = 0; i < points.size(); ++i)
    {
        for (size_t j = i + 1; j < points.size(); ++j)
        {
            bool validEdge = true;
            for (size_t k = 0; k < points.size(); ++k)
            {
                if (k != i && k != j)
                {
                    for (size_t l : result[k])
                    {
                        if (l != i && l != j && isIntersect(points[i], points[j], points[k], points[l]))
                        {
                            validEdge = false;
                            break;
                        }
                    }
                    if (!validEdge) break;
                }
            }
            if (validEdge)
            {
                result[i].push_back(j);
                result[j].push_back(i);
            }
        }
    }
    return result;
}
