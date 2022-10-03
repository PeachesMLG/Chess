#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float aTexId;

out vec4 ourColor;
out vec2 ourTexCoord;
out float ourTexId;

void main()
{
    gl_Position = vec4((aPos / vec3(4, 4, 4)) - vec3(1, 1, 1), 1.0);
    ourColor = aColor;
    ourTexCoord = aTexCoord;
    ourTexId = aTexId;
}