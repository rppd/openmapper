#version 330 core
layout (location=0) in vec2 vert_in;
layout (location=1) in vec2 uv_in;

out vec2 vert;
out vec2 uv;

uniform mat4 transform;

void main() {
    uv = uv_in;
    gl_Position = transform*vec4(vert_in,0,1);
    //gl_Position = vec4(vert_in, 0., 1.);
}