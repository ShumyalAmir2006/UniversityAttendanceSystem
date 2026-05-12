#pragma once
#include <string>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

const int   CLASS_DURATION_MINUTES = 90;
const float MIN_ATTENDANCE_PERCENT = 75.0f;
const int   MIN_MINUTES_REQUIRED = (int)((MIN_ATTENDANCE_PERCENT / 100.0f) * CLASS_DURATION_MINUTES);
const int   NUM_PROGRAMS = 3;
const int   NUM_COURSES = 4;

extern string programs[NUM_PROGRAMS];
extern string courses[NUM_PROGRAMS][NUM_COURSES];