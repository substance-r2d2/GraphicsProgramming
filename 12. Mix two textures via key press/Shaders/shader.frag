#version 330 core
out vec4 color;

in vec4 OurColor;
in vec2 TexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float mix;

void main()
{
	color = mix(texture(ourTexture1,TexCoord),texture(ourTexture2,TexCoord),mix);
}
