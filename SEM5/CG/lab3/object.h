#ifndef OBJECT_H
#define OBJECT_H
#include <QVector>
#include <QColor>
#include "vertex.h"
#include "polygon.h"

struct Transformation {
    double scale = 1;
    double angle_x = 0;
    double angle_y = 0;
    double angle_z = 0;
    double x = 0;
    double y = 0;
    double z = 0;
};

struct LightProperty {
    double ambient = 0;
    double diffuse = 0;
    double specular = 0;
    double shininess = 0;
};

struct Object
{
    Object();
    void addVertex(double x, double y, double z);
    void addPolygon(int v1, int v2, int v3, QColor color);
    Transformation transform;
    LightProperty property;
    QVector<Vertex> vertices;
    QVector<Polygon> polygons;
};

#endif // OBJECT_H
