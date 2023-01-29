#include"core/input.h"

bool isKeyPressed = false;
char lastKeyPressed = '\0';

void getInputInfo(){
    isKeyPressed = false;
    lastKeyPressed = '\0';
    for(unsigned short i = 0; i < 256; i++){
        if(GetKeyState(i) & 0x8000){
            isKeyPressed = true;
            lastKeyPressed = i;
        }
    }
}