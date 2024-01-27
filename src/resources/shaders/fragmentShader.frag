#version 460 core

in vec2 v_textureCoord;
in float v_textureID;

out vec4 texColor;

uniform sampler2D u_textures[4];

void main()
{
	int index = int(v_textureID);
	texColor = texture2D(u_textures[index], v_textureCoord);
}
