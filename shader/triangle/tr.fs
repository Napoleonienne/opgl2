#version 330 core

#ifdef GL_ES
precision mediump float;
#endif

out vec4 fragcolor;
void main(){
    fragcolor = vec4(0.4f,0.5f,0.6,1.0f);
}