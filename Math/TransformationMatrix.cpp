//
// Created by colli on 2/24/2022.
//

#include "TransformationMatrix.h"
#include <cmath>

TransformationMatrix::TransformationMatrix() {
    this->data[0][0] = 1.0f;
    this->data[1][1] = 1.0f;
    this->data[2][2] = 1.0f;
    this->data[3][3] = 1.0f;

}

void TransformationMatrix::setOffset(const float& x, const float& y, const float& z) {
    this->data[0][3] = x;
    this->data[1][3] = y;
    this->data[2][3] = z;
}

void TransformationMatrix::setRotationExtrinsic(const float& x, const float& y, const float& z) {
    TransformationMatrix rotation;
    {
        Matrix4f Z;
        Z.data[0][0] = cosf(z); Z.data[0][1] = -sinf(z);
        Z.data[1][0] = sinf(z); Z.data[1][1] = cosf(z);
        Z.data[2][2] = 1; Z.data[3][3] = 1;
        rotation *= Z;
    }
    {
        Matrix4f Y;
        Y.data[0][0] = cosf(y); Y.data[0][2] = -sinf(y);
        Y.data[2][0] = sinf(y); Y.data[2][2] = cosf(y);
        Y.data[1][1] = 1; Y.data[3][3] = 1;
        rotation *= Y;
    }
    {
        Matrix4f X;
        X.data[1][1] = cosf(x); X.data[1][2] = -sinf(x);
        X.data[2][1] = sinf(x); X.data[2][2] = cosf(x);
        X.data[0][0] = 1; X.data[3][3] = 1;
        rotation *= X;
    }

    for(uint8_t i = 0; i < 3; i++){
        for(uint8_t j = 0; j < 3; j++){
            data[i][j] = rotation.data[i][j];
        }
    }
}

void TransformationMatrix::setRotationIntrinsic(const float& x, const float& y, const float& z) {
    TransformationMatrix rotation;
    {
        Matrix4f X;
        X.data[1][1] = cosf(x); X.data[1][2] = -sinf(x);
        X.data[2][1] = sinf(x); X.data[2][2] = cosf(x);
        X.data[0][0] = 1; X.data[3][3] = 1;
        rotation *= X;
    }
    {
        Matrix4f Y;
        Y.data[0][0] = cosf(y); Y.data[0][2] = -sinf(y);
        Y.data[2][0] = sinf(y); Y.data[2][2] = cosf(y);
        Y.data[1][1] = 1; Y.data[3][3] = 1;
        rotation *= Y;
    }
    {
        Matrix4f Z;
        Z.data[0][0] = cosf(z); Z.data[0][1] = -sinf(z);
        Z.data[1][0] = sinf(z); Z.data[1][1] = cosf(z);
        Z.data[2][2] = 1; Z.data[3][3] = 1;
        rotation *= Z;
    }

    for(uint8_t i = 0; i < 3; i++){
        for(uint8_t j = 0; j < 3; j++){
            data[i][j] = rotation.data[i][j];
        }
    }
}

void TransformationMatrix::applyScale(const float& scale) {
    for(uint8_t i = 0; i < 3; i++){
        for(uint8_t j = 0; j < 3; j++){
            data[i][j] *= scale;
        }
    }
}

void TransformationMatrix::applyTransformation(Vector3f &vector) const{
    Vector3f temp;
    temp.x = vector.x * data[0][0] + vector.y * data[0][1] + vector.z * data[0][2] + data[0][3];
    temp.y = vector.x * data[1][0] + vector.y * data[1][1] + vector.z * data[1][2] + data[1][3];
    temp.z = vector.x * data[2][0] + vector.y * data[2][1] + vector.z * data[2][2] + data[2][3];
    vector = temp;
}

void TransformationMatrix::applyPerspective(const float &fov, const float &aspectRatio, const float& near, const float& far) {
    float tanHalfFOV = std::tan(fov / 2);
    float range = near - far;

    //std::cout << tanHalfFOV << std::endl;
    //the z might need to be flipped
    //

    Matrix4f perspective(
            {1.f / (tanHalfFOV * aspectRatio), 0.f, 0.f, 0},//there is a negative because of the way z-buffering works. The z-buffer makes the screen left-handed, whereas everything else is right-handed. Flipping x fixes this.
            {0.f, (-near - far) / range, 0.f, 2.f * far * near / range},
            {0.f, 0.f, 1.f / tanHalfFOV, 0},
            {0.f, 1.f, 0.f, 0.f}
    );


    perspective *= *this;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            this->data[i][j] = perspective.data[i][j];
        }
    }
}

void TransformationMatrix::reset() {
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            this->data[i][j] = i == j;
        }
    }
}

TransformationMatrix &TransformationMatrix::operator=(const Matrix4f &other) {
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            this->data[i][j] = other.data[i][j];
        }
    }
    return *this;
}

TransformationMatrix::TransformationMatrix(const Matrix4<float> &other) {
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            this->data[i][j] = other.data[i][j];
        }
    }
}

