#ifndef ASSETGROUP_CLASS_H
#define ASSETGROUP_CLASS_H

#include<vector>
#include<glm/glm.hpp>
#include<iostream>
#include<filesystem>
#include<fstream>
#include<sstream>
#include<string.h>
#include<map>
#include<glm/gtc/type_ptr.hpp>
#include"assets/model.h"
#include"assets/shaders.h"

inline char resourcePath[MAX_CWD + 12];

class Assets{
    void addShader(const char*, const char*);
    std::map<std::string, Texture> textures;
    std::map<std::string, GLuint> vertexShaders;
    std::map<std::string, GLuint> fragmentShaders;

public:
    Texture* getTexture(const char*);
    GLuint getVertexShader(const char*);
    GLuint getFragmentShader(const char*);
    void load();
    static Assets& getAssets(){
        static Assets created;
        return created;
    }

};

#endif