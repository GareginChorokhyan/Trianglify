#ifndef TRIANGULATION_HPP
#define TRIANGULATION_HPP

#include <QtWidgets>
#include <vector>

struct Point
{
    int x, y;
    bool operator==(const Point& other) const { return x == other.x && y == other.y; }
};

using PointSet = std::vector<Point>;
using AdjList = std::vector<size_t>;
using GraphMatrix = std::vector<AdjList>;

class TriangulationWidget : public QWidget
{
    Q_OBJECT
private:
    PointSet points;
    GraphMatrix incrementalTriangulation;

public:
    explicit TriangulationWidget(QWidget* parent = nullptr);

    void addPoint(const QPoint& point);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    bool isIntersect(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
    GraphMatrix computeTriangulationInc(const PointSet& points);
};

#endif // TRIANGULATION_HPP