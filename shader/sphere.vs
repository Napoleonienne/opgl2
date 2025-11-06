#version 450 core
layout (location = 0) in vec3 aPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    mat4 PVM = projection * view * model;
    gl_Position = PVM * vec4(aPos, 0.5); 
    
}
