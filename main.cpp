#include <iostream>
#include <map>
#include <vector>
#include <chrono>
#include <cmath>
#include <algorithm>

#include "Pipelines/MeshPipeline.h"
#include "Pipelines/LinePipeline.h"
#include "Pipelines/Pipeline.h"
#include "Renderables/Line.h"
#include "Plots/Surface.h"
#include "Plots/Curve.h"
#include "Camera.h"


#include "Plots/ColorField.h"

#include "Pipelines/VolumePipeline.h"

#define _USE_MATH_DEFINES

//before I can make the grid lines. I need to add support for opacity.
//opacity would be set during cam.draw(drawable, opacity);

//mesh opacity doesn't work correctly because the mesh triangles are not being sorted based on distance from camera

//Make a volume pipeline
//Ideally it raytraces through 3D Textures
//that's all it does
//when attempting to implement, actually read the documentation



Camera cam;

std::vector<bool> keysPressed(256);
std::map<int, bool> specialKeysPressed;
float cameraSpeed = 2;
float cameraSensitivity = 1/400.0;
float pointSize = 1;

void onMouseMove(int x, int y);
void keyboardDownCallback(unsigned char key, int x, int y);
void keyboardUpCallback(unsigned char key, int x, int y);
void keyboardSpecialDownCallback(int key, int x, int y);
void keyboardSpecialUpCallback(int key, int x, int y);
void scrollWheelCallback(int button, int direction, int x, int y);

void controls();
int getSpecialKey(int glutCode);
void drawAxes(Camera& cam);
void drawGrid(Camera& cam);



int main(int argc, char** argv) {
    srand(time(nullptr));
    glutInit(&argc, argv);
    Pipeline::selectWindow(Pipeline::makeWindow(400, 400, "hi"));
    glutFullScreen();

    glEnable(GL_DEPTH_TEST);
    glutSetCursor(GLUT_CURSOR_NONE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutPassiveMotionFunc(onMouseMove);
    glutKeyboardFunc(keyboardDownCallback);
    glutKeyboardUpFunc(keyboardUpCallback);
    glutSpecialFunc(keyboardSpecialDownCallback);
    glutSpecialUpFunc(keyboardSpecialUpCallback);
    glutMouseWheelFunc(scrollWheelCallback);




    MeshPipeline::compileShaders("shader2.vs", "shader.fs");
    LinePipeline::compileShaders("shader2.vs", "shader.fs");
    VolumePipeline::compileShaders("shaderVolume.vs","shaderVolume.fs");

    //glDispatchCompute

    cam.position.x = -1;
    cam.position.y = -1;
    cam.position.z = 1;
    cam.angleTheta = -M_PI_4;
    cam.anglePhi = -M_PI / 5;

    double time = 0;
    double printTimer = 0;
    int counter = 0;
    double totalDelta = 0;

    Surface hi([](float u, float v){
        return Vector3f(u, v, 0);
    }, {-10, 10}, {-10, 10}, 100000);

    Curve bye([](float t){
        return Vector3f(
                t / (1+t),
                sqrt(1 + t),
                0
                );
    }, -10, 10, 10000);

    Pipeline::addDisplayCallback([&](){
        static auto lastTime = std::chrono::high_resolution_clock::now();
        auto now = std::chrono::high_resolution_clock::now();
        double deltaTime = std::chrono::duration<double>(now - lastTime).count();
        time += deltaTime;
        printTimer += deltaTime;
        lastTime = now;

        controls();

        cam.draw(bye);


        totalDelta += deltaTime;
        counter++;
        if(printTimer > 0.1){
            std::cout << counter / totalDelta << std::endl;
            printTimer = 0;
            counter = 0;
            totalDelta = 0;
        }


        drawAxes(cam);
        drawGrid(cam);
        glutPostRedisplay();
    });

    glutMainLoop();



    return 0;
}

Curve xAxisPos([](double t){
    return Vector3f(
            t * 1000000,0,0
    );
}, 0, 1, 2);
Curve xAxisNeg([](double t){
    return Vector3f(
            -t * 1000000,0,0
    );
}, 0, 1, 2);
Curve yAxisPos([](double t){
    return Vector3f(
            0,t * 1000000,0
    );
}, 0, 1, 2);
Curve yAxisNeg([](double t){
    return Vector3f(
            0,-t * 1000000,0
    );
}, 0, 1, 2);
Curve zAxisPos([](double t){
    return Vector3f(
            0, 0, t * 1000000
    );
}, 0, 1, 2);
Curve zAxisNeg([](double t){
    return Vector3f(
            0, 0, -t * 1000000
    );
}, 0, 1, 2);

void drawAxes(Camera& cam){
    cam.draw(xAxisPos, 0.6);
    cam.draw(xAxisNeg, 0.6);
    cam.draw(yAxisPos, 0.6);
    cam.draw(yAxisNeg, 0.6);
    cam.draw(zAxisPos, 0.6);
    cam.draw(zAxisNeg, 0.6);
}

void drawGrid(Camera& cam){

    for(int i = 0; i <= 3; i++){
        int z = 5 * (i - 1) + floor(cam.position.z / 5) * 5;
        float distanceZ = abs(z - cam.position.z);

        for(int x = floor(cam.position.x - 10); x <= floor(cam.position.x + 10); x++){
            if(z==0 && x==0){
                continue;
            }

            float distanceX = abs(x - cam.position.x);
            Curve curve([&cam, &x, &z](double t){
                return Vector3f(
                        x, t, z
                );
            }, cam.position.y - 10, cam.position.y + 10, 2);
            curve.line.vertexInfo[1] = {1, 1, 1};
            curve.line.vertexInfo[3] = {1, 1, 1};

            float opacity = 0.2;
            if(distanceZ > 5){
                opacity -= (distanceZ - 5) / 5 * 0.2;
            }
            if(distanceX > 5){
                opacity -= (distanceX - 5) / 5 * 0.2;
            }
            if(opacity < 0){
                opacity = 0;
            }
            cam.draw(curve, opacity);
        }

        for(int y = floor(cam.position.y - 10); y <= floor(cam.position.y + 10); y++){
            if(z==0 && y==0){
                continue;
            }

            float distanceY = std::abs(y - cam.position.y);
            Curve curve([&cam, &y, &z](double t){
                return Vector3f(
                        t, y, z
                );
            }, cam.position.x - 10, cam.position.x + 10, 2);
            curve.line.vertexInfo[1] = {1, 1, 1};
            curve.line.vertexInfo[3] = {1, 1, 1};

            float opacity = 0.2;
            if(distanceZ > 5){
                opacity -= (distanceZ - 5) / 5 * 0.2;
            }
            if(distanceY > 5){
                opacity -= (distanceY - 5) / 5 * 0.2;
            }
            cam.draw(curve, opacity);
        }
    }



}



void onMouseMove(int x, int y){
    static int lastX = x;
    static int lastY = y;

    int deltaX = x - lastX;
    int deltaY = y - lastY;

    cam.angleTheta -= deltaX * cameraSensitivity;
    cam.anglePhi -= deltaY * cameraSensitivity;

    cam.anglePhi = std::min(std::max((float)-M_PI_2, cam.anglePhi), (float)M_PI_2);
    cam.angleTheta = std::fmod(cam.angleTheta, 2 * (float)M_PI);

    lastX = Pipeline::getWindowWidth() / 2;
    lastY = Pipeline::getWindowHeight() / 2;
    glutWarpPointer(lastX, lastY);

}

void keyboardDownCallback(unsigned char key, int x, int y){
    switch (key) {
        case 27:
            exit(0);
            break;
    }
    keysPressed[key] = true;

    if(key >= 97 && key <= 122){
        keysPressed[key - 97 + 65] = true;
    }

    if(key >= 65 && key <= 90){
        keysPressed[key - 65 + 97] = true;
    }

}

void keyboardUpCallback(unsigned char key, int x, int y){
    keysPressed[key] = false;

    if(key >= 97 && key <= 122){
        keysPressed[key - 97 + 65] = false;
    }

    if(key >= 65 && key <= 90){
        keysPressed[key - 65 + 97] = false;
    }
}

void keyboardSpecialDownCallback(int key, int x, int y){
    specialKeysPressed[key] = true;
}
void keyboardSpecialUpCallback(int key, int x, int y){
    specialKeysPressed[key] = false;
}

void controls(){
    static auto lastTime = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    double deltaTime = std::chrono::duration<double>(now - lastTime).count();
    lastTime = now;

    if(keysPressed['w']  || keysPressed['W']){
        cam.position.y += std::cos(-cam.angleTheta) * deltaTime * cameraSpeed;
        cam.position.x += std::sin(-cam.angleTheta) * deltaTime * cameraSpeed;
    }

    if(keysPressed['s']  || keysPressed['S']){
        cam.position.y -= std::cos(-cam.angleTheta) * deltaTime * cameraSpeed;
        cam.position.x -= std::sin(-cam.angleTheta) * deltaTime * cameraSpeed;
    }

    if(keysPressed['a']  || keysPressed['A']){
        cam.position.y += std::sin(-cam.angleTheta) * deltaTime * cameraSpeed;
        cam.position.x -= std::cos(-cam.angleTheta) * deltaTime * cameraSpeed;
    }

    if(keysPressed['d']  || keysPressed['D']){
        cam.position.y -= std::sin(-cam.angleTheta) * deltaTime * cameraSpeed;
        cam.position.x += std::cos(-cam.angleTheta) * deltaTime * cameraSpeed;
    }

    if(keysPressed[' ']){
        cam.position.z += deltaTime * cameraSpeed;
    }

    if(specialKeysPressed[GLUT_KEY_SHIFT_L]){
        cam.position.z -= deltaTime * cameraSpeed;
    }

    if(keysPressed['q'] || keysPressed['Q']){
        pointSize -= deltaTime * 100;
        pointSize = std::max(1.f, pointSize);
        glPointSize(pointSize);
        glLineWidth(pointSize);
    }

    if(keysPressed['e'] || keysPressed['E']){
        pointSize += deltaTime * 100;
        pointSize = std::min(10.f, pointSize);//it seems to also be limited somewhere else. That source of limitation should be removed
        glPointSize(pointSize);
        glLineWidth(pointSize);
    }

}

int getSpecialKey(int glutCode){
    if(glutCode <= 12){
        return 255 + glutCode;
    }else{
        return 255 + glutCode - 100 + 1 + 12;
    }
}

void scrollWheelCallback(int button, int direction, int x, int y){
    cameraSpeed *= std::pow(2, direction / 10.f);
    cameraSpeed = std::max(0.f, cameraSpeed);
    cameraSpeed = std::min(100.f, cameraSpeed);
}