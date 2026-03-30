#include <f_util.hpp>






namespace f_util
{


image* chargertex(const char* chemin, bool alpha){
    image *tex;
    tex->donne = stbi_load(chemin, &tex->largeur, &tex->hauteur, &tex->channel, 0);
    if (!tex->donne)
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
        std::cerr << "Failed to load texture: " << chemin << std::endl;
        return nullptr;
    }

    return tex;
}
unsigned char* load_texture(const char* chemin,bool alpha){
    image* tex = chargertex(chemin,alpha);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (tex->donne)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->largeur, tex->hauteur, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->donne);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    return tex->donne;
}


    std::vector<glm::vec3> vecaleatoire(int n,float binf,float bsup){
        std::vector<glm::vec3> pos;
        for (int i = 0; i < n; i++)
        {
            pos.push_back(glm::vec3(random_float(binf,bsup),random_float(binf,bsup),random_float(binf,bsup)));
        };
        return pos;
    }


    float random_float(float min, float max) {
        static std::random_device rd;  // Générateur de graine aléatoire
        static std::mt19937 gen(rd()); // Moteur de génération (Mersenne Twister)
        std::uniform_real_distribution<float> dis(min, max); // Distribution uniforme
        return dis(gen);
    }

    

}