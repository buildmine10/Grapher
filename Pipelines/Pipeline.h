//
// Created by colli on 4/13/2022.
//

#ifndef GRAPHER_PIPELINE_H
#define GRAPHER_PIPELINE_H

#include <functional>
#include <vector>

#include <GL/glew.h>// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/freeglut.h>

class Pipeline {
protected:
    static void addShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);

    static bool isInitialized;
    static unsigned int windowWidth;
    static unsigned int windowHeight;

    static void displayCallback();

    static std::vector<std::function<void()>> displayCallbacks;

public:

    static void selectWindow(const int& window);
    static int makeWindow(const int& width, const int& height, const std::string& name);
    //static void compileShaders(std::string vertexShaderFile, std::string fragmentShaderFile);

    static unsigned long long addDisplayCallback(const std::function<void()>& function);
    static float getAspectRatio();
    static unsigned int getWindowWidth();
    static unsigned int getWindowHeight();
};


#endif //GRAPHER_PIPELINE_H
