#version 460 core

in vec2 v_TexCoord;

out vec4 texColor;

uniform sampler2D shipTexture;

void main()
{
	texColor = texture2D(shipTexture, v_TexCoord);
	// texColor = vec4 (0.5, 0.5, 0.0, 1.0);
}
