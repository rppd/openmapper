#version 330 core
layout (location=0) in vec2 vert_in;
layout (location=1) in vec2 uv_in;

out vec2 vert;
out vec2 uv;

// uniform mat4 transform;

void main() {
    // mat4 transform = mat4(1.0/300);
    // vert = (transform * vec4(vert_in,0,0)).xy;
    uv = uv_in;
    gl_Position = vec4(vert_in/400,0,1);
}