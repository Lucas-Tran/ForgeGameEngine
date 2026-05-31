#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTextureCoordinates;
layout (location = 2) in vec3 inNormal;

out vec2 textureCoordinates;
out vec3 normalCoordinates;
out vec3 fragPos;

// MVP
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
   vec4 worldCordinates = model * vec4(inPosition, 1.0f);
   fragPos = vec3(worldCordinates);
   gl_Position = projection * view * worldCordinates;
   textureCoordinates = inTextureCoordinates;
   normalCoordinates = mat3(transpose(inverse(model))) * inNormal;  
}