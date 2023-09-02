//
// Created by colli on 4/14/2022.
//

#ifndef GRAPHER_LINEPIPELINE_H
#define GRAPHER_LINEPIPELINE_H

#include "Pipeline.h"
#include "../Renderables/Line.h"
#include "../Math/TransformationMatrix.h"

class LinePipeline : public Pipeline {
private:
    static GLuint shaderProgram;

    static GLuint VBO;

    static GLuint gPositionLocation;
    static GLuint gTransformLocation;
    static GLuint gColorLocation;
    static GLuint gOpacityLocation;

    static void findShaderVariables(const GLuint& ShaderProgram);

public:
    static void draw(const Line& line, const TransformationMatrix& transformation, const float& opacity = 1);


    static int makeWindow(const int& width, const int& height, const std::string& name) = delete;
    static void selectWindow(const int& window) = delete;
    static void compileShaders(std::string vertexShaderFile, std::string fragmentShaderFile);
    static unsigned long long addDisplayCallback(const std::function<void()>& function) = delete;


};


#endif //GRAPHER_LINEPIPELINE_H
