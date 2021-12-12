#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

uniform vec3 pos;

out vec2 TexCoord0;
out vec3 mVertex;

void main()
{
    vec3 temp;
    temp.x = Position.x + pos.x;
    temp.y = Position.y + pos.y;
    temp.z = Position.z + pos.z;
    mVertex = temp;

    gl_Position = (projection * view * model) * vec4(Position, 1.0);
    TexCoord0 = TexCoord;
}
