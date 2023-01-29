#include"level.h"

LevelManager::LevelManager(Camera* cam, GLFWwindow* window, bool* levelComplete) : window(window), levelCam(cam), levelComplete(levelComplete){}

void LevelManager::drawOpaque(){
    level_p->draw();
}

void LevelManager::drawTransparent(){
    level_p->drawTransparent();
}

bool LevelManager::checkTile(int x, int y){
    if(loaded){
        if(x < 0 || y < 0 || x > level_p->w - 1 || y > level_p->h - 1) return true;
    }
    return false;
}

void LevelManager::update(){
    level_p->update();
}

void LevelManager::restart(){
    level_p->restart();
}