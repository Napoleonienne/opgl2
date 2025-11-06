#version 450 core

out vec4 FragColor;
uniform vec4 couleur;
uniform vec3 light;
vec4 b =vec4(light,1.0);
void main()
{
    //FragColor = vec4(0.5,0.6,0.1, 1.0); 
    FragColor = couleur*b;
}
