#pragma once
#include <glad.h>
#include <string>
GLuint vbodym;
GLuint VBO_principale;
int cursor;
int cursor;



class buffer{
    public:
    GLuint vbodym;
    GLuint VBO_principale;
    buffer(int t=1);
    std::string supp_buff(int indice);
    
    private:
    int cursorp;
    int cursord;
    int vbp_;



};
