#pragma once
#include "Person.h"

class Security : public Person {
    string shiftTiming, assignedDept;
public:
    void setSecurityDetails(const string& shift, const string& dept);
    void displayInfo()  const;
    void monitorCampus() const;
    void checkEntry(const string& personName) const;
    void reportIssue()  const;
    void logGateEntry(const string& personName, const string& gate,
        const string& type, const string& role) const;
    void saveToFile()   const;
    static void loadAll();
};
