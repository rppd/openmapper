#version 330 core
#define M_PI 3.1415926535897932384626433832795

in vec2 vert;
in vec2 uv;

out vec4 FragColor;

uniform float t;

void main() {
    float z = mod(3*t,2*M_PI);
    float r = (uv.x + uv.y)/2;
    float c1 = cos(3*t)/2 + 0.5;
    float c2 = cos(vert.x/100)/2 + 0.5;
    float c3 = sin(10*r+z)/2 + 0.5;

    FragColor =  vec4(0,0,c3,1);
}