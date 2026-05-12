#include "AttendanceManager.h"
#include "Utilities.h"
#include "Constants.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
using namespace std;

void AttendanceManager::markCheckIn(const string& studentID) {
    if (studentID.empty()) throw invalid_argument("Student ID is required.");

    cout << "\n";
    int    progIdx = selectProgram();
    string selectedCourse = selectCourse(progIdx);

    cout << "\n  Class duration options:\n"
        << "  1. 60  minutes\n"
        << "  2. 90  minutes (default)\n"
        << "  3. 120 minutes\n";
    int dChoice = getIntInput("  Choice (1-3): ", 1, 3);
    int dur = (dChoice == 1) ? 60 : (dChoice == 3) ? 120 : 90;

    string ts = getCurrentTimestamp();
    ofstream f("attendance.txt", ios::app);
    if (!f.is_open()) throw runtime_error("Cannot open attendance.txt");
    f << "StudentID: " << studentID
        << " | CourseID: " << selectedCourse
        << " | Type: CHECK_IN"
        << " | Duration: " << dur
        << " | Time: " << ts << "\n";
    f.close();

    cout << "\n  [OK] CHECK-IN: " << studentID
        << "\n       Course  : " << selectedCourse
        << "\n       Time    : " << ts
        << "\n       ClassDur: " << dur << " min"
        << "\n       Required: "
        << (int)((MIN_ATTENDANCE_PERCENT / 100.0f) * dur)
        << " min to be marked PRESENT\n";
}

void AttendanceManager::markCheckOut(const string& studentID) {
    if (studentID.empty()) throw invalid_argument("Student ID is required.");

    cout << "\n";
    int    progIdx = selectProgram();
    string selectedCourse = selectCourse(progIdx);

    ifstream inF("attendance.txt");
    if (!inF.is_open()) throw runtime_error("Cannot read attendance.txt");

    int    checkInCount = 0, checkOutCount = 0;
    string lastCheckInTime;
    int    lastDur = CLASS_DURATION_MINUTES;
    string line;

    while (getline(inF, line)) {
        if (line.find("StudentID: " + studentID) == string::npos) continue;
        if (line.find("CourseID: " + selectedCourse) == string::npos) continue;
        if (line.find("CHECK_IN") != string::npos) {
            checkInCount++;
            lastCheckInTime = line.substr(line.rfind("Time: ") + 6);
            size_t dp = line.find("Duration: ");
            if (dp != string::npos) lastDur = stoi(line.substr(dp + 10));
        }
        if (line.find("CHECK_OUT") != string::npos) checkOutCount++;
    }
    inF.close();

    if (checkInCount <= checkOutCount)
        throw runtime_error("No active CHECK_IN found for " + studentID +
            " in " + selectedCourse + ". Please check in first.");

    string ts = getCurrentTimestamp();
    ofstream outF("attendance.txt", ios::app);
    if (!outF.is_open()) throw runtime_error("Cannot open attendance.txt");
    outF << "StudentID: " << studentID
        << " | CourseID: " << selectedCourse
        << " | Type: CHECK_OUT"
        << " | Time: " << ts << "\n";
    outF.close();

    int inSec = timeToSeconds(lastCheckInTime);
    int outSec = timeToSeconds(ts);
    int diff = outSec - inSec;
    if (diff < 0) diff = 0;
    int mins = diff / 60;
    int secs = diff % 60;
    int req = (int)((MIN_ATTENDANCE_PERCENT / 100.0f) * lastDur);
    bool present = (mins >= req);

    cout << "\n  ============================================\n";
    cout << "       ATTENDANCE RESULT\n";
    cout << "  ============================================\n";
    cout << "  Student  : " << studentID << "\n";
    cout << "  Course   : " << selectedCourse << "\n";
    cout << "  Check-in : " << lastCheckInTime << "\n";
    cout << "  Check-out: " << ts << "\n";
    cout << "  Duration : " << mins << " min " << secs << " sec\n";
    cout << "  Required : " << req << " min\n";
    cout << "  Status   : " << (present ? "PRESENT" : "ABSENT") << "\n";
    cout << "  ============================================\n";
}

void AttendanceManager::calculatePresenceDuration(const string& studentID,
    const string& courseID) {
    ifstream f("attendance.txt");
    if (!f.is_open()) throw runtime_error("Cannot open attendance.txt");

    string checkInTime, checkOutTime;
    int    classDur = CLASS_DURATION_MINUTES;
    string line;

    while (getline(f, line)) {
        if (line.find("StudentID: " + studentID) == string::npos) continue;
        if (line.find("CourseID: " + courseID) == string::npos) continue;
        string ts = line.substr(line.rfind("Time: ") + 6);
        if (line.find("CHECK_IN") != string::npos) {
            checkInTime = ts;
            size_t dp = line.find("Duration: ");
            if (dp != string::npos) classDur = stoi(line.substr(dp + 10));
        }
        if (line.find("CHECK_OUT") != string::npos) checkOutTime = ts;
    }
    f.close();

    printHeader("ATTENDANCE REPORT");
    cout << "  Student  : " << studentID << "\n"
        << "  Course   : " << courseID << "\n";

    if (checkInTime.empty()) {
        cout << "  Status   : No check-in record found.\n";
        return;
    }

    cout << "  Check-in : " << checkInTime << "\n";

    if (checkOutTime.empty()) {
        cout << "  Check-out: Still in class / not checked out.\n"
            << "  Status   : PRESENT (attending)\n";
        return;
    }

    cout << "  Check-out: " << checkOutTime << "\n";

    int inSec = timeToSeconds(checkInTime);
    int outSec = timeToSeconds(checkOutTime);
    int diff = outSec - inSec;
    if (diff < 0) { cout << "  [!] Check-out time is before check-in.\n"; return; }

    int hours = diff / 3600;
    int mins = (diff % 3600) / 60;
    int secs = diff % 60;
    int req = (int)((MIN_ATTENDANCE_PERCENT / 100.0f) * classDur);

    cout << "  Duration : " << hours << "h " << mins << "m " << secs << "s\n"
        << "  Required : " << req << " min (" << MIN_ATTENDANCE_PERCENT
        << "% of " << classDur << " min class)\n"
        << "  Status   : " << ((mins + hours * 60) >= req ? "PRESENT" : "ABSENT") << "\n";
}

void AttendanceManager::viewCourseAttendance(const string& courseID) {
    ifstream f("attendance.txt");
    if (!f.is_open()) throw runtime_error("Cannot open attendance.txt");

    printHeader("ATTENDANCE LOG: " + courseID);
    string line;
    bool   found = false;
    while (getline(f, line)) {
        if (line.find("CourseID: " + courseID) != string::npos) {
            cout << "  " << line << "\n";
            found = true;
        }
    }
    if (!found) cout << "  No records found for course: " << courseID << "\n";
    f.close();
}

void AttendanceManager::viewAllAttendance() {
    ifstream f("attendance.txt");
    if (!f.is_open()) { cout << "  No attendance records found.\n"; return; }
    printHeader("FULL ATTENDANCE LOG");
    string line;
    while (getline(f, line)) cout << "  " << line << "\n";
    f.close();
}