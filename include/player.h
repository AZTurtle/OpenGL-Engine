#ifndef WORM_CLASS_H
#define WORM_CLASS_H

// #define PI 3.1415926
// #define RING_RES 16
// #define RING_NUM 4
// #define END_VERTS 17
// #define SEG_VERTS 64
// #define SEG_OFFSET 1.41414141414f
#include"resources.h"
#include"camera.h"
#include"core/fs.h"

struct tile{
    glm::ivec3 pos;
    glm::vec3 renderPos;
    glm::mat4 transform;
    glm::mat4 scaledTransform;
    bool moveable;
    Shader_* shader;
    tile(glm::ivec3 pos, bool moveable) : pos(pos), renderPos(pos), transform(glm::translate(glm::mat4(1.0f), glm::vec3(-renderPos.x, renderPos.y, -renderPos.z))), moveable(moveable){};
    void update(){
        renderPos += ((glm::vec3)pos - renderPos) * 8.0f * delta_time;
        scaledTransform = glm::scale(glm::mat4(1.0f),glm::vec3(1.2f, 1.2f, 1.2f));
        transform = glm::translate(glm::mat4(1.0f), glm::vec3(-renderPos.x, renderPos.y, -renderPos.z));
        scaledTransform = glm::translate(glm::mat4(1.0f), glm::vec3(-renderPos.x, renderPos.y, -renderPos.z));
    }
};

struct letterTile : tile{
    char letter;
    glm::vec3 color;
    bool chained = false;
    bool player;
    Model model;
    letterTile(glm::ivec3 pos, glm::vec3 color, char letter, bool moveable, bool player) : tile(pos, moveable), player(player), model(Model(&models::letters[letter - 97])), letter(letter), color(color){};
};

extern bool hasLetters;

class Player{

    unsigned short wordLen;
    const char* word; 

    glm::mat4 transform = glm::mat4(1.0f);

    Shader_* letterShader;
    GLuint pos_u;

    void update();

    public:

        std::vector<letterTile*> body;

        Player(Camera*);

        void move(glm::ivec3);
        void prepModel(const char*, glm::ivec3);
        void clearWords();
};

#endif