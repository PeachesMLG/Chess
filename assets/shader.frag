#version 330 core

out vec4 FragColor;

in vec4 ourColor;
in vec2 ourTexCoord;
in float ourTexId;

uniform sampler2D[3] ourTextures;

void main()
{
    int index = int(ourTexId);
    if (index == -1) {
        FragColor = ourColor;
    } else {
        FragColor = texture(ourTextures[index], ourTexCoord);
    }
}