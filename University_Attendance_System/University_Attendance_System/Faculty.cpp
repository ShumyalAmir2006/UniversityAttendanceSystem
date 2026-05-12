#include "Faculty.h"
#include <iostream>
#include <fstream>
using namespace std;

void Faculty::setFacultyDetails(const string& desig, const string& dept) {
    designation = desig; department = dept;
}

void Faculty::displayInfo() const {
    displayBasicInfo();
    cout << "  Desig : " << designation << "\n"
        << "  Dept  : " << department << "\n";
}

void Faculty::assignCourse(const string& cName) const {
    cout << "  Assigning course: " << cName << " to " << name << "\n";
}

void Faculty::markAttendance() const {
    cout << "  " << name << " marked attendance.\n";
}

void Faculty::saveToFile() const {
    ofstream f("faculty.txt", ios::app);
    if (!f.is_open()) throw runtime_error("Cannot open faculty.txt");
    f << "ID: " << id << " | Name: " << name
        << " | Desig: " << designation << " | Dept: " << department << "\n"
        << string(50, '-') << "\n";
    cout << "  [OK] Faculty record saved.\n";
}

void Faculty::loadAll() {
    ifstream f("faculty.txt");
    if (!f.is_open()) { cout << "  No faculty records found.\n"; return; }
    string line;
    cout << "\n";
    while (getline(f, line)) cout << "  " << line << "\n";
}