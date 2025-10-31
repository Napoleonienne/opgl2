// Charge les fonctions OpenGL
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad.h>        // Toujours avant glfw3.h
#include <GLFW/glfw3.h>

#include <Shader.hpp>    // Classe shader personnalisée

#define IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// Callback appelée lors du redimensionnement de la fenêtre
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// Fonction pour gérer les entrées clavier
void processInput(GLFWwindow *window);
unsigned int chargerTexture(const char* chemin);
void interface(float* rX,float* rY,float* rZ,glm::vec4 *couleur);

// Paramètres de la fenêtre
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // Initialisation GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Création de la fenêtre
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cube Texturé", NULL, NULL);
    if (!window)
    {
        std::cerr << "Échec de la création de la fenêtre GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialisation GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Échec de l'initialisation de GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // Initialisation ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    // Création et compilation du shader
    Shader ourShader("../shader/triangle/tr.vs", "../shader/triangle/tr.fs");

    // Données du cube (positions + texture)
    float vertices[] = {
    // positions           // texture coords
    // Face avant
    -0.25f, -0.25f,  0.25f,  0.0f, 0.0f,
     0.25f, -0.25f,  0.25f,  1.0f, 0.0f,
     0.25f,  0.25f,  0.25f,  1.0f, 1.0f,
    -0.25f,  0.25f,  0.25f,  0.0f, 1.0f,

    // Face arrière
    -0.25f, -0.25f, -0.25f,  1.0f, 0.0f,
     0.25f, -0.25f, -0.25f,  0.0f, 0.0f,
     0.25f,  0.25f, -0.25f,  0.0f, 1.0f,
    -0.25f,  0.25f, -0.25f,  1.0f, 1.0f,

    // Face gauche
    -0.25f, -0.25f, -0.25f,  0.0f, 0.0f,
    -0.25f, -0.25f,  0.25f,  1.0f, 0.0f,
    -0.25f,  0.25f,  0.25f,  1.0f, 1.0f,
    -0.25f,  0.25f, -0.25f,  0.0f, 1.0f,

    // Face droite
     0.25f, -0.25f, -0.25f,  1.0f, 0.0f,
     0.25f, -0.25f,  0.25f,  0.0f, 0.0f,
     0.25f,  0.25f,  0.25f,  0.0f, 1.0f,
     0.25f,  0.25f, -0.25f,  1.0f, 1.0f,

    // Face dessous
    -0.25f, -0.25f, -0.25f,  0.0f, 1.0f,
     0.25f, -0.25f, -0.25f,  1.0f, 1.0f,
     0.25f, -0.25f,  0.25f,  1.0f, 0.0f,
    -0.25f, -0.25f,  0.25f,  0.0f, 0.0f,

    // Face dessus
    -0.25f,  0.25f, -0.25f,  0.0f, 0.0f,
     0.25f,  0.25f, -0.25f,  1.0f, 0.0f,
     0.25f,  0.25f,  0.25f,  1.0f, 1.0f,
    -0.25f,  0.25f,  0.25f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
    0, 1, 2,  2, 3, 0,       // avant
    4, 5, 6,  6, 7, 4,       // arrière
    8, 9,10, 10,11, 8,       // gauche
    12,13,14,14,15,12,       // droite
    16,17,18,18,19,16,       // dessous
    20,21,22,22,23,20        // dessus
    };


    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    unsigned int tex = chargerTexture("../wall.jpg");

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Attributs
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Matrices
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,-2.0f));
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f), 
        (float)SCR_WIDTH / (float)SCR_HEIGHT, 
        0.1f, 
        100.0f
                                        );
    float rotX = 0.0f;
    float rotY = 0.0f;
    float rotZ = 0.0f;
    float* rx = &rotX; 
    float* rY = &rotY;
    float* rZ = &rotZ;                                
    glm::vec4 couleur = glm::vec4(0.5f,0.6f,0.3f,1.0f);
    glm::vec4* c = &couleur;
                                        
    // Boucle principale
  
    

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.3f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        float utime=glfwGetTime();
       
        interface(rx,rY,rZ,c);
        // Rotation
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (rotX), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, (rotY), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, (rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
        ourShader.use();
        ourShader.set("couleur",couleur);
        ourShader.set("model", model);
        ourShader.set("view", view);
        ourShader.set("projection", projection);
        ourShader.set("utime",utime);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);
        std::string texName = "ourTexture";
        ourShader.uniformetex(texName, 0);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}

unsigned int chargerTexture(const char* chemin)
{
    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(chemin,&width,&height,&nrChannels,0);
    if (data)
    {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Échec du chargement de la texture : " << chemin << std::endl;
    }
    stbi_image_free(data);
    return texture;
}
void interface(float* rX,float* rY,float* rZ,glm::vec4 *couleur)
{
        ImGui::Begin("control");
        ImGui::Button("rotation");
        ImGui::SliderAngle("rotation x",rX);
        ImGui::SliderAngle("rotation y",rY);
        ImGui::SliderAngle("rotation z",rZ);
        ImGui::ColorEdit4("couleeur",glm::value_ptr(*couleur));

        ImGui::End();
}