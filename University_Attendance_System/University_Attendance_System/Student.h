#pragma once
#include "Person.h"
#include <iomanip>

class Student : public Person {
    float  cgpa = 0.0f;
    string department;
public:
    void   setStudentDetails(float g, const string& dept);
    float  getCGPA() const { return cgpa; }
    string getDept() const { return department; }
    void   displayInfo()  const;
    void   saveToFile()   const;
    static void loadAll();
    void   enrollCourse(const string& cName) const;
};
