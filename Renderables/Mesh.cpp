//
// Created by colli on 4/13/2022.
//

#include "Mesh.h"

Vector3f& Mesh::getVertex(const int& index) {
    if(index % 2 == 0 && index < vertexInfo.size()){
        return vertexInfo[index * 2];
    }else{
        throw std::runtime_error("Tried to get a vertex that doesn't exist");
    }
}

Vector3f &Mesh::getColor(const int& index) {
    if(index % 2 == 0 && index < vertexInfo.size()){
        return vertexInfo[index * 2 + 1];
    }else{
        throw std::runtime_error("Tried to get a color from vertex that doesn't exist");
    }
}

void Mesh::addVertex(const float& x, const float& y, const float& z, const float& r, const float& g, const float& b) {
    vertexInfo.emplace_back(x, y, z);
    vertexInfo.emplace_back(r, b, g);
}

void Mesh::addVertex(const float &x, const float &y, const float &z) {
    addVertex(x, y, z, rand() % 1000 / 1000.0, rand() % 1000 / 1000.0, rand() % 1000 / 1000.0);
}

Mesh Mesh::generatePlane(const int &width, const int &length) {
    Mesh output;

    for(int y = 0; y < length; y++){
        for(int x = 0; x < width; x++){
            output.addVertex(x, y, 0);
            //std::cout << "\t" << y * width + x << std::endl;
        }
    }

    for(int y = 0; y < length - 1; y++){
        //std::cout << y << std::endl;
        if(y % 2 == 0){
            for(int x = 0; x < width; x++){
                output.vertexOrder.push_back(y * width + x);
                output.vertexOrder.push_back((y + 1) * width + x);
            }
        }else{

            for(int x = width - 1; x >= 0; x--){
                //std::cout << "\t" << y * width + x << " " << (y + 1) * width + x << std::endl;
                output.vertexOrder.push_back(y * width + x);
                output.vertexOrder.push_back((y + 1) * width + x);
            }
        }
    }
    return output;
}

void Mesh::printVertices() {
    for(int i = 0; i < vertexInfo.size(); i += 2){
        vertexInfo[i].print();
    }
}

void Mesh::applyTransformation(const TransformationMatrix &matrix) {
    for(int i = 0; i < vertexInfo.size(); i += 2){
        matrix.applyTransformation(vertexInfo[i]);
    }
}

void Mesh::applyScale(const float &x, const float &y, const float &z) {
    for(int i = 0; i < vertexInfo.size(); i += 2){
        vertexInfo[i].x *= x;
        vertexInfo[i].y *= y;
        vertexInfo[i].z *= z;
    }
}

void Mesh::printColors() {
    for(int i = 0; i < vertexInfo.size(); i += 2){
        vertexInfo[i + 1].print();
    }
}



