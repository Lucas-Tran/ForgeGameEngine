#version 330 core

out vec4 outColor;

in vec2 textureCoordinates;

uniform sampler2D texture_0;

void main() {
   outColor = texture(texture_0, textureCoordinates);
}