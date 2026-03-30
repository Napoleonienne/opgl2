#pragma once
#define GLM_FORCE_SWIZZLE


#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/scalar_constants.hpp>

struct alignas(16) vertex
{
    glm::vec3 vertice;
    glm::vec3 normale;
    glm::vec2 uv;
};

