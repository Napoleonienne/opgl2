#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <hashtable.h>
#include <stb_image.h>
#include <random>
#include <vector>
#include <glm/glm.hpp>




struct image
{
    unsigned char *donne;
    int largeur,hauteur,channel;
    
};
namespace f_util
{
image* chargertex(const char* chemin, bool alpha);
std::vector<glm::vec3> vecaleatoire(int n);
 float random_float(float min, float max) ;




}