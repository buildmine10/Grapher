//
// Created by colli on 5/22/2022.
//

#include "ColorField.h"
#include "../Math/Vector3.h"
#include <cmath>
#include <algorithm>

ColorField::ColorField(std::function<float(float, float, float)> func, std::array<float, 2> xBounds, std::array<float, 2> yBounds, std::array<float, 2> zBounds, std::array<int, 3> divisions) {
    Vector3f scale = {xBounds[1] - xBounds[0], yBounds[1] - yBounds[0], zBounds[1] - zBounds[0]};
    volume = Volume(divisions[0], divisions[1], divisions[2], scale.x, scale.z, scale.y);
    volume.position = {xBounds[0], yBounds[0], zBounds[0]};

    for(int ix = 0; ix < divisions[0]; ix++){
        float x = xBounds[0] + scale.x * ix / divisions[0];
        for(int iy = 0; iy < divisions[1]; iy++){
            float y = yBounds[0] + scale.y * iy / divisions[1];
            for(int iz = 0; iz < divisions[2]; iz++){
                float z = zBounds[0] + scale.z * iz / divisions[2];
                uint8_t value = (uint8_t) std::max(std::min(std::floor(255 * func(x, y, z)), 255.f), 0.f);
                volume.setValue(ix, iy, iz, value, value, value, value);
            }
        }
    }
}

ColorField::ColorField(std::function<std::array<float, 4>(float, float, float)> func, std::array<float, 2> xBounds, std::array<float, 2> yBounds, std::array<float, 2> zBounds, std::array<int, 3> divisions) {
    Vector3f scale = {xBounds[1] - xBounds[0], yBounds[1] - yBounds[0], zBounds[1] - zBounds[0]};
    volume = Volume(divisions[0], divisions[1], divisions[2], scale.x, scale.z, scale.y);
    volume.position = {xBounds[0], yBounds[0], zBounds[0]};

    for(int ix = 0; ix < divisions[0]; ix++){
        float x = xBounds[0] + scale.x * ix / divisions[0];
        for(int iy = 0; iy < divisions[1]; iy++){
            float y = yBounds[0] + scale.y * iy / divisions[1];
            for(int iz = 0; iz < divisions[2]; iz++){
                float z = zBounds[0] + scale.z * iz / divisions[2];
                std::array<float, 4> temp = func(x, y, z);
                std::array<uint8_t, 4> value;
                value[0] = (uint8_t) std::max(0.f, std::min(255.f, std::floor(255 * temp[0])));
                value[1] = (uint8_t) std::max(0.f, std::min(255.f, std::floor(255 * temp[1])));
                value[2] = (uint8_t) std::max(0.f, std::min(255.f, std::floor(255 * temp[2])));
                value[3] = (uint8_t) std::max(0.f, std::min(255.f, std::floor(255 * temp[3])));

                volume.setValue(ix, iy, iz, value[0], value[1], value[2], value[3]);
            }
        }
    }
}
