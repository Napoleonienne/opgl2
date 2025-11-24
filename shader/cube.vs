#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aPosTEX;
layout (location = 2) in vec3 aNORMALE;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 normale;
out vec3 FragPos;
out vec2 postexture;


void main()
{
    mat4 PVM = projection * view * model;
    gl_Position = PVM * vec4(aPos, 0.5); 
    FragPos = vec3(model * vec4(aPos, 1.0));
    normale = mat3(transpose(inverse(model))) * aNORMALE;
    postexture = aPosTEX ;

    
}
