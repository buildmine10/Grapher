//
// Created by colli on 4/14/2022.
//

#ifndef GRAPHER_CAMERA_H
#define GRAPHER_CAMERA_H

#include "Math/TransformationMatrix.h"
#include "Math/Vector3.h"
#include "Plots/Surface.h"
#include "Plots/Curve.h"
#include "Plots/ColorField.h"

#define _USE_MATH_DEFINES

class Camera {
private:
    float fov = M_PI_2;
    float farPlane = 1000;
    float nearPlane = 0.1;//I don't recommend shrinking this further than 0.1

public:

    void draw(const Surface& surface, const float& opacity = 1);
    void drawWireframe(const Surface& surface, const float& opacity = 1);

    void draw(const Curve& curve, const float& opacity = 1);

    void draw(const Line& curve, const float& opacity = 1);

    void draw(const ColorField& field);


    TransformationMatrix getTransformation();
    TransformationMatrix getRotationMatrix();
    TransformationMatrix getVolumeMatrix();

    Vector3f position;
    float angleTheta = 0;//horizontal look
    float anglePhi = 0;//vertical look

    float getFOV() const;
};


#endif //GRAPHER_CAMERA_H
