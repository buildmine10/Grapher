#version 330 core

attribute vec3 Position;
uniform mat4 Transform;

uniform vec3 CameraPosition;

uniform vec3 VolumePosition;
uniform vec3 VolumeScale;

out vec3 percentPosition;
out vec3 position;

void main()
{
    percentPosition = Position;
    position = Position * VolumeScale + VolumePosition;
    gl_Position = Transform * vec4(position.x, position.y, position.z, 1);
    //The reordering is needed because the mathematical coordinates do not match rendering coordinates
    float temp = gl_Position.z;
    gl_Position.z = gl_Position.y;
    gl_Position.y = temp;
}