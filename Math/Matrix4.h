//
// Created by colli on 2/24/2022.
//

#ifndef INC_3DRENDERING_MATRIX4_H
#define INC_3DRENDERING_MATRIX4_H

#include <stdexcept>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <array>
#include "Vector3.h"


template<class T>
struct __attribute__ ((__packed__)) Matrix4 {
    T data[4][4];

    Matrix4();
    explicit Matrix4(std::array<T, 4> row0, std::array<T, 4> row1, std::array<T, 4> row2, std::array<T, 4> row3);

    Matrix4<T> operator* (const Matrix4<T>& other);
    Matrix4<T>& operator*= (const Matrix4<T>& other);
    Matrix4<T> operator* (const double& scalar);
    Matrix4<T>& operator*= (const double& scalar);
};

template<class T>
Matrix4<T> Matrix4<T>::operator*(const Matrix4<T> &other) {
    Matrix4<T> output;
    for(uint8_t i = 0; i < 4; i++){//y
        for(uint8_t j = 0; j < 4; j++){//x
            //std::cout << (int)j << ", " << (int)i << std::endl;
            output.data[i][j] = 0;
            for(uint8_t k = 0; k < 4; k++){
                output.data[i][j] += data[i][k] * other.data[k][j];
                //std::cout << data[i][k] << " " << other.data[k][j] << std::endl;
            }
            //std::cout << std::endl;
        }
    }
    return output;
}

template<class T>
Matrix4<T> &Matrix4<T>::operator*=(const Matrix4<T> &other) {
    Matrix4<T> temp;
    for(uint8_t i = 0; i < 4; i++){
        for(uint8_t j = 0; j < 4; j++){
            temp.data[i][j] = 0;
            for(uint8_t k = 0; k < 4; k++){
                temp.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    for(uint8_t i = 0; i < 4; i++){
        for(uint8_t j = 0; j < 4; j++){
            data[i][j] = temp.data[i][j];
        }
    }
    return *this;
}

template<class T>
Matrix4<T> Matrix4<T>::operator*(const double &scalar) {
    Matrix4<T> output;
    for(uint8_t i = 0; i < 4; i++){
        for(uint8_t j = 0; j < 4; j++){
            output.data[i][j] = data[i][j] * scalar;
        }
    }
    return output;
}

template<class T>
Matrix4<T> &Matrix4<T>::operator*=(const double &scalar) {
    for(uint8_t i = 0; i < 4; i++){
        for(uint8_t j = 0; j < 4; j++){
            data[i][j] *= scalar;
        }
    }
    return *this;
}

template<class T>
Matrix4<T>::Matrix4() {
    for(uint8_t i = 0; i < 4; i++){
        for(uint8_t j = 0; j < 4; j++){
            data[i][j] = 0;
            if(i == j){
                data[i][j] = 1;
            }
        }
    }
}

template<class T>
Matrix4<T>::Matrix4(std::array<T, 4> row0, std::array<T, 4> row1, std::array<T, 4> row2, std::array<T, 4> row3) {
    for(int j = 0; j < 4; j++){
        this->data[0][j] = row0[j];
    }
    for(int j = 0; j < 4; j++){
        this->data[1][j] = row1[j];
    }
    for(int j = 0; j < 4; j++){
        this->data[2][j] = row2[j];
    }
    for(int j = 0; j < 4; j++){
        this->data[3][j] = row3[j];
    }
}



typedef Matrix4<float> Matrix4f;
typedef Matrix4<int> Matrix4i;
typedef Matrix4<double> Matrix4d;

#endif //INC_3DRENDERING_MATRIX4_H
