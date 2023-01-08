#version 330 core
in vec2 vert;
in vec2 uv;

out vec4 FragColor;

void main() {
    // FragColor = vec4(uv.x,uv.y,0,1);
    FragColor =  vec4((uv.x+uv.y)/2,0,1,1);
}