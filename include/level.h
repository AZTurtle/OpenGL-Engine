
#ifndef LEVEL_CLASS_H
#define LEVEL_CLASS_H

#include"camera.h"
#include"player.h"
#include"core/input.h"
#include"core/time_manager.h"
#include"assets/model.h"
#include"assets/assets.h"

struct level{
    const int w, h, z;
    virtual void drawTransparent() = 0;
    
    void update(){
        if(!hasLetters) return;
        if(globalTime - lastPressed >= 150){
            switch(lastKeyPressed){
                case VK_UP:
                    movePlayer(glm::ivec3(0.0f, 0.0f, 1.0f));
                    break;
                case VK_DOWN:
                    movePlayer(glm::ivec3(0.0f, 0.0f, -1.0f));
                    break;
                case VK_LEFT:
                    movePlayer(glm::ivec3(1.0f, 0.0f, 0.0f));
                    break;
                case VK_RIGHT:
                    movePlayer(glm::ivec3(-1.0f, 0.0f, 0.0f));
                    break;
                case VK_SPACE:
                    clearWords();
                    player.clearWords();
                    lastPressed = globalTime;
                    break;
                case 'R':
                    restart();
                    break;
            }
        }
        for(auto letter : letters){
            letter->update();
        }
    }
	glm::mat4 lTransform;

    std::vector<tile*> tiles;
    std::vector<letterTile*> letters;
    std::vector<std::string> validWords;
    Player player;
    Camera* cam;
    Assets& assets = Assets::getAssets();
    Shader_* tableShader;
    Model table;
    bool* levelComplete;
    virtual void draw(){
        static GLuint objMat_u = glGetUniformLocation(shaders::diffuse.id, "objMatrix");
        static GLuint camMat_u = glGetUniformLocation(shaders::diffuse.id, "camMatrix");
        for(auto letter : letters){
            static GLuint color = glGetUniformLocation(shaders::diffuse.id, "color");
            static GLuint camMatrix = glGetUniformLocation(shaders::diffuse.id, "camMatrix");
            static GLuint objMatrix = glGetUniformLocation(shaders::diffuse.id, "objMatrix");
            shaders::diffuse.bind();
            glUniformMatrix4fv(camMatrix, 1, GL_FALSE, glm::value_ptr(cam->matrix));
            glUniformMatrix4fv(objMatrix, 1, GL_FALSE, glm::value_ptr(letter->transform));
            if(letter->chained) glUniform3fv(color, 1, glm::value_ptr(letter->color * glm::vec3(0.6f, 1.0f, 0.6f)));
            else glUniform3fv(color, 1, glm::value_ptr(letter->color));
            letter->model.render();
        }
        tableShader->bind();
        table.render();
    }
    long long lastPressed = 0;
    level(float dist, Camera* cam, int w, int h, int z, std::vector<std::string> validWords, bool* levelComplete): lTransform(glm::rotate(glm::translate(glm::mat4(1.0f),glm::vec3(-w/2.0f + 0.5f,0.0f,-h/2.0f + 0.5f)), glm::radians(90.0f), UP_VECTOR)), tableShader(new Shader(shaders::textured, uniforms(&cam->matrix, assets.getTexture("table.png")),staticUniforms(&lTransform))), table(&models::table), levelComplete(levelComplete), validWords(validWords), cam(cam), player(cam), w(w), h(h), z(z){
        cam->move(glm::vec3(-w/2.0f, 30.0f, dist),glm::vec3(0.0f, -0.6f, -1.0f));
        checkWords();
        hasLetters = true;
    }
    void addLetter(char letter, glm::ivec3 pos){
        letters.push_back(new letterTile(pos,glm::vec3(0.4f, 0.4f, 0.4f),letter,true,false));
    }
    void addTile(glm::ivec3 pos){
        tiles.push_back(new tile(pos, false));
    }
    tile* getTile(glm::ivec3 pos){
        for(auto letter : letters){
            if(letter->pos == pos){
                return letter;
            }
        }
        for(auto tile : tiles){
            if(tile->pos == pos){
                return tile;
            }
        }
        return nullptr;
    }
    virtual void restart(){
        letters.clear();
        player.body.clear();
        hasLetters = true;
    }
    bool move(glm::ivec3 init, glm::ivec3 shift){
        glm::ivec3 newPos = init + shift;
        tile* first = getTile(init);
        tile* next = getTile(newPos);
        if(!(newPos.x >= -1 && newPos.x <= w && newPos.z >= -1 && newPos.z <= h) || (first != nullptr && !first->moveable)) return false;
        else if(first == nullptr) return true;
        else if(move(newPos,shift)){
            first->pos += shift;
            return true;
        }
        return false;
    }
    void movePlayer(glm::ivec3 shift){
        if(move(player.body[0]->pos + shift, shift)){
            player.move(shift);
            checkWords();
            lastPressed = globalTime;
        }
    }
    void clearWords(){
        auto i = letters.begin();
        while(i != letters.end()){
            if((*i)->chained){
                letters.erase(i);
            } else {
                i++;
            }
        }
        if(letters.size() == 0){
            *levelComplete = true;
        }
    }

    void checkWords(){
        std::vector<char*> words;
        std::vector<letterTile**> letterOrder;
        for(int y = 0; y < h; y++){
            words.push_back(new char[w]);
            letterOrder.push_back(new letterTile*[w]);
            for(int x = 0; x < w; x++){
                words[y][x] = ' ';
            }
        }

        for(auto letter : letters){
            words[letter->pos.z][letter->pos.x] = letter->letter;
            letterOrder[letter->pos.z][letter->pos.x] = letter;
        }
        std::vector<std::string> foundWords;
        std::vector<std::vector<letterTile*>> foundLetters;
        for(int y = 0; y < h; y++){
            std::string word;
            bool adj = false;
            std::vector<letterTile*> lettersTemp;
            for(int x = 0; x < w; x++){
                if(words[y][x] != ' '){
                    word.insert(word.begin(), words[y][x]);
                    lettersTemp.push_back(letterOrder[y][x]);
                    adj = true;
                } else {
                    adj = false;
                }
                if((!adj && word.length() > 0) || (x == w - 1 && word.length() > 0)){
                    foundWords.push_back(word);
                    foundLetters.push_back(lettersTemp);
                    word = "";
                    lettersTemp.clear();
                }
            }
        }   
        std::vector<std::vector<letterTile*>> finalLetters;

        for(int i = 0; i < foundWords.size(); i++){
            for(auto word : validWords){
                if(foundWords[i].compare(word) == 0){
                    finalLetters.push_back(foundLetters[i]);
                    printf(foundWords[i].c_str());
                }
            }
        }

        for(auto letter : letters){
            letter->chained = false;
        }

        for(auto word : finalLetters){
            for(auto letter : word){
                letter->chained = true;
            }
        }
    }
};

class LevelManager{
    public:
        bool loaded = false;
        bool* levelComplete;
        Camera* levelCam;
        GLFWwindow* window;

        level* level_p = nullptr;
        LevelManager(Camera* cam, GLFWwindow* window, bool* levelComplete);
        template<typename T>
        void loadLevel(){
            if(level_p != nullptr){
                delete level_p;
            }
            level_p = new T(levelCam, levelComplete);
            loaded = true;
        }
        void update();
        void drawOpaque();
        void drawTransparent();
        void restart();
        bool checkTile(int, int);
};

#endif