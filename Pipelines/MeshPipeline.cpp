//
// Created by colli on 4/13/2022.
//

#include "MeshPipeline.h"
#include <fstream>

GLuint MeshPipeline::shaderProgram{};

GLuint MeshPipeline::gPositionLocation{};
GLuint MeshPipeline::gTransformLocation{};
GLint MeshPipeline::gColorLocation{};
GLuint MeshPipeline::gOpacityLocation{};
GLuint MeshPipeline::VBO{};
GLuint MeshPipeline::IBO{};

void MeshPipeline::draw(const Mesh &mesh, const TransformationMatrix &transformation, const float& opacity) {
    glUseProgram(shaderProgram);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);//Declares that the buffer VBO is an array buffer
    glBufferData(GL_ARRAY_BUFFER, mesh.vertexInfo.size() * sizeof(Vector3f), mesh.vertexInfo.data(), GL_STATIC_DRAW);//assigns the data that goes in the buffer VBO

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);//Declares that the buffer VBO is an array buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.vertexOrder.size() * sizeof(int), mesh.vertexOrder.data(), GL_STATIC_DRAW);//assigns the data that goes in the buffer VBO



    glEnableVertexAttribArray(gPositionLocation);//enables access to vertex attribute Position
    glVertexAttribPointer(gPositionLocation, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(Vector3f), nullptr);

    glEnableVertexAttribArray(gColorLocation);
    glVertexAttribPointer(gColorLocation, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(Vector3f), (void*)(sizeof(Vector3f)));

    glUniformMatrix4fv(gTransformLocation, 1, GL_TRUE, &transformation.data[0][0]);
    glUniform1f(gOpacityLocation, opacity);

    glDrawElements(GL_TRIANGLE_STRIP, mesh.vertexOrder.size(), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(gPositionLocation);//a safety precaution
    glDisableVertexAttribArray(gColorLocation);//a safety precaution
}


void MeshPipeline::drawWireframe(const Mesh &mesh, const TransformationMatrix &transformation, const float& opacity) {
    glUseProgram(shaderProgram);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);//Declares that the buffer VBO is an array buffer
    glBufferData(GL_ARRAY_BUFFER, mesh.vertexInfo.size() * sizeof(Vector3f), mesh.vertexInfo.data(), GL_STATIC_DRAW);//assigns the data that goes in the buffer VBO

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);//Declares that the buffer VBO is an array buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.vertexOrder.size() * sizeof(int), mesh.vertexOrder.data(), GL_STATIC_DRAW);//assigns the data that goes in the buffer VBO



    glEnableVertexAttribArray(gPositionLocation);//enables access to vertex attribute Position
    glVertexAttribPointer(gPositionLocation, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(Vector3f), nullptr);

    glEnableVertexAttribArray(gColorLocation);
    glVertexAttribPointer(gColorLocation, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(Vector3f), (void*)(sizeof(Vector3f)));

    glUniformMatrix4fv(gTransformLocation, 1, GL_TRUE, &transformation.data[0][0]);
    glUniform1f(gOpacityLocation, opacity);

    glDrawElements(GL_LINE_STRIP, mesh.vertexOrder.size(), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(gPositionLocation);//a safety precaution
    glDisableVertexAttribArray(gColorLocation);//a safety precaution
}

void MeshPipeline::findShaderVariables(const GLuint &ShaderProgram) {
    gPositionLocation = glGetAttribLocation(ShaderProgram, "Position");
    if(gPositionLocation == 0xFFFFFFFF){//checks if gPositionLocation is -1
        throw std::runtime_error("Position was not found in the shader program.");
    }

    gTransformLocation = glGetUniformLocation(ShaderProgram, "Transform");
    if(gTransformLocation == 0xFFFFFFFF){//checks if gScaleLocation is -1
        throw std::runtime_error("Transform was not found in the shader program.");
    }

    gColorLocation = glGetAttribLocation(ShaderProgram, "Color");
    if(gColorLocation == 0xFFFFFFFF){//checks if gScaleLocation is -1
        throw std::runtime_error("Color was not found in the shader program.");
    }

    gOpacityLocation = glGetUniformLocation(ShaderProgram, "Opacity");
    if(gOpacityLocation == 0xFFFFFFFF){//checks if gScaleLocation is -1
        throw std::runtime_error("Opacity was not found in the shader program.");
    }
}

void MeshPipeline::compileShaders(std::string vertexShaderFile, std::string fragmentShaderFile) {
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
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    findShaderVariables(shaderProgram);

}


