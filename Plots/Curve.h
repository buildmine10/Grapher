//
// Created by colli on 4/14/2022.
//

#ifndef GRAPHER_CURVE_H
#define GRAPHER_CURVE_H
#include <functional>
#include <array>
#include "../Renderables/Line.h"

class Curve {
public:
    Line line;

    Curve(std::function<float(float)> func, double lowerBound, double upperBound, int numberOfPoints);
    Curve(std::function<Vector3f(float)> func, double lowerBound, double upperBound, int numberOfPoints);
    Curve(std::function<Vector3f(float)> func, double lowerBound, double upperBound, double pointDensity);
};


#endif //GRAPHER_CURVE_H
