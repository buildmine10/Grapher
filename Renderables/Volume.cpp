//
// Created by colli on 5/17/2022.
//

#include "Volume.h"
#include <stdexcept>
#include <algorithm>
#include <cmath>

bool Volume::boundsCheck(const size_t &x, const size_t &y, const size_t &z) const {
    return x >= 0 && x < iWidth && y >= 0 && y < iDepth && z >= 0 && z < iHeight;
}

void Volume::boundsCheckWithError(const size_t &x, const size_t &y, const size_t &z) const {
    if(!boundsCheck(x, y, z)){
        throw std::runtime_error("Attempted to access part of data that is out of bounds");
    }
}

void Volume::setValue(size_t x, size_t y, size_t z, float r, float g, float b, float a) {
    boundsCheckWithError(x, y, z);
    int index = 4 * (z + y * iHeight + x * iHeight * iDepth);

    data[index] = r;
    data[index + 1] = g;
    data[index + 2] = b;
    data[index + 3] = a;
}

Volume::Volume(size_t iWidth, size_t iHeight, size_t iDepth, float width, float height, float depth) {
    this->iWidth = iWidth;
    this->iHeight = iHeight;
    this->iDepth = iDepth;
    this->width = width;
    this->height = height;
    this->depth = depth;

    this->data = new uint8_t[iWidth * iHeight * iDepth * 4];
    for(int i = 0; i < iWidth * iHeight * iDepth * 4; i++){
        this->data[i] = rand() % 256;
    }
}

Volume::Volume(size_t iWidth, size_t iHeight, size_t iDepth) {
    this->iWidth = iWidth;
    this->iHeight = iHeight;
    this->iDepth = iDepth;
    this->width = iWidth;
    this->height = iHeight;
    this->depth = iDepth;

    this->data = new uint8_t[iWidth * iHeight * iDepth * 4];
    for(int i = 0; i < iWidth * iHeight * iDepth * 4; i++){
        this->data[i] = rand() % 256;
    }
}

Volume &Volume::operator=(const Volume &other) {
    delete[] this->data;

    iWidth = other.iWidth;
    iHeight = other.iHeight;
    iDepth = other.iDepth;

    width = other.width;
    height = other.height;
    depth = other.depth;

    this->data = new uint8_t[iWidth * iHeight * iDepth * 4];

    for(int i = 0; i < iWidth * iHeight * iDepth * 4; i++){
        this->data[i] = other.data[i];
    }



    position = other.position;

    return *this;
}





