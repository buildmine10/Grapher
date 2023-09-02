//
// Created by colli on 4/13/2022.
//

#ifndef GRAPHER_MESHPIPELINE_H
#define GRAPHER_MESHPIPELINE_H

#include "Pipeline.h"
#include "../Renderables/Mesh.h"
#include "../Math/TransformationMatrix.h"

class MeshPipeline : public Pipeline {
protected:
    static GLuint shaderProgram;

    static GLuint VBO;
    static GLuint IBO;

    static GLuint gPositionLocation;
    static GLuint gTransformLocation;
    static GLint gColorLocation;
    static GLuint gOpacityLocation;

    static void findShaderVariables(const GLuint& ShaderProgram);

public:
    static void draw(const Mesh& mesh, const TransformationMatrix& transformation, const float& opacity = 1);
    static void drawWireframe(const Mesh& mesh, const TransformationMatrix& transformation, const float& opacity = 1);


    static int makeWindow(const int& width, const int& height, const std::string& name) = delete;
    static void selectWindow(const int& window) = delete;
    static void compileShaders(std::string vertexShaderFile, std::string fragmentShaderFile);
    static unsigned long long addDisplayCallback(const std::function<void()>& function) = delete;


};


#endif //GRAPHER_MESHPIPELINE_H
