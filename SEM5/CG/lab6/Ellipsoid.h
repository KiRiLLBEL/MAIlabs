//
// Created by kiril on 12.11.2023.
//

#ifndef ELLIPSOID_H
#define ELLIPSOID_H
#include "Object.h"


class Ellipsoid {
public:
    Ellipsoid();
    explicit Ellipsoid(double a, double b, double c, int hResolution, int wResolution);
    void setHResolution(int step_);
    void setWResolution(int step_);
    void setA(double a_);
    void setB(double b_);
    void setC(double c_);
    Object generate_mesh();
private:
    int hResolution, wResolution;
    double a, b, c;
};



#endif //ELLIPSOID_H
