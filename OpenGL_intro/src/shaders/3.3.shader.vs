#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
flat out int triangleIndex; 

uniform float xOffset;


void main()
{
    if (gl_VertexID < 3) 
    {
        gl_Position = vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0); 
    }
    else
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); 
    }
    ourColor = aColor;

    triangleIndex = gl_VertexID; // Assuming each triangle has 3 vertices
}

