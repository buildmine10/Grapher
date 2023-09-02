//
// Created by colli on 4/14/2022.
//

#ifndef GRAPHER_LINE_H
#define GRAPHER_LINE_H

#include <vector>
#include <array>
#include "../Math/Vector3.h"
#include "../Math/TransformationMatrix.h"

class Line {
public:
    std::vector<Vector3f> vertexInfo;

    Vector3f& getVertex(const int& index);
    Vector3f& getColor(const int& index);

    void addVertex(const float& x, const float& y, const float& z, const float& r, const float& g, const float& b);
    void addVertex(const float& x, const float& y, const float& z);

    void printVertices();
    void printColors();
    void applyTransformation(const TransformationMatrix& matrix);

};


#endif //GRAPHER_LINE_H
