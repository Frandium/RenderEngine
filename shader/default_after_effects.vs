#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;
layout(location = 3) in vec2 norm;

out vec2 TexCoord;


void main()
{
    gl_Position = vec4(pos,1);
    TexCoord = uv;
}