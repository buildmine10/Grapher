//
// Created by colli on 4/14/2022.
//

#include "Surface.h"
#include <cmath>
#include <iostream>

Surface::Surface(std::function<float(float, float)> func, std::array<double, 2> xBounds, std::array<double, 2> yBounds, int numberOfPoints) {
    int size = (int)std::sqrt(numberOfPoints);
    mesh = Mesh::generatePlane(size, size);

    float xRange = xBounds[1] - xBounds[0];
    float yRange = yBounds[1] - yBounds[0];



    for(int i = 0; i < mesh.vertexInfo.size(); i += 2){
        mesh.vertexInfo[i].x = (mesh.vertexInfo[i].x / (size - 1)) * xRange + xBounds[0];
        mesh.vertexInfo[i].y = (mesh.vertexInfo[i].y / (size - 1)) * yRange + yBounds[0];
        const float& x = mesh.vertexInfo[i].x;
        const float& y = mesh.vertexInfo[i].y;

        mesh.vertexInfo[i].z = func(x, y);

        double dX;
        double dY;

        {
            double pX = func(x + 0.001, y);
            double nX = func(x - 0.001, y);

            double pY = func(x, y + 0.001);
            double nY = func(x, y - 0.001);

            dX = (pX - nX) / 0.002;
            dY = (pY - nY) / 0.002;
        }

        Vector3f normal = Vector3f(
                dX,dY,-1
        );


        normal /= -normal.magnitude();
        //normal.print();
        normal += {1, 1, 1};
        normal /= 2.f;

        mesh.vertexInfo[i + 1] = normal;
    }


}

Surface::Surface(std::function<Vector3f(float, float)> func, std::array<double, 2> uBounds, std::array<double, 2> vBounds, int numberOfPoints) {
    int size = (int)std::sqrt(numberOfPoints);
    mesh = Mesh::generatePlane(size, size);

    float uRange = uBounds[1] - uBounds[0];
    float vRange = vBounds[1] - vBounds[0];



    for(int i = 0; i < mesh.vertexInfo.size(); i += 2){
        const float& u = (mesh.vertexInfo[i].x / (size - 1)) * uRange + uBounds[0];
        const float& v = (mesh.vertexInfo[i].y / (size - 1)) * vRange + vBounds[0];

        mesh.vertexInfo[i] = func(u, v);//position

        Vector3f dU;
        Vector3f dV;

        {
            Vector3f pU = func(u + 0.001, v);
            Vector3f nU = func(u - 0.001, v);

            Vector3f pV = func(u, v + 0.001);
            Vector3f nV = func(u, v - 0.001);

            dU = (pU - nU) / 0.002;
            dV = (pV - nV) / 0.002;
        }

        Vector3f normal = dU.cross(dV);


        normal /= normal.magnitude();
        //std::cout << normal.x << ", " << normal.y << ", " << normal.z << std::endl;
        normal += {1, 1, 1};
        normal /= 2.f;

        mesh.vertexInfo[i + 1] = normal;//color
    }


}
