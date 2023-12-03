//
// Created by kiril on 19.11.2023.
//

#include "Object.h"

Object::Object(const QVector<Vertex>& vertices, const QVector<unsigned int>& polygons)
    : vertices(vertices), polygons(polygons) {
}

Object::Object() {

}
