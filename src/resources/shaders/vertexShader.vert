#version 460 core

layout(location = 0) in vec2 Position; 
layout(location = 1) in vec2 texCoord;
  
out vec2 v_TexCoord; 

void main()
{
    gl_Position = vec4(Position, 0.0, 1.0); 
    v_TexCoord = texCoord;
}
