#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texc;

out vec2 Textcord; // <-- D�clare la variable � passer au fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    mat4 PVM = projection * view * model;
    gl_Position = PVM * vec4(aPos, 1.0); 
    Textcord = texc; // <-- maintenant c'est correct
}
