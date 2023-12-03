//
// Created by kiril on 19.11.2023.
//

#ifndef VERTEX_H
#define VERTEX_H
#include <QtOpenGL>


struct Vertex {
    QVector4D position;
    QVector4D color;
    QVector4D normal;
    Vertex(const QVector4D& position, const QVector4D& color, const QVector4D& normal);
};


#endif //VERTEX_H
