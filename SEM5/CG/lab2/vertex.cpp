#include "vertex.h"
#include <cmath>

Vertex::Vertex(): x(0), y(0), z(0), w(0) {

}

Vertex::Vertex(const double x, const double y, const double z) : x(x), y(y), z(z) {

}

Vertex::Vertex(const double x, const double y, const double z, const double w) : x(x), y(y), z(z), w(w) {

}

void Vertex::rotateX(double angle) {
    double y_ = y;
    double z_ = z;
    y = y_ * cos(angle) - z_ * sin(angle);
    z = y_ * sin(angle) + z_ * cos(angle);
}

void Vertex::rotateY(double angle) {
    double x_ = x;
    double z_ = z;
    x = x_ * cos(angle) + z_ * sin(angle);
    z = -x_ * sin(angle) + z_ * cos(angle);
}

void Vertex::rotateZ(double angle) {
    double x_ = x;
    double y_ = y;
    x = x_ * cos(angle) - y_ * sin(angle);
    y = x_ * sin(angle) + y_ * cos(angle);
}

void Vertex::scaleModel(double scale) {
    x = x * scale;
    y = y * scale;
    z = z * scale;
}

void Vertex::shiftX(double x_) {
    x += x_;
}

void Vertex::shiftY(double y_) {
    y += y_;
}

void Vertex::shiftZ(double z_) {
    z += z_;
}

Vertex operator+(const Vertex& lhs, const Vertex& rhs) {
    return {
        lhs.x + rhs.x,
        lhs.y + rhs.y,
        lhs.z + rhs.z
    };
}

Vertex operator-(const Vertex& lhs, const Vertex& rhs) {
    return {
        lhs.x - rhs.x,
        lhs.y - rhs.y,
        lhs.z - rhs.z,
        1
    };
}

Vertex operator^(const Vertex& lhs, const Vertex& rhs) {
    return {
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x,
        1
    };
}

Vertex operator^(double lhs, const Vertex& rhs) {
    return {
        lhs * rhs.x,
        lhs * rhs.y,
        lhs * rhs.z,
        1
    };
}

double operator*(const Vertex& lhs, const Vertex& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}