#include <buffer.hpp>




buffer::buffer(int t){
    glGenBuffers(t, &VBO_principale);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_principale);
    glBufferData(GL_ARRAY_BUFFER, 128000000, nullptr, GL_STATIC_DRAW); //128mo

    glGenBuffers(t, &vbodym);
    glBindBuffer(GL_ARRAY_BUFFER, vbodym);
    glBufferData(GL_ARRAY_BUFFER, 64000000, nullptr, GL_DYNAMIC_DRAW); //64mo
    
}


std::string buffer::supp_buff(int indice){

    
    return "rt";
};