#include "Menus.h"
#include "Utilities.h"
#include "Student.h"
#include "Faculty.h"
#include "Security.h"
#include "Gate.h"
#include "Course.h"
#include "Report.h"
#include "Schedule.h"
#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

void showStudentMenu(AttendanceManager& am) {
    string studentID, studentName;
    cout << "\n  Enter Student ID   : "; getline(cin, studentID);
    cout << "  Enter Student Name : "; getline(cin, studentName);
    if (studentID.empty()) { cout << "  [!] Student ID is required.\n"; return; }

    int choice;
    do {
        cout << "\n";
        printHeader("STUDENT PORTAL  [" + studentID + " - " + studentName + "]");
        cout << "  1. Mark Check-in\n"
            << "  2. Mark Check-out\n"
            << "  3. View My Attendance Duration\n"
            << "  4. View My Full Attendance Log\n"
            << "  0. Logout\n";
        printLine();
        choice = getIntInput("  Choice: ", 0, 4);

        try {
            if (choice == 1) {
                am.markCheckIn(studentID);
            }
            else if (choice == 2) {
                am.markCheckOut(studentID);
            }
            else if (choice == 3) {
                cout << "\n";
                int    pi = selectProgram();
                string cid = selectCourse(pi);
                am.calculatePresenceDuration(studentID, cid);
            }
            else if (choice == 4) {
                ifstream f("attendance.txt");
                if (!f.is_open()) { cout << "  No records found.\n"; }
                else {
                    printHeader("MY ATTENDANCE LOG");
                    string line;
                    bool   found = false;
                    while (getline(f, line)) {
                        if (line.find("StudentID: " + studentID) != string::npos) {
                            cout << "  " << line << "\n";
                            found = true;
                        }
                    }
                    if (!found) cout << "  No records found for " << studentID << ".\n";
                }
            }
        }
        catch (const exception& e) {
            cout << "  [!] Error: " << e.what() << "\n";
        }

        if (choice != 0) pauseScreen();

    } while (choice != 0);
    cout << "  Logged out.\n";
}

void showFacultyMenu(AttendanceManager& am) {
    string facID, facName, desig, dept;
    cout << "\n  Faculty ID           : "; getline(cin, facID);
    cout << "  Name                 : "; getline(cin, facName);
    cout << "  Designation          : "; getline(cin, desig);
    cout << "  Department (CS/AI/IT): "; getline(cin, dept);
    if (facID.empty()) { cout << "  [!] Faculty ID required.\n"; return; }

    Faculty fac;
    try {
        fac.setBasicInfo(facID, facName, "faculty@uni.edu", "0000-0000000");
        fac.setFacultyDetails(desig, dept);
    }
    catch (const exception& e) { cout << "  [!] " << e.what() << "\n"; }

    int choice;
    do {
        cout << "\n";
        printHeader("FACULTY PORTAL  [" + facID + " - " + facName + "]");
        cout << "  1. View Attendance for a Course\n"
            << "  2. Check Student Attendance Duration\n"
            << "  3. Mark Class Attendance (Session)\n"
            << "  4. View My Info\n"
            << "  5. Save Faculty Record to File\n"
            << "  6. View All Faculty Records\n"
            << "  7. View Saved Schedules\n"
            << "  0. Logout\n";
        printLine();
        choice = getIntInput("  Choice: ", 0, 7);

        try {
            if (choice == 1) {
                cout << "\n";
                int    pi = selectProgram();
                string cid = selectCourse(pi);
                am.viewCourseAttendance(cid);
            }
            else if (choice == 2) {
                string sid;
                cout << "\n  Student ID : "; getline(cin, sid);
                cout << "\n";
                int    pi = selectProgram();
                string cid = selectCourse(pi);
                am.calculatePresenceDuration(sid, cid);
            }
            else if (choice == 3) {
                fac.markAttendance();
                cout << "  Session recorded at: " << getCurrentTimestamp() << "\n";
                ofstream f("attendance.txt", ios::app);
                if (f.is_open())
                    f << "Faculty: " << facID
                    << " | Session at: " << getCurrentTimestamp() << "\n";
            }
            else if (choice == 4) { fac.displayInfo(); }
            else if (choice == 5) { fac.saveToFile(); }
            else if (choice == 6) { Faculty::loadAll(); }
            else if (choice == 7) { Schedule::loadAll(); }
        }
        catch (const exception& e) {
            cout << "  [!] Error: " << e.what() << "\n";
        }

        if (choice != 0) pauseScreen();

    } while (choice != 0);
    cout << "  Logged out.\n";
}

void showSecurityMenu() {
    string secID, secName, email, phone, shift, dept;
    cout << "\n  Security ID          : "; getline(cin, secID);
    cout << "  Name                 : "; getline(cin, secName);
    cout << "  Email                : "; getline(cin, email);
    cout << "  Phone                : "; getline(cin, phone);
    cout << "  Shift (Morning/Evening/Night): "; getline(cin, shift);
    cout << "  Assigned Dept        : "; getline(cin, dept);

    Security sec;
    try {
        sec.setBasicInfo(secID, secName, email, phone);
        sec.setSecurityDetails(shift, dept);
    }
    catch (const exception& e) { cout << "  [!] " << e.what() << "\n"; return; }

    Gate gates[3];
    gates[0].setDetails(1, "Main Gate (North)", true);
    gates[1].setDetails(2, "East Gate", true);
    gates[2].setDetails(3, "West Gate (Staff)", false);

    int choice;
    do {
        cout << "\n";
        printHeader("SECURITY PORTAL  [" + secID + " - " + secName + "]");
        cout << "  1. Log Campus Entry\n"
            << "  2. Log Campus Exit\n"
            << "  3. View Gate Entry Log\n"
            << "  4. Gate Status & Control\n"
            << "  5. Report Security Incident\n"
            << "  6. Monitor Campus\n"
            << "  7. View My Info\n"
            << "  8. Save Security Record\n"
            << "  9. View All Security Records\n"
            << "  0. Logout\n";
        printLine();
        choice = getIntInput("  Choice: ", 0, 9);

        try {
            if (choice == 1 || choice == 2) {
                string type = (choice == 1) ? "ENTRY" : "EXIT";
                string person, role, gate;
                cout << "\n  Person Name/ID : "; getline(cin, person);
                cout << "  Role (Student/Faculty/Admin/Visitor): "; getline(cin, role);
                cout << "  Gate:\n"
                    << "  1. Gate 1 - Main\n"
                    << "  2. Gate 2 - East\n"
                    << "  3. Gate 3 - West\n";
                int gc = getIntInput("  Choice: ", 1, 3);
                gate = "Gate " + to_string(gc);
                sec.logGateEntry(person, gate, type, role);
            }
            else if (choice == 3) {
                ifstream f("gate_log.txt");
                if (!f.is_open()) { cout << "  No gate log found.\n"; }
                else {
                    printHeader("GATE ENTRY LOG");
                    string line;
                    while (getline(f, line)) cout << "  " << line << "\n";
                }
            }
            else if (choice == 4) {
                printHeader("GATE STATUS");
                for (int i = 0; i < 3; i++) gates[i].displayInfo();
                cout << "\n  Which gate to control?\n"
                    << "  1. Gate 1   2. Gate 2   3. Gate 3   0. Back\n";
                int gc = getIntInput("  Choice: ", 0, 3);
                if (gc > 0) {
                    cout << "  1. Open   2. Close\n";
                    int oc = getIntInput("  Choice: ", 1, 2);
                    if (oc == 1) gates[gc - 1].open();
                    else         gates[gc - 1].close();
                }
            }
            else if (choice == 5) {
                string itype, loc, detail;
                cout << "\n  Incident Type:\n"
                    << "  1. Unauthorized Entry\n"
                    << "  2. Suspicious Behaviour\n"
                    << "  3. Equipment Damage\n"
                    << "  4. Other\n";
                int it = getIntInput("  Choice: ", 1, 4);
                string types[] = { "Unauthorized Entry","Suspicious Behaviour",
                                   "Equipment Damage","Other" };
                itype = types[it - 1];
                cout << "  Location : "; getline(cin, loc);
                cout << "  Details  : "; getline(cin, detail);
                ofstream f("incidents.txt", ios::app);
                if (!f.is_open()) throw runtime_error("Cannot open incidents.txt");
                f << "Officer: " << secID << " | Type: " << itype
                    << " | Location: " << loc << " | Detail: " << detail
                    << " | Time: " << getCurrentTimestamp() << "\n"
                    << string(50, '-') << "\n";
                cout << "  [OK] Incident report submitted.\n";
            }
            else if (choice == 6) { sec.monitorCampus(); }
            else if (choice == 7) { sec.displayInfo(); }
            else if (choice == 8) { sec.saveToFile(); }
            else if (choice == 9) { Security::loadAll(); }
        }
        catch (const exception& e) {
            cout << "  [!] Error: " << e.what() << "\n";
        }

        if (choice != 0) pauseScreen();

    } while (choice != 0);
    cout << "  Logged out.\n";
}

void showAdminMenu(AttendanceManager& am, FileManager& fm) {
    int choice;
    do {
        cout << "\n";
        printHeader("ADMINISTRATION MENU");
        cout << "  -: Attendance :-\n"
            << "  1.  Check Student Attendance Duration\n"
            << "  2.  View All Attendance for a Course\n"
            << "  3.  View Full Attendance Log\n"
            << "  -: Reports :-\n"
            << "  4.  Create & Save Report\n"
            << "  5.  View Saved Reports\n"
            << "  -: Records :-\n"
            << "  6.  Add Student Record\n"
            << "  7.  View All Student Records\n"
            << "  8.  Add Course Record\n"
            << "  9.  View All Course Records\n"
            << "  -: Schedule :-\n"
            << "  10. Add / Update Class Schedule\n"
            << "  11. View All Schedules\n"
            << "  -: Personnel :-\n"
            << "  12. View Faculty Info (from file)\n"
            << "  13. View Security Info (from file)\n"
            << "  -: File Management :-\n"
            << "  14. Clear Attendance File\n"
            << "  15. Clear ALL Files\n"
            << "  16. List All Files\n"
            << "  0.  Logout\n";
        printLine();
        choice = getIntInput("  Choice: ", 0, 16);

        try {
            if (choice == 1) {
                string sid;
                cout << "\n  Student ID : "; getline(cin, sid);
                cout << "\n";
                int    pi = selectProgram();
                string cid = selectCourse(pi);
                am.calculatePresenceDuration(sid, cid);
            }
            else if (choice == 2) {
                cout << "\n";
                int    pi = selectProgram();
                string cid = selectCourse(pi);
                am.viewCourseAttendance(cid);
            }
            else if (choice == 3) { am.viewAllAttendance(); }
            else if (choice == 4) {
                Report r;
                string id, title, desc, date, rtype;
                cout << "\n  Report ID   : "; getline(cin, id);
                cout << "  Title       : "; getline(cin, title);
                cout << "  Description : "; getline(cin, desc);
                cout << "  Date (blank for now): "; getline(cin, date);
                cout << "  Type (Attendance/Performance/General): "; getline(cin, rtype);
                if (rtype.empty()) rtype = "General";
                r.setDetails(id, title, desc, date, rtype);
                r.displayInfo();
                r.saveToFile();
            }
            else if (choice == 5) { Report::loadAll(); }
            else if (choice == 6) {
                Student s;
                string id, name, email, phone, dept;
                float  cgpa;
                cout << "\n  Student ID  : "; getline(cin, id);
                cout << "  Name        : "; getline(cin, name);
                cout << "  Email       : "; getline(cin, email);
                cout << "  Phone       : "; getline(cin, phone);
                cout << "  Department  : "; getline(cin, dept);
                cgpa = getFloatInput("  CGPA (0.0-4.0): ", 0.0f, 4.0f);
                s.setBasicInfo(id, name, email, phone);
                s.setStudentDetails(cgpa, dept);
                s.saveToFile();
            }
            else if (choice == 7) { Student::loadAll(); }
            else if (choice == 8) {
                Course c;
                string cid, cname, instrID;
                cout << "\n  Course ID    : "; getline(cin, cid);
                cout << "  Course Name  : "; getline(cin, cname);
                cout << "  Instructor ID: "; getline(cin, instrID);
                int credits = getIntInput("  Credit Hours (1-6): ", 1, 6);
                c.setDetails(cid, cname, credits, instrID);
                c.saveToFile();
            }
            else if (choice == 9) { Course::loadAll(); }
            else if (choice == 10) {
                cout << "\n";
                int    pi = selectProgram();
                string cid = selectCourse(pi);
                Schedule sc;
                string sid, day, time;
                cout << "\n  Schedule ID  : "; getline(cin, sid);
                cout << "  Day          : "; getline(cin, day);
                cout << "  Time (HH:MM) : "; getline(cin, time);
                int room = getIntInput("  Room No      : ", 1, 999);
                cout << "  Duration:\n"
                    << "  1. 60 min   2. 90 min   3. 120 min\n";
                int dc = getIntInput("  Choice: ", 1, 3);
                int dur = (dc == 1) ? 60 : (dc == 3) ? 120 : 90;
                sc.setDetails(sid, cid, day, time, room, dur);
                sc.displayInfo();
                sc.saveToFile();
            }
            else if (choice == 11) { Schedule::loadAll(); }
            else if (choice == 12) { Faculty::loadAll(); }
            else if (choice == 13) { Security::loadAll(); }
            else if (choice == 14) { fm.clearFile("attendance.txt"); }
            else if (choice == 15) {
                char confirm;
                cout << "\n  [!] Clear ALL data files? (y/n): ";
                cin >> confirm;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (confirm == 'y' || confirm == 'Y') fm.clearAll();
                else cout << "  Cancelled.\n";
            }
            else if (choice == 16) { fm.listFiles(); }
        }
        catch (const exception& e) {
            cout << "  [!] Error: " << e.what() << "\n";
        }

        if (choice != 0) pauseScreen();

    } while (choice != 0);
    cout << "  Admin logged out.\n";
}