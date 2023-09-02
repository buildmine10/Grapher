//
// Created by colli on 5/17/2022.
//

#ifndef GRAPHER_VOLUME_H
#define GRAPHER_VOLUME_H
#include <vector>
#include "../Math/Vector3.h"

//x = width
//y = depth
//z = height

//values range from 0 - 1

class Volume {
private:
    //std::vector<std::vector<std::vector<std::array<float, 4>>>> data;//[x][y][z][channel]

    inline bool boundsCheck(const size_t& x, const size_t& y, const size_t& z) const;
    void boundsCheckWithError(const size_t& x, const size_t& y, const size_t& z) const;

public:
    uint8_t* data;

    size_t iWidth = 0;
    size_t iHeight = 0;
    size_t iDepth = 0;
    float width = 0;
    float height = 0;
    float depth = 0;

    Vector3f position = {0, 0, 0};

    explicit Volume(size_t iWidth, size_t iHeight, size_t iDepth, float width, float height, float depth);
    explicit Volume(size_t iWidth = 0, size_t iHeight = 0, size_t iDepth = 0);

    void setValue(size_t x, size_t y, size_t z, float r, float g, float b, float a);

    Volume& operator=(const Volume& other);
};


#endif //GRAPHER_VOLUME_H
