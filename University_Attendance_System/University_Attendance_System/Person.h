#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

class Person {
protected:
    string id, name, email, phone;
public:
    void setBasicInfo(const string& i, const string& n,
        const string& e, const string& p) {
        if (i.empty() || n.empty() || e.empty() || p.empty())
            throw invalid_argument("All fields (ID, Name, Email, Phone) are required.");
        id = i; name = n; email = e; phone = p;
    }
    string getID()   const { return id; }
    string getName() const { return name; }

    void displayBasicInfo() const {
        cout << "  ID    : " << id << "\n"
            << "  Name  : " << name << "\n"
            << "  Email : " << email << "\n"
            << "  Phone : " << phone << "\n";
    }
    void saveToFile(const string& filename = "persons.txt") const {
        ofstream f(filename, ios::app);
        if (!f.is_open()) throw runtime_error("Cannot open " + filename);
        f << "ID: " << id << " | Name: " << name
            << " | Email: " << email << " | Phone: " << phone << "\n"
            << string(50, '-') << "\n";
    }
    virtual ~Person() {}
};