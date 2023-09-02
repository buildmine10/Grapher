//
// Created by colli on 4/14/2022.
//

#ifndef GRAPHER_SURFACE_H
#define GRAPHER_SURFACE_H
#include <functional>
#include <array>
#include "../Renderables/Mesh.h"

class Surface {
public:
    Mesh mesh;

    Surface(std::function<float(float, float)> func, std::array<double, 2> xBounds, std::array<double, 2> yBounds, int numberOfPoints);
    Surface(std::function<Vector3f(float, float)> func, std::array<double, 2> uBounds, std::array<double, 2> vBounds, int numberOfPoints);
};


#endif //GRAPHER_SURFACE_H
