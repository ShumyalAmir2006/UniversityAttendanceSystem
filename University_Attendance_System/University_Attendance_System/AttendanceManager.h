#pragma once
#include <string>
using namespace std;

class AttendanceManager {
public:
    void markCheckIn(const string& studentID);
    void markCheckOut(const string& studentID);
    void calculatePresenceDuration(const string& studentID, const string& courseID);
    void viewCourseAttendance(const string& courseID);
    void viewAllAttendance();
};