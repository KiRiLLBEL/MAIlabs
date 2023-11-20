#include "object.h"

void Object::addVertex(double x, double y, double z) {
    vertices.emplace_back(x, y, z);
}

void Object::addPolygon(int v1, int v2, int v3, QColor color) {
    polygons.emplace_back(v1 - 1, v2 - 1, v3 - 1, color);
}

Object::Object() = default;
