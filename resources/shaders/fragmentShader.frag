#version 330 core

in vec2 v_textureCoord;
in float v_textureID;

out vec4 texColor;

uniform sampler2D u_textures[11];

void main()
{
	int index = int(v_textureID);
	texColor = texture(u_textures[index], v_textureCoord);
}
