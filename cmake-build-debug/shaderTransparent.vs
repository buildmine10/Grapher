#version 330 core

attribute vec3 Position;
uniform mat4 Transform;
attribute vec3 Color;

out vec4 color;

void main()
{
    gl_Position = Transform * vec4(Position.x, Position.y, Position.z, 1);//The order is needed because the mathematical coordinates do not match rendering coordinates
    float temp = gl_Position.z;
    gl_Position.z = gl_Position.y;
    gl_Position.y = temp;
    color = vec4(Color, 0.25);
}