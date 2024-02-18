#version 450 core

layout(location = 0) in vec3  a_objectCoord; 
layout(location = 1) in vec2  a_textureCoord; 
layout(location = 2) in float a_textureID; 
  
out vec2 v_textureCoord; 
out float v_textureID;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(a_objectCoord, 1.0);
    v_textureCoord = a_textureCoord;
    v_textureID = a_textureID;
}
