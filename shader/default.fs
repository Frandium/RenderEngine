#version 330 core
out vec4 FragColor;

in vec4 myColor;
in vec2 TexCoord;

uniform sampler2D MainTex;
uniform sampler2D Tex1;
uniform float time;

void main()
{
     FragColor = mix(texture(MainTex, TexCoord) , texture(Tex1, TexCoord), time);
}