#ifndef TIME_CLASS_H
#define TIME_CLASS_H

#include<chrono>
#include<iostream>

using namespace std::chrono;

extern milliseconds global_time;
extern float delta_time;
extern long long globalTime;

void update_time();

#endif