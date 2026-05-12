#pragma once
#include <string>
using namespace std;

class Course {
    string courseID, courseName, instructorID;
    int    creditHours = 3;
public:
    void setDetails(const string& id, const string& name,
        int credits, const string& instrID);
    void displayInfo()  const;
    void saveToFile()   const;
    static void loadAll();
    void assignInstructor(const string& instrID);
};