#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include<vector>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<cstring>
#include"core/fs.h"

inline char modelPath[MAX_CWD + 19];

class Model_{
    public:
        Model_(const char*);
        static inline std::vector<Model_*> models;
        virtual void load();
        virtual void loadModel();
        unsigned int indNum;
    protected:
        GLuint VBO, EBO;
        const char* filepath;
};

struct Vert{
    glm::vec3 pos;
};

class Model_def : public Model_{    
    public:
        void load();
        void loadModel();
        Model_def(const char*);
};

struct Vert_NT{
    glm::vec3 pos;
    glm::vec3 norm;
    glm::vec2 uv;
};

class Model_def_NT : public Model_{  
    public:
        void load();
        void loadModel();
        Model_def_NT(const char*);
};

struct Vert_N{
    glm::vec3 pos;
    glm::vec3 norm;
};

class Model_def_N : public Model_{
    public:
        void load();
        void loadModel();
        Model_def_N(const char*);
};

struct Vert_T{
    glm::vec3 pos;
    glm::vec2 uv;
};

struct Vert_T_2D{
    glm::vec2 pos;
    glm::vec2 uv;
};

class Model_def_T : public Model_{
    public:
        void load();
        void loadModel();
        Model_def_T(const char*);
};

class Model{
    unsigned int indNum;
    GLuint id;
    public:
        Model(Model_*);
        void render();
};

#endif