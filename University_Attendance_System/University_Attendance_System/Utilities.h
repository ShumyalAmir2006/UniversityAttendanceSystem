#pragma once
#include <string>
#include <limits>
using namespace std;

void   clearScreen();
void   pauseScreen();
string getCurrentTimestamp();
int    timeToSeconds(const string& ts);
void   printLine(char c = '-', int len = 55);
void   printHeader(const string& title);
int    getIntInput(const string& prompt, int lo, int hi);
float  getFloatInput(const string& prompt, float lo, float hi);
int    selectProgram();
string selectCourse(int progIdx);
