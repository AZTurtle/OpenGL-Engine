#include "assets/textures.h"

Texture loadTexture(const char* filepath){
    Texture res;
    int channels;
    glGenTextures(1, &res.id);
    glBindTexture(GL_TEXTURE_2D, res.id);

    // Texture Properties

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    unsigned char* data = stbi_load(filepath, &res.w, &res.h, &channels, 0);

    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, res.w, res.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    } else {
        std::cout << "Couldn't load Texture" << std::endl;
    }

    stbi_image_free(data);

    return res;
}