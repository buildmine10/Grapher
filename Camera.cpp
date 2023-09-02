//
// Created by colli on 4/14/2022.
//

#include "Camera.h"
#include "Pipelines/MeshPipeline.h"
#include "Pipelines/LinePipeline.h"
#include "Pipelines/VolumePipeline.h"
#include <cmath>

void Camera::draw(const Surface &surface, const float& opacity) {

    MeshPipeline::draw(surface.mesh, getTransformation(), opacity);
}

void Camera::drawWireframe(const Surface &surface, const float& opacity) {
    MeshPipeline::drawWireframe(surface.mesh, getTransformation(), opacity);
}

TransformationMatrix Camera::getTransformation() {
    TransformationMatrix transform;
    TransformationMatrix cameraTransform;
    cameraTransform.setOffset(-position.x, -position.y, -position.z);
    transform = cameraTransform * transform;

    cameraTransform.reset();
    cameraTransform.setRotationIntrinsic(-anglePhi, 0, -angleTheta);
    transform = cameraTransform * transform;
    //position.print();

    transform.applyPerspective(fov, MeshPipeline::getAspectRatio(), nearPlane, farPlane);//the far and near distances must be this
    return transform;
}

void Camera::draw(const Curve &curve, const float& opacity) {
    LinePipeline::draw(curve.line, getTransformation(), opacity);
}

void Camera::draw(const Line &curve, const float& opacity) {
    LinePipeline::draw(curve, getTransformation(), opacity);
}

void Camera::draw(const ColorField &field) {
    VolumePipeline::draw(field.volume, *this);
}

TransformationMatrix Camera::getRotationMatrix() {
    TransformationMatrix transform;
    transform.setRotationIntrinsic(-anglePhi, 0, -angleTheta);
    return transform;
}

TransformationMatrix Camera::getVolumeMatrix() {
    TransformationMatrix rotation;

    TransformationMatrix fieldOfView = Matrix4f(
            {std::tan(fov / 2) * Pipeline::getAspectRatio(), 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, std::tan(fov / 2), 0},
            {0, 0, 0, 1}
    );
    rotation.setRotationExtrinsic(anglePhi, 0, angleTheta);
    return rotation * fieldOfView;
}

float Camera::getFOV() const {
    return fov;
}


