//
// Created by colli on 4/14/2022.
//

#include "Line.h"

Vector3f& Line::getVertex(const int& index) {
    if(index % 2 == 0 && index < vertexInfo.size()){
        return vertexInfo[index * 2];
    }else{
        throw std::runtime_error("Tried to get a vertex that doesn't exist");
    }
}

Vector3f &Line::getColor(const int& index) {
    if(index % 2 == 0 && index < vertexInfo.size()){
        return vertexInfo[index * 2 + 1];
    }else{
        throw std::runtime_error("Tried to get a color from vertex that doesn't exist");
    }
}

void Line::addVertex(const float& x, const float& y, const float& z, const float& r, const float& g, const float& b) {
    vertexInfo.emplace_back(x, y, z);
    vertexInfo.emplace_back(r, g, b);
}

void Line::addVertex(const float &x, const float &y, const float &z) {
    addVertex(x, y, z, rand() % 1000 / 1000.0, rand() % 1000 / 1000.0, rand() % 1000 / 1000.0);
}


void Line::printVertices() {
    for(int i = 0; i < vertexInfo.size(); i += 2){
        vertexInfo[i].print();
    }
}

void Line::applyTransformation(const TransformationMatrix &matrix) {
    for(int i = 0; i < vertexInfo.size(); i += 2){
        matrix.applyTransformation(vertexInfo[i]);
    }
}

void Line::printColors() {
    for(int i = 0; i < vertexInfo.size(); i += 2){
        vertexInfo[i + 1].print();
    }
}