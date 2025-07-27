
#version 330 core
out vec4 FragColor;  
in vec3 ourColor;

uniform float utime;

void main()

{
    float x =sin(utime*ourColor.x)*0.5;
    float y = sin(utime)*0.4;
    float z = sin(utime)*0.7;
    FragColor = vec4(vec3(sin(x)),1.0);
}