#version 330 core
#define M_PI 3.1415926535897932384626433832795

in vec2 vert;
in vec2 uv;

out vec4 FragColor;

uniform float t;

void main() {
    //float z = cos(vert.x/1000.);
    float z = vert.y;
    z = (z+1.)/2.;
    //z = pow(z, 10.);
  
    FragColor =  vec4(0,0,z,1);
}