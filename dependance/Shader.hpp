#pragma once
#include <string>
#include <glad.h> // include glad BEFORE any GLFW includes that might follow
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>




class Shader {
public:
    GLuint ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    void use() const;

    template<typename T>
    void set(const std::string& name, const T& value) const;

    void uniformetex(std::string& name, const unsigned int value) const;

private:
    void checkCompileErrors(GLuint shader, const std::string &type) const;
};

#include <Shader.inl>