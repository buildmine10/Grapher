//
// Created by colli on 4/13/2022.
//

#include "Pipeline.h"

#include <stdio.h>
#include <fstream>
#include <cmath>
#include <sstream>

bool Pipeline::isInitialized = false;
unsigned int Pipeline::windowWidth = 0;
unsigned int Pipeline::windowHeight = 0;

std::vector<std::function<void()>> Pipeline::displayCallbacks{};


void Pipeline::addShader(GLuint ShaderProgram, const char *pShaderText, GLenum ShaderType) {
    GLuint ShaderObj = glCreateShader(ShaderType);//makes a shader

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }

    //loads the shader source code
    const GLchar* p[1];//an array of character pointers (an array of strings)
    p[0] = pShaderText;//puts the shader source code into the array of strings

    GLint Lengths[1];//a list of the lengths of each string
    Lengths[0] = (GLint)strlen(pShaderText);

    glShaderSource(ShaderObj, 1, p, Lengths);//specifies the shader source

    glCompileShader(ShaderObj);//compiles the shader

    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success) {//reports what went wrong with compilation
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);//adds the newly compiled shader to the program
}
/*
void Pipeline::compileShaders(std::string vertexShaderFile, std::string fragmentShaderFile) {
    shaderProgram = glCreateProgram();
    if (shaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    std::string vs, fs;

    std::ifstream file(vertexShaderFile);
    std::stringstream buffer;
    buffer << file.rdbuf();
    vs = buffer.str();
    file.close();

    addShader(shaderProgram, vs.c_str(), GL_VERTEX_SHADER);


    file.open(fragmentShaderFile);
    buffer = std::stringstream();
    buffer << file.rdbuf();
    fs = buffer.str();
    //I could check if it fails

    addShader(shaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glUseProgram(shaderProgram);


}
 */

void Pipeline::selectWindow(const int& window) {
    glutSetWindow(window);


    windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
}

int Pipeline::makeWindow(const int& width, const int& height, const std::string& name) {
    if(!Pipeline::isInitialized){
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowSize(width, height);
        glutInitWindowPosition(100, 100);
        int window = glutCreateWindow(name.c_str());

        GLenum res = glewInit();//all glut initialization must happen before this
        if (res != GLEW_OK)
        {
            fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
            throw std::runtime_error("Glew didn't initialize properly");
        }

        isInitialized = true;

        glutDisplayFunc(displayCallback);

        return window;
    }else{
        glutInitWindowSize(width, height);
        glutInitWindowPosition(100, 100);
        return glutCreateWindow(name.c_str());
    }
}

void Pipeline::displayCallback() {
    windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clears the buffer

    for(auto func : displayCallbacks){
        func();
    }

    glutSwapBuffers();
}

unsigned long long Pipeline::addDisplayCallback(const std::function<void()>& function) {
    displayCallbacks.push_back(function);
    return displayCallbacks.size() - 1;
}

float Pipeline::getAspectRatio() {
    return (float)windowWidth / windowHeight;
}

unsigned int Pipeline::getWindowHeight(){
    return windowHeight;
}

unsigned int Pipeline::getWindowWidth() {
    return windowWidth;
}
