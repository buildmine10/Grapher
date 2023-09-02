//
// Created by Collin on 1/7/2022.
//

#ifndef MATHSTUFF_VECTOR3_H
#define MATHSTUFF_VECTOR3_H

#include <stdexcept>
#include <cmath>
#include <iostream>
#include <iomanip>

template<class T>
//the attribute ensures that the struct takes up only the space needed for storage
struct __attribute__ ((__packed__)) Vector3 {
    T x = 0, y = 0, z = 0;

    Vector3();
    Vector3(const Vector3<T>& vector);
    Vector3(T x, T y, T z);


    Vector3<T>& operator=(const Vector3<T>& other);

    Vector3<T> operator+(const Vector3<T>& other) const;
    Vector3<T> operator-(const Vector3<T>& other) const;
    T operator*(const Vector3<T>& other) const;
    Vector3<T> cross(const Vector3<T>& other) const;

    Vector3<T> operator*(const T& value) const;
    Vector3<T> operator/(const T& value) const;


    Vector3<T>& operator+=(const Vector3<T>& other);
    Vector3<T>& operator-=(const Vector3<T>& other);
    Vector3<T>& operator*=(const T& value);
    Vector3<T>& operator/=(const T& value);

    Vector3<T> multiplyElementWise(const Vector3<T>& other) const;
    bool lessThanElementWise(const Vector3<T>& other) const;//true is all elements are less


    T magnitude() const;

    void print() const;

    Vector3<T> normalize() const;
};

template<class T>
Vector3<T>::Vector3() {
    x = y = z = 0;
}

template<class T>
Vector3<T>::Vector3(const Vector3<T> &vector) {
    x = vector.x;
    y = vector.y;
    z = vector.z;
}

template<class T>
Vector3<T>::Vector3(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template<class T>
Vector3<T> &Vector3<T>::operator=(const Vector3<T> &other) {
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

template<class T>
Vector3<T> Vector3<T>::operator+(const Vector3<T> &other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

template<class T>
Vector3<T> Vector3<T>::operator-(const Vector3<T> &other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

template<class T>
T Vector3<T>::operator*(const Vector3<T> &other) const {
    return x * other.x + y * other.y + z * other.z;
}

template<class T>
Vector3<T> Vector3<T>::cross(const Vector3<T> &other) const {
    return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

template<class T>
Vector3<T> Vector3<T>::operator*(const T &value) const {
    return Vector3(value * x, value * y, value * z);
}

template<class T>
Vector3<T> Vector3<T>::operator/(const T &value) const {
    return Vector3(x / value, y / value, z / value);
}

template<class T>
Vector3<T> &Vector3<T>::operator+=(const Vector3<T> &other) {
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

template<class T>
Vector3<T> &Vector3<T>::operator-=(const Vector3<T> &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

template<class T>
Vector3<T> &Vector3<T>::operator*=(const T &value) {
    x *= value;
    y *= value;
    z *= value;

    return *this;
}

template<class T>
Vector3<T> &Vector3<T>::operator/=(const T &value) {
    x /= value;
    y /= value;
    z /= value;

    return *this;
}

template<class T>
T Vector3<T>::magnitude() const {
    return std::sqrt(x*x + y*y + z*z);
}

template<class T>
void Vector3<T>::print() const {
    std::cout << std::fixed << std::setprecision(10) << x << ", " << y << ", " << z << std::endl;
}

template<class T>
Vector3<T> Vector3<T>::multiplyElementWise(const Vector3<T> &other) const {
    return Vector3(x * other.x, y * other.y, z * other.z);
}

template<class T>
bool Vector3<T>::lessThanElementWise(const Vector3<T> &other) const {
    return x < other.x && y < other.y && z < other.z;
}

template<class T>
Vector3<T> Vector3<T>::normalize() const {
    return *this / magnitude();
}


typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;
typedef Vector3<double> Vector3d;

#endif //MATHSTUFF_VECTOR3_H
