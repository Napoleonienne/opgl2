#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "glm/vec3.hpp"
#include <glm/gtc/type_ptr.hpp>






namespace gui {


    void init(GLFWwindow *window);

    void nvframes();
    void interface(glm::vec3 *couleur);
    void SetupImGuiModernStyle();
    void endframes();
    void liberer();





}