#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Utilities.h"
using namespace std;

class FileManager {
    vector<string> fileList = {
        "students.txt", "persons.txt", "courses.txt", "reports.txt",
        "login_history.txt", "attendance.txt", "schedules.txt",
        "faculty.txt", "security.txt", "gate_log.txt", "incidents.txt"
    };
public:
    void clearFile(const string& fname) {
        ofstream f(fname, ios::trunc);
        if (!f.is_open()) { cout << "  [!] Could not clear " << fname << "\n"; return; }
        cout << "  [OK] " << fname << " cleared.\n";
    }
    void clearAll() {
        cout << "\n  Clearing all files...\n";
        for (auto& fn : fileList) clearFile(fn);
        cout << "  All files cleared.\n";
    }
    void listFiles() {
        printHeader("REGISTERED FILES");
        for (auto& fn : fileList) {
            ifstream f(fn);
            cout << "  " << setw(25) << left << fn
                << (f.is_open() ? " [EXISTS]" : " [NOT FOUND]") << "\n";
        }
    }
};