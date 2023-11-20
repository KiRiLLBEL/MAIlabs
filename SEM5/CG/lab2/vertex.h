#ifndef VERTEX_H
#define VERTEX_H

struct Vertex
{
    double x, y, z, w = 0, h = 0;
    Vertex();
    Vertex(double x, double y, double z);
    Vertex(double x, double y, double z, double w);
    void rotateX(double angle);
    void rotateY(double angle);
    void rotateZ(double angle);
    void scaleModel(double scale);
    void shiftX(double x);
    void shiftY(double y);
    void shiftZ(double z);
};

Vertex operator+(const Vertex& lhs, const Vertex& rhs);
Vertex operator-(const Vertex& lhs, const Vertex& rhs);
Vertex operator^(const Vertex& lhs, const Vertex& rhs);
Vertex operator^(double lhs, const Vertex& rhs);
double operator*(const Vertex& lhs, const Vertex& rhs);

#endif // VERTEX_H
