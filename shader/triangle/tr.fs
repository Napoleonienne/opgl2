// Fragment shader:
// ================
#version 330 core
out vec4 FragColor;
in vec2 Textcord;
uniform sampler2D ourTexture;
uniform float utime;
uniform vec4 couleur;
void main()
{
    //FragColor = vec4(0.5,0.6,0.1, 1.0); 
    FragColor = texture(ourTexture,Textcord)*couleur;
}
