//
// Created by colli on 5/20/2022.
//

#include "VolumePipeline.h"
#include <fstream>
#include <sstream>

const std::array<Vector3f, 8> VolumePipeline::volumeCubeVertices = {
        Vector3f(0, 0, 0),
        Vector3f(1, 0, 0),
        Vector3f(1, 1, 0),
        Vector3f(0, 1, 0),

        Vector3f(0, 1, 1),
        Vector3f(1, 1, 1),
        Vector3f(1, 0, 1),
        Vector3f(0, 0, 1)
};

const std::array<int, 36> VolumePipeline::volumeCubeTris = {
        0, 2, 1, //face front
        0, 3, 2,
        2, 3, 4, //face top
        2, 4, 5,
        1, 2, 5, //face right
        1, 5, 6,
        0, 7, 4, //face left
        0, 4, 3,
        5, 4, 7, //face back
        5, 7, 6,
        0, 6, 7, //face bottom
        0, 1, 6
};


GLuint VolumePipeline::shaderProgram{};

GLuint VolumePipeline::VBO{};
GLuint VolumePipeline::IBO{};
GLuint VolumePipeline::gPositionLocation{};
GLint VolumePipeline::gTransformLocation{};
GLuint VolumePipeline::texture3D{};

GLint VolumePipeline::gVolumePositionLocation{};
GLint VolumePipeline::gVolumeScaleLocation{};
GLint VolumePipeline::gRayTransformLocation{};
GLint VolumePipeline::gCameraPositionLocation{};
GLint VolumePipeline::gWindowSizeLocation{};
GLint VolumePipeline::gVolumeDivisionsLocation{};


void VolumePipeline::findShaderVariables(const GLuint &ShaderProgram) {
    gPositionLocation = glGetAttribLocation(ShaderProgram, "Position");
    if(gPositionLocation == 0xFFFFFFFF){//checks if gPositionLocation is -1
        throw std::runtime_error("Position was not found in the shader program.");
    }

    gTransformLocation = glGetUniformLocation(ShaderProgram, "Transform");
    if(gTransformLocation == 0xFFFFFFFF){//checks if gScaleLocation is -1
        throw std::runtime_error("Transform was not found in the shader program.");
    }

    gVolumePositionLocation = glGetUniformLocation(ShaderProgram, "VolumePosition");
    if(gVolumePositionLocation == 0xFFFFFFFF){//checks if gScaleLocation is -1
        throw std::runtime_error("VolumePosition was not found in the shader program.");
    }

    gVolumeScaleLocation = glGetUniformLocation(ShaderProgram, "VolumeScale");
    if(gVolumeScaleLocation == 0xFFFFFFFF){//checks if gScaleLocation is -1
        throw std::runtime_error("VolumeScale was not found in the shader program.");
    }

    gRayTransformLocation = glGetUniformLocation(ShaderProgram, "RayTransform");
    if(gRayTransformLocation == 0xFFFFFFFF){//checks if gScaleLocation is -1
        throw std::runtime_error("RayTransform was not found in the shader program.");
    }

    gCameraPositionLocation = glGetUniformLocation(ShaderProgram, "CameraPosition");
    if(gCameraPositionLocation == 0xFFFFFFFF){//checks if gScaleLocation is -1
        //throw std::runtime_error("CameraPosition was not found in the shader program.");
    }

    gWindowSizeLocation = glGetUniformLocation(ShaderProgram, "WindowSize");
    if(gWindowSizeLocation == 0xFFFFFFFF){//checks if gScaleLocation is -1
        //throw std::runtime_error("WindowSize was not found in the shader program.");
    }

    gVolumeDivisionsLocation = glGetUniformLocation(ShaderProgram, "VolumeDivisions");
    if(gVolumeDivisionsLocation == 0xFFFFFFFF){//checks if gScaleLocation is -1
        //throw std::runtime_error("VolumeDivisions was not found in the shader program.");
    }
}

void VolumePipeline::compileShaders(std::string vertexShaderFile, std::string fragmentShaderFile) {
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

    //glEnable(GL_TEXTURE_3D);
    glGenTextures(1, &texture3D);

    findShaderVariables(shaderProgram);
}

void VolumePipeline::draw(const Volume &volume, Camera &camera) {
    glUseProgram(shaderProgram);

    glBindTexture(GL_TEXTURE_3D, texture3D);
    glEnable(GL_CULL_FACE);
    if(volume.width * volume.depth * volume.height > 0){
        glCullFace(GL_FRONT);
    }else {
        glCullFace(GL_BACK);
    }

    //textures are samples between 0 and 1. If a number is chosen outside that range, this decides how to handle that
    float borderColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);//x
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);//y
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);//z
    glTexParameterfv(GL_TEXTURE_3D, GL_TEXTURE_BORDER_COLOR, borderColor);//sets the border color
    //if sampled out of the range of 0 to 1, it will use the border color

    //glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//nearest neighbor sampling
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//linear neighbor sampling

    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, volume.iWidth, volume.iHeight, volume.iDepth, 0, GL_RGBA, GL_UNSIGNED_BYTE, volume.data);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);//Declares that the buffer VBO is an array buffer
    glBufferData(GL_ARRAY_BUFFER, volumeCubeVertices.size() * sizeof(Vector3f), volumeCubeVertices.data(), GL_STATIC_DRAW);//assigns the data that goes in the buffer VBO

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);//Declares that the buffer VBO is an array buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, volumeCubeTris.size() * sizeof(int), volumeCubeTris.data(), GL_STATIC_DRAW);//assigns the data that goes in the buffer VBO



    glEnableVertexAttribArray(gPositionLocation);//enables access to vertex attribute Position
    glVertexAttribPointer(gPositionLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    TransformationMatrix mat = camera.getTransformation();
    glUniformMatrix4fv(gTransformLocation, 1, GL_TRUE, &mat.data[0][0]);


    TransformationMatrix mat2 = camera.getVolumeMatrix();
    //mat2.setRotationIntrinsic(camera.anglePhi, 0, camera.angleTheta);
    glUniformMatrix4fv(gRayTransformLocation, 1, GL_TRUE, &mat2.data[0][0]);

    glUniform3f(gVolumePositionLocation, volume.position.x, volume.position.y, volume.position.z);
    glUniform3f(gVolumeScaleLocation, volume.width, volume.depth, volume.height);
    glUniform3f(gCameraPositionLocation, camera.position.x, camera.position.y, camera.position.z);
    glUniform2f(gWindowSizeLocation, Pipeline::getWindowWidth(), Pipeline::getWindowHeight());
    glUniform3f(gVolumeDivisionsLocation, volume.iWidth, volume.iDepth, volume.iHeight);


    glDrawElements(GL_TRIANGLES, volumeCubeTris.size(), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(gPositionLocation);//a safety precaution
}

