#version 330 core
out vec4 FragColor;

in vec4 myColor;
in vec2 TexCoord;

uniform sampler2D MainTex;

void main()
{
    FragColor = texture(MainTex, TexCoord);
}