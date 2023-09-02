//
// Created by colli on 5/22/2022.
//

#ifndef GRAPHER_COLORFIELD_H
#define GRAPHER_COLORFIELD_H

#include <functional>
#include <array>
#include "../Renderables/Volume.h"

class ColorField {
public:
    Volume volume;

    ColorField(std::function<float(float, float, float)> func, std::array<float, 2> xBounds, std::array<float, 2> yBounds, std::array<float, 2> zBounds, std::array<int, 3> divisions);
    ColorField(std::function<std::array<float, 4>(float, float, float)> func, std::array<float, 2> xBounds, std::array<float, 2> yBounds, std::array<float, 2> zBounds, std::array<int, 3> divisions);
};


#endif //GRAPHER_COLORFIELD_H
