#pragma once
#include "Person.h"

class Administration : public Person {
    string role;
public:
    void setRole(const string& r) { role = r; }
    void displayInfo()    const { displayBasicInfo(); cout << "  Role  : " << role << "\n"; }
    void manageRecords()  const { cout << "  " << role << " managing university records.\n"; }
    void generateReport() const { cout << "  " << name << " generating report.\n"; }
};