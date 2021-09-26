#version 330

in vec2 TexCoord0;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
    FragColor = texture2D(tex, TexCoord0);
}
