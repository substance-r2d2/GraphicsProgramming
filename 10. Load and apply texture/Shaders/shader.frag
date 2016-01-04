#version 330 core
out vec4 color;

in vec4 OurColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
	color = texture(ourTexture,TexCoord);// * OurColor;
}
