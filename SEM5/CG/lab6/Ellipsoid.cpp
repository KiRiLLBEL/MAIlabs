#include "Ellipsoid.h"
#include <iostream>
Ellipsoid::Ellipsoid() : a(3), b(3), c(3), hResolution(3), wResolution(3) {

}

Ellipsoid::Ellipsoid(double a, double b, double c, int hResolution, int wResolution) : a(a), b(b), c(c), hResolution(hResolution), wResolution(wResolution) {

}

void Ellipsoid::setHResolution(int step_) {
    hResolution = step_;
}

void Ellipsoid::setWResolution(int step_) {
    wResolution = step_;
}

void Ellipsoid::setA(double a_) {
    a = a_;
}

void Ellipsoid::setB(double b_) {
    b = b_;
}

void Ellipsoid::setC(double c_) {
    c = c_;
}

Object Ellipsoid::generate_mesh() {
    QVector<Vertex> vertices;
    QVector<unsigned int> polygons;
    for(int i = 0; i <= hResolution; ++i) {
        for(int j = 0; j <= wResolution; ++j) {
            float phi = i * 2 * M_PI / hResolution;
            float ksi = j * M_PI / hResolution;
            QVector4D position;
            QVector4D normal(0, 0, 0, 0);
            QVector4D color(0.5, 0.5, 0.5, 1);
            position.setX(a * cos(phi) * sin(ksi));
            position.setY(b * sin(phi) * sin(ksi));
            position.setZ(c * cos(ksi));
            position.setW(1);
            position.normalize();
            normal.setX(position.x() / (a * a));
            normal.setY(position.y() / (b * b));
            normal.setZ(position.z() / (c * c));
            normal.normalize();
            vertices.append(Vertex(position, color, normal));
        }
    }

    for(int i = 0; i < hResolution; ++i) {
        for(int j = 0; j < wResolution; ++j) {
            int v1 = i * (wResolution + 1) + j;
            int v2 = i * (wResolution + 1) + j + 1;
            int v3 = (i + 1) * (wResolution + 1) + j;
            int v4 = (i + 1) * (wResolution + 1) + j + 1;

            polygons.append(v1);
            polygons.append(v2);
            polygons.append(v3);
            polygons.append(v2);
            polygons.append(v4);
            polygons.append(v3);
        }
    }

    return {vertices, polygons};
}