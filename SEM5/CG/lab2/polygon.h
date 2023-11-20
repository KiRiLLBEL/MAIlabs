#ifndef POLYGON_H
#define POLYGON_H
#include <QColor>

struct Polygon
{
    int v1, v2, v3;
    QColor color;
    Polygon(int v1, int v2, int v3, QColor color);
};

#endif // POLYGON_H
