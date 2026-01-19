#pragma once

class mesh {
public:
    mesh() = default;
    ~mesh() = default;
    void load_obj(const char* path);

    private: 
    int *mesh;






};