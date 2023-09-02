//
// Created by colli on 4/14/2022.
//

#include "LinePipeline.h"
#include <fstream>

GLuint LinePipeline::shaderProgram{};

GLuint LinePipeline::gPositionLocation{};
GLuint LinePipeline::gTransformLocation{};
GLuint LinePipeline::gColorLocation{};
GLuint LinePipeline::gOpacityLocation{};
GLuint LinePipeline::VBO{};

void LinePipeline::draw(const Line &line, const TransformationMatrix &transformation, const float& opacity) {
    glUseProgram(shaderProgram);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);//Declares that the buffer VBO is an array buffer
    glBufferData(GL_ARRAY_BUFFER, line.vertexInfo.size() * sizeof(Vector3f), line.vertexInfo.data(), GL_STATIC_DRAW);//assigns the data that goes in the buffer VBO

    glEnableVertexAttribArray(gPositionLocation);//enables access to vertex attribute Position
    glVertexAttribPointer(gPositionLocation, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(Vector3f), nullptr);

    glEnableVertexAttribArray(gColorLocation);
    glVertexAttribPointer(gColorLocation, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(Vector3f), (void*)(sizeof(Vector3f)));

    glUniformMatrix4fv(gTransformLocation, 1, GL_TRUE, &transformation.data[0][0]);
    glUniform1f(gOpacityLocation, opacity);

    glDrawArrays(GL_LINE_STRIP, 0, line.vertexInfo.size() / 2);

    glDisableVertexAttribArray(gPositionLocation);//a safety precaution
    glDisableVertexAttribArray(gColorLocation);//a safety precaution
}


void LinePipeline::findShaderVariables(const GLuint &ShaderProgram) {
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

void LinePipeline::compileShaders(std::string vertexShaderFile, std::string fragmentShaderFile) {
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

    findShaderVariables(shaderProgram);

}


