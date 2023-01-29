#include"core/fs.h"

void getFilePath(char* init, const char* join){
    strcpy(init,CWD);
    strcat(init,join);
}