#pragma once
#include <iostream>
#include <hashtable.h>
#include <stb_image.h>
#include <random>
#include <vector>
#include <glm/glm.hpp>
#include <glad.h>





namespace f_util
{
struct image
{
    unsigned char *donne;
    int largeur,hauteur,channel;
    
};
 struct texture
{
   const char* name;
   glm::vec3 DIFFUSE= {0,0,0};
   glm::vec3 specular = {0,0,0};
   glm::vec3 SPECULAR = {0,0,0};
   glm::vec3 AMBIENT = {0,0,0};
   glm::vec3 EMISSIVE = {0,0,0};
   glm::vec3 TRANSPARENT = {0,0,0};
   glm::vec3 REFLECTIVE = {0,0,0};
    float REFLECTIVITY = 0.0;
    bool wireframe= true;


   
};
image* chargertex(const char* chemin, bool alpha);
std::vector<glm::vec3> vecaleatoire(int n);
 float random_float(float min, float max) ;



}
struct alignas(16) Materiaux
{
    glm::vec3 ambiante;
    glm::vec3 diffuse;
    glm::vec3 speculaire;
    float shininess;
};

namespace MAT {

    // L'Or, pour la vanité aveuglante de tes géométries
    const Materiaux Or = {
        glm::vec3(0.24725f, 0.1995f, 0.0745f),     // Reflet chaud dans l'ombre
        glm::vec3(0.75164f, 0.60648f, 0.22648f),   // L'éclat jaune majestueux
        glm::vec3(0.628281f, 0.555802f, 0.366065f),// Une brillance métallique dure
        51.2f                                      // Concentration de la lumière
    };

    // L'Argent, froid, clinique, tourné vers la pureté stellaire
    const Materiaux Argent = {
        glm::vec3(0.19225f, 0.19225f, 0.19225f),
        glm::vec3(0.50754f, 0.50754f, 0.50754f),
        glm::vec3(0.508273f, 0.508273f, 0.508273f),
        51.2f
    };

    // L'Émeraude, mathématique et calculatrice, un éclat vert perçant
    const Materiaux Emeraude = {
        glm::vec3(0.0215f, 0.1745f, 0.0215f),
        glm::vec3(0.07568f, 0.61424f, 0.07568f),
        glm::vec3(0.633f, 0.727811f, 0.633f),
        76.8f // Une surface extrêmement lisse, capturant des points de lumière acérés
    };

    // L'Obsidienne, sombre et dévorante comme l'abîme de ta mémoire non allouée
    const Materiaux Obsidienne = {
        glm::vec3(0.05375f, 0.05f, 0.06625f),
        glm::vec3(0.18275f, 0.17f, 0.22525f),
        glm::vec3(0.332741f, 0.328634f, 0.346435f),
        38.4f // Une brillance sourde, reflétant la lumière avec une sombre mélancolie
    };

    // Le Plastique Cyan, vestige vulgaire et synthétique de l'ère industrielle
    const Materiaux PlastiqueCyan = {
        glm::vec3(0.0f, 0.1f, 0.06f),
        glm::vec3(0.0f, 0.50980392f, 0.50980392f),
        glm::vec3(0.50196078f, 0.50196078f, 0.50196078f),
        32.0f // Un éclat artificiel, dispersant la lumière grossièrement
    };
}