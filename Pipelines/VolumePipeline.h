//
// Created by colli on 5/20/2022.
//

#ifndef GRAPHER_VOLUMEPIPELINE_H
#define GRAPHER_VOLUMEPIPELINE_H
#include "Pipeline.h"
#include "../Math/Vector3.h"
#include "../Math/TransformationMatrix.h"
#include "../Renderables/Volume.h"
#include "../Camera.h"

class VolumePipeline : public Pipeline {
private:
    static const std::array<Vector3f, 8> volumeCubeVertices;
    static const std::array<int, 36> volumeCubeTris;

    static GLuint shaderProgram;

    static GLuint VBO;
    static GLuint IBO;
    static GLuint texture3D;

    static GLuint gPositionLocation;
    static GLint gTransformLocation;

    static GLint gVolumePositionLocation;
    static GLint gVolumeScaleLocation;
    static GLint gRayTransformLocation;
    static GLint gCameraPositionLocation;
    static GLint gWindowSizeLocation;
    static GLint gVolumeDivisionsLocation;

    static void findShaderVariables(const GLuint& ShaderProgram);

public:

    static void draw(const Volume& volume, Camera& camera);
    static void compileShaders(std::string vertexShaderFile, std::string fragmentShaderFile);

    static int makeWindow(const int& width, const int& height, const std::string& name) = delete;
    static void selectWindow(const int& window) = delete;
    static unsigned long long addDisplayCallback(const std::function<void()>& function) = delete;

};


#endif //GRAPHER_VOLUMEPIPELINE_H
