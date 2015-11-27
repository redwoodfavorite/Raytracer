#version 410 core

layout(location = 0) in vec3 v_Color;

out vec3 color;

void main(){
    color = v_Color;
}