#include <QApplication>
#include "triangulation.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    TriangulationWidget widget;
    widget.setGeometry(100, 100, 400, 400);
    widget.show();
    return app.exec();
}
