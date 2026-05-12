#include "Security.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
using namespace std;

void Security::setSecurityDetails(const string& shift, const string& dept) {
    shiftTiming = shift; assignedDept = dept;
}

void Security::displayInfo() const {
    displayBasicInfo();
    cout << "  Shift : " << shiftTiming << "\n"
        << "  Dept  : " << assignedDept << "\n";
}

void Security::monitorCampus() const {
    cout << "  " << name << " monitoring campus during " << shiftTiming << " shift.\n";
}

void Security::checkEntry(const string& personName) const {
    cout << "  " << name << " checking entry for " << personName << ".\n";
}

void Security::reportIssue() const {
    cout << "  " << name << " reporting an issue.\n";
}

void Security::logGateEntry(const string& personName, const string& gate,
    const string& type, const string& role) const {
    ofstream f("gate_log.txt", ios::app);
    if (!f.is_open()) throw runtime_error("Cannot open gate_log.txt");
    f << "Officer: " << name << " | Person: " << personName
        << " | Role: " << role << " | Gate: " << gate
        << " | Type: " << type << " | Time: " << getCurrentTimestamp() << "\n";
    cout << "  [OK] " << type << " logged for " << personName
        << " at " << gate << ".\n";
}

void Security::saveToFile() const {
    ofstream f("security.txt", ios::app);
    if (!f.is_open()) throw runtime_error("Cannot open security.txt");
    f << "ID: " << id << " | Name: " << name
        << " | Shift: " << shiftTiming << " | Dept: " << assignedDept << "\n"
        << string(50, '-') << "\n";
    cout << "  [OK] Security record saved.\n";
}

void Security::loadAll() {
    ifstream f("security.txt");
    if (!f.is_open()) { cout << "  No security records found.\n"; return; }
    string line;
    cout << "\n";
    while (getline(f, line)) cout << "  " << line << "\n";
}