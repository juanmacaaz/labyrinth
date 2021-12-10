#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform vec3 pos;

void main()
{
    TexCoords = aPos;
    vec3 new;
    new.x = aPos.x + pos.x;
    new.y = aPos.y + pos.y;
    new.z = aPos.z + pos.z;
    vec4 pos = projection * view * vec4(new, 1.0);
    gl_Position = pos.xyww;
}  