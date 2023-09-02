//
// Created by colli on 2/24/2022.
//

#ifndef INC_3DRENDERING_TRANSFORMATIONMATRIX_H
#define INC_3DRENDERING_TRANSFORMATIONMATRIX_H

#include "Matrix4.h"
#include "Vector3.h"

struct __attribute__ ((__packed__)) TransformationMatrix : public Matrix4<float>{
    TransformationMatrix();
    TransformationMatrix(const Matrix4<float>& other);

    void reset();
    void setOffset(const float& x, const float& y, const float& z);
    void setRotationExtrinsic(const float& x, const float& y, const float& z);
    void setRotationIntrinsic(const float& x, const float& y, const float& z);
    void applyScale(const float& scale);
    void applyPerspective(const float& fov, const float& aspectRatio, const float& near = 0.1, const float& far = 10);

    void applyTransformation(Vector3f& vector) const;

    TransformationMatrix& operator=(const Matrix4f& other);
};






#endif //INC_3DRENDERING_TRANSFORMATIONMATRIX_H
