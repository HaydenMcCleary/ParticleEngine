#version 330 core
out vec4 FragColor;

in vec3 ourColor;
flat in int triangleIndex; // Receive triangle index from vertex shader

uniform float colorOffset;


void main()
{

    if (triangleIndex < 3) 
    {
        FragColor = vec4(ourColor, 1.0f);
    }
    else 
    {
        FragColor = vec4(ourColor.x + colorOffset, ourColor.y - colorOffset, ourColor.z, 1.0f);
    }

}

