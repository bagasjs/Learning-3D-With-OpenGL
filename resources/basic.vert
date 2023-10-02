#version 330 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec4 a_Color;

out vec4 v_Color;
uniform mat4 u_Proj;
uniform mat4 u_View;
uniform mat4 u_Model;

void main() {
    gl_Position = u_Proj * u_View * u_Model * vec4(a_Pos, 1.0);
    v_Color = a_Color;
}
