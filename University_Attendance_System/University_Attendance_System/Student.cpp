#include "Student.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
using namespace std;

void Student::setStudentDetails(float g, const string& dept) {
    if (g < 0.0f || g > 4.0f)
        throw invalid_argument("CGPA must be between 0.0 and 4.0.");
    cgpa = g; department = dept;
}

void Student::displayInfo() const {
    displayBasicInfo();
    cout << "  CGPA  : " << fixed << setprecision(2) << cgpa << "\n"
        << "  Dept  : " << department << "\n";
}

void Student::saveToFile() const {
    ofstream f("students.txt", ios::app);
    if (!f.is_open()) throw runtime_error("Cannot open students.txt");
    f << "ID: " << id << " | Name: " << name
        << " | CGPA: " << fixed << setprecision(2) << cgpa
        << " | Dept: " << department << "\n"
        << string(50, '-') << "\n";
    cout << "  [OK] Student record saved.\n";
}

void Student::loadAll() {
    ifstream f("students.txt");
    if (!f.is_open()) { cout << "  No student records found.\n"; return; }
    string line;
    cout << "\n";
    while (getline(f, line)) cout << "  " << line << "\n";
}

void Student::enrollCourse(const string& cName) const {
    cout << "  " << name << " enrolled in: " << cName << "\n";
}