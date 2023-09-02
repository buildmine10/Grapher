//
// Created by colli on 4/13/2022.
//

#ifndef GRAPHER_MESH_H
#define GRAPHER_MESH_H
#include <vector>
#include <array>
#include "../Math/Vector3.h"
#include "../Math/TransformationMatrix.h"

class Mesh {
public:
    std::vector<Vector3f> vertexInfo;
    std::vector<int> vertexOrder;

    Vector3f& getVertex(const int& index);
    Vector3f& getColor(const int& index);

    void addVertex(const float& x, const float& y, const float& z, const float& r, const float& g, const float& b);
    void addVertex(const float& x, const float& y, const float& z);

    static Mesh generatePlane(const int& width, const int& length);

    void printVertices();
    void printColors();
    void applyTransformation(const TransformationMatrix& matrix);
    void applyScale(const float& x, const float& y, const float& z);
};


#endif //GRAPHER_MESH_H
