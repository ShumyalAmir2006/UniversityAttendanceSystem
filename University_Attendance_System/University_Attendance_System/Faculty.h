#pragma once
#include "Person.h"

class Faculty : public Person {
    string designation, department;
public:
    void   setFacultyDetails(const string& desig, const string& dept);
    string getDept() const { return department; }
    void   displayInfo()   const;
    void   assignCourse(const string& cName) const;
    void   markAttendance() const;
    void   saveToFile()    const;
    static void loadAll();
};