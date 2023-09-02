//
// Created by colli on 4/14/2022.
//

#include "Curve.h"

Curve::Curve(std::function<float(float)> func, double lowerBound, double upperBound, int numberOfPoints) {
    double deltaX = (upperBound - lowerBound) / (numberOfPoints - 1);

    for(double x = lowerBound; x <= upperBound; x += deltaX){
        float dX;

        {
            double pX = func(x + 0.001);
            double nX = func(x - 0.001);

            dX = (float)(pX - nX) / 0.002f;
        }

        Vector3f direction(
                1, 0, dX
        );



        direction /= direction.magnitude();
        direction += {1, 1, 1};
        direction /= 2.f;

        //auto temp = direction * 255;
        //std::cout << "rgb(" << std::floor(temp.x) << ", " << std::floor(temp.y) << ", " << std::floor(temp.z) << ")" << std::endl;

        line.addVertex(x, 0, func(x), direction.x, direction.y, direction.z);
        if(lowerBound == upperBound){
            break;
        }
    }

    if(lowerBound == upperBound){
        line.addVertex(line.vertexInfo[0].x,line.vertexInfo[0].y,line.vertexInfo[0].z,line.vertexInfo[1].x,line.vertexInfo[1].y,line.vertexInfo[1].z);
    }
}

Curve::Curve(std::function<Vector3f(float)> func, double lowerBound, double upperBound, int numberOfPoints) {
    double deltaT = (upperBound - lowerBound) / (numberOfPoints - 1);

    for(double t = lowerBound; t <= upperBound; t += deltaT){
        Vector3f direction;

        {
            Vector3f pT = func(t + 0.001);
            Vector3f nT = func(t - 0.001);

            direction = (pT - nT) / 0.002f;
        }



        direction /= direction.magnitude();
        //direction.print();
        //std::cout << normal.t << ", " << normal.y << ", " << normal.z << std::endl;
        direction += {1, 1, 1};
        direction /= 2.f;

        //std::cout << 255 * normal.t << ", " << 255 * normal.y << ", " << 255 * normal.z << std::endl;
        //std::cout << std::endl;

        Vector3f position = func(t);
        line.addVertex(position.x, position.y, position.z, direction.x, direction.y, direction.z);

        if(lowerBound == upperBound){
            break;
        }
    }
    if(lowerBound == upperBound){
        line.addVertex(line.vertexInfo[0].x,line.vertexInfo[0].y,line.vertexInfo[0].z,line.vertexInfo[1].x,line.vertexInfo[1].y,line.vertexInfo[1].z);
    }
}

Curve::Curve(std::function<Vector3f(float)> func, double lowerBound, double upperBound, double pointDensity) {
    for(double x = lowerBound; x <= upperBound; x += pointDensity){
        Vector3f direction;

        {
            Vector3f pX = func(x + 0.001);
            Vector3f nX = func(x - 0.001);

            direction = (pX - nX) / 0.002f;
        }



        direction /= direction.magnitude();
        //std::cout << normal.x << ", " << normal.y << ", " << normal.z << std::endl;
        direction += {1, 1, 1};
        direction /= 2.f;

        //std::cout << 255 * normal.x << ", " << 255 * normal.y << ", " << 255 * normal.z << std::endl;
        //std::cout << std::endl;

        Vector3f position = func(x);
        line.addVertex(position.x, position.y, position.z, direction.x, direction.y, direction.z);
    }
}
