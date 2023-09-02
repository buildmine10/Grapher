//
// Created by colli on 5/22/2022.
//

#ifndef GRAPHER_ISOSURFACE_H
#define GRAPHER_ISOSURFACE_H

#include <GL/glew.h>// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/freeglut.h>

class IsoSurface {
public:
    static GLuint shaderProgram;

public:
    void calculate();
    void generateShader();
};


#endif //GRAPHER_ISOSURFACE_H
