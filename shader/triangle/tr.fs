
#version 330 core
out vec4 FragColor;  
in vec3 ourColor;

uniform float utime;
out vec3 pos;
void main()

{
    vec4 temp = vec3(0.1,0.647,0.35);
    FragColor = vec4(temp,1);
    pos = temp;
}