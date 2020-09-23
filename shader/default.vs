#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;

uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


out vec4 myColor;
out vec2 TexCoord;


void main()
{
    gl_Position = projection * view * model * vec4(pos.xyz, 1.0);
    myColor = vec4(1, 1, 1, 1) * time;
    TexCoord = uv;
}