#include "glad.h" // Charge les fonctions OpenGL
#include <GLFW/glfw3.h> // Bibliothèque pour la gestion de la fenêtre et des entrées
#include <iostream>
#include "Shader.cpp" // Classe utilitaire pour les shaders

// Callback appelée lors du redimensionnement de la fenêtre
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// Fonction pour gérer les entrées clavier
void processInput(GLFWwindow *window);
// paramètres de la fenêtre
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{

    // Initialisation et configuration de GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Version majeure OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Version mineure OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Profil OpenGL

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Compatibilité MacOS
#endif

    // Création de la fenêtre GLFW
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl; // Affiche une erreur si la fenêtre n'a pas pu être créée
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Définit le contexte OpenGL courant
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Définit le callback de redimensionnement

    // Initialisation de GLAD pour charger les fonctions OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl; // Affiche une erreur si GLAD n'a pas pu être initialisé
        return -1;
    }

    // Création et compilation du shader
    const char *vs ="/home/guy/Documents/opengl/test/tes2/shader/triangle/tr.vs";
    const char *fs="/home/guy/Documents/opengl/test/tes2/shader/triangle/tr.fs";
    Shader ourShader(vs,fs); // Les fichiers de shader

    // Définition des données des sommets (positions et couleurs)
    float vertices[] = {
        // positions         // couleurs
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bas droite
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bas gauche
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // haut
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO); // Génère un VAO
    glGenBuffers(1, &VBO);      // Génère un VBO

    
    // Bind du VAO puis du VBO et configuration des attributs de sommet
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Attribut de position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Attribut de couleur
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


   
    // Boucle de rendu
    while (!glfwWindowShouldClose(window))
    {
        // Gestion des entrées
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ourShader.use();
        float utime = glfwGetTime();
        ourShader.setFloat("utime",utime);
        ourShader.setFloat("decal",0.5f);


        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Échange des buffers et gestion des événements
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Libération des ressources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // Terminaison de GLFW
    glfwTerminate();
    return 0;
}

// Fonction pour gérer la touche Échap
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}

// Callback appelé lors du redimensionnement de la fenêtre
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Met à jour la zone d'affichage OpenGL
    glViewport(0, 0, width, height);
}