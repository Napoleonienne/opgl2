#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <vector>
#include <glad.h>  
#include <Sphere.hpp>
#include <Shader.hpp>





Sphere::Sphere(glm::vec3 origine, float rayon, glm::vec3 _couleur,Shader a): shade(a),couleur(_couleur){
    int latitudeCount = face;
    int longitudeCount = face/2;

    for (int lat = 0; lat <= latitudeCount; lat++) {
        float theta = glm::pi<float>() * lat / latitudeCount; // de 0 à pi
        float v = (float)lat / latitudeCount;                 // UV V

        for (int lon = 0; lon <= longitudeCount; lon++) {
            float phi = 2.0f * glm::pi<float>() * lon / longitudeCount; // de 0 à 2pi
            float u = (float)lon / longitudeCount;                     // UV U

            float x = origine.x + rayon * sin(theta) * cos(phi);
            float y = origine.y + rayon * cos(theta);
            float z = origine.z + rayon * sin(theta) * sin(phi);

            vertex.push_back(glm::vec3(x, y, z));
            uv.push_back(glm::vec2(u, v));
        }
    }
 
    normale.assign(vertex.size(), glm::vec3(0.0f));

    // Création des indices
    for (int lat = 0; lat < latitudeCount; lat++) {
        for (int lon = 0; lon < longitudeCount; lon++) {
            int current = lat * (longitudeCount + 1) + lon;
            int next = (lat + 1) * (longitudeCount + 1) + lon;

            // Premier triangle de la bande
            indice.push_back((GLuint)current);
            indice.push_back((GLuint)next);
            indice.push_back((GLuint)(current + 1));

            // Deuxième triangle de la bande
            indice.push_back((GLuint)(current + 1));
            indice.push_back((GLuint)next);
            indice.push_back((GLuint)(next + 1));
        }
    }

for (size_t i = 0; i < indice.size(); i += 3)
{
    glm::vec3 A = vertex[indice[i]];
    glm::vec3 B = vertex[indice[i + 1]];
    glm::vec3 C = vertex[indice[i + 2]];

    glm::vec3 normalFace = glm::normalize(glm::cross(B - A, C - A));

    // Ajouter cette normale aux 3 vertices pour un lissage
    normale[indice[i]]     += normalFace;
    normale[indice[i + 1]] += normalFace;
    normale[indice[i + 2]] += normalFace;
}

// Normaliser toutes les normales des vertices
for (size_t i = 0; i < normale.size(); i++)
{
    normale[i] = glm::normalize(normale[i]);
}

    Sphere::init();
    
    
    
}


void Sphere::init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO2);

    glBindVertexArray(VAO);

    // Positions
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(glm::vec3), vertex.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    // Normales
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, normale.size() * sizeof(glm::vec3), normale.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    // Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice.size() * sizeof(GLuint), indice.data(), GL_STATIC_DRAW);
}



void Sphere::dessiner(glm::mat4 procj, glm::mat4 model,glm::mat4 vision){
    shade.use();
    shade.set("model",model);
    shade.set("projection",procj);
    shade.set("view", vision);
    shade.set("couleur",couleur);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indice.size(), GL_UNSIGNED_INT, 0);

            
}
void Sphere::destroy(){
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteBuffers(1,&VBO2);
}