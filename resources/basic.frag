#version 330 core

layout(location = 0) out vec4 fragColor;

in vec4 v_Color;
in vec2 v_TexCoords;
uniform sampler2D u_TextureSamplers;

void main() {
    fragColor = texture(u_TextureSamplers, v_TexCoords) * v_Color;
}
