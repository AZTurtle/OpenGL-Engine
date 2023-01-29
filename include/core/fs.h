#ifndef FS_CLASS_H
#define FS_CLASS_H

#include<iostream>
#include<string.h>

inline const unsigned int MAX_CWD = 1024;
inline char CWD[MAX_CWD];

void getFilePath(char* init, const char* join);

#endif