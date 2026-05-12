#include "Course.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

void Course::setDetails(const string& id, const string& name,
    int credits, const string& instrID) {
    if (credits < 1 || credits > 6)
        throw invalid_argument("Credit hours must be 1-6.");
    courseID = id; courseName = name;
    creditHours = credits; instructorID = instrID;
}

void Course::displayInfo() const {
    cout << "  ID      : " << courseID << "\n"
        << "  Name    : " << courseName << "\n"
        << "  Credits : " << creditHours << "\n"
        << "  Instr.  : " << instructorID << "\n";
}

void Course::saveToFile() const {
    ofstream f("courses.txt", ios::app);
    if (!f.is_open()) throw runtime_error("Cannot open courses.txt");
    f << "ID: " << courseID << " | Name: " << courseName
        << " | Credits: " << creditHours
        << " | Instructor: " << instructorID << "\n"
        << string(50, '-') << "\n";
    cout << "  [OK] Course record saved.\n";
}

void Course::loadAll() {
    ifstream f("courses.txt");
    if (!f.is_open()) { cout << "  No course records found.\n"; return; }
    string line;
    cout << "\n";
    while (getline(f, line)) cout << "  " << line << "\n";
}

void Course::assignInstructor(const string& instrID) {
    instructorID = instrID;
    cout << "  Instructor " << instrID << " assigned to " << courseName << ".\n";
}