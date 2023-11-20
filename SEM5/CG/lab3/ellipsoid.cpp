#include "ellipsoid.h"
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
    Object object;
    for(int i = 0; i <= hResolution; ++i) {
        for(int j = 0; j <= wResolution; ++j) {
            float phi = i * 2 * M_PI / hResolution;
            float ksi = j * M_PI / hResolution;

            Vertex vertex = {
                a * cos(phi) * sin(ksi),
                b * sin(phi) * sin(ksi),
                c * cos(ksi)
            };
            object.vertices.push_back(vertex);
        }
    }

    for(int i = 0; i < hResolution; ++i) {
        for(int j = 0; j < wResolution; ++j) {
            int v1 = i * (wResolution + 1) + j;
            int v2 = i * (wResolution + 1) + j + 1;
            int v3 = (i + 1) * (wResolution + 1) + j;
            int v4 = (i + 1) * (wResolution + 1) + j + 1;

            object.polygons.emplace_back(v1, v2, v3, Qt::gray);
            object.polygons.emplace_back(v2, v4, v3, Qt::gray);
        }
    }

    return object;
}