#pragma once
#include <glad.h>
#include <string>
#include <iostream>



class buffer{
    public:
    GLuint vbodym;
    GLuint VBO_principale;
    buffer();
    ~buffer();
    int get_cursorp();
    int get_cursord();

    void add_mem_dym(int mem);
    void add_mem_static(int meme);

    
    private:
    int cursorp= 0;
    int cursord=0;
    int vbp_;



};
