//
// Created by kiril on 19.11.2023.
//

#ifndef OBJECT_H
#define OBJECT_H
#include <QtOpenGL>
#include "Vertex.h"

struct Transformation {
    float angleX = 0;
    float angleY = 0;
    float angleZ = 0;
    float translateX = 0;
    float translateY = 0;
    float translateZ = 0;
    float scaleX = 1;
    float scaleY = 1;
    float scaleZ = 1;
};

struct Properties {
    float ambient = 0.5;
    float specular = 0.5;
    float shininess = 0.5;
    float diffuse = 0.5;
};

struct Object {
    QVector<Vertex> vertices;
    QVector<unsigned int> polygons;
    Transformation transform;
    Properties property;


    Object(const QVector<Vertex>& vertices, const QVector<unsigned int>& polygons);
    Object();
};



#endif //OBJECT_H
