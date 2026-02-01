#include <buffer.hpp>




buffer::buffer(){
    glGenBuffers(1, &VBO_principale);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_principale);
    glBufferData(GL_ARRAY_BUFFER, 128000000, nullptr, GL_STATIC_DRAW); //128mo

    glGenBuffers(1, &vbodym);
    glBindBuffer(GL_ARRAY_BUFFER, vbodym);
    glBufferData(GL_ARRAY_BUFFER, 64000000, nullptr, GL_DYNAMIC_DRAW); //64mo
    
}


buffer::~buffer(){
    glDeleteBuffers(1,&VBO_principale);
    glDeleteBuffers(1,&vbodym);
}

int buffer::get_cursord(){

    return 0;
}
int buffer::get_cursorp(){


    return 0;

}

void buffer::add_mem_dym(int mem){}
void buffer::add_mem_static(int mem){}