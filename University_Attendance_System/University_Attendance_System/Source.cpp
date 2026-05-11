#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <stdexcept>
#include <algorithm>
#include <limits>

using namespace std;

// ═══════════════════════════════════════════════════════════════════
//  CONSTANTS & PROGRAM DATA
// ═══════════════════════════════════════════════════════════════════

const int    CLASS_DURATION_MINUTES = 90;
const float  MIN_ATTENDANCE_PERCENT = 75.0f;
const int    MIN_MINUTES_REQUIRED = (int)((MIN_ATTENDANCE_PERCENT / 100.0f) * CLASS_DURATION_MINUTES);

const int    NUM_PROGRAMS = 3;
const int    NUM_COURSES = 4;

string programs[NUM_PROGRAMS] = { "CS", "AI", "IT" };

string courses[NUM_PROGRAMS][NUM_COURSES] = {
    { "CS101-Programming", "CS102-DataStructures", "CS103-OOP", "CS104-Algorithms"         },
    { "AI101-MachineLearning", "AI102-NeuralNetworks", "AI103-ComputerVision", "AI104-NLP" },
    { "IT101-Networking", "IT102-DatabaseSystems", "IT103-WebDev", "IT104-CyberSecurity"   }
};

// ═══════════════════════════════════════════════════════════════════
//  UTILITY HELPERS
// ═══════════════════════════════════════════════════════════════════

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    cout << "\n  Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

string getCurrentTimestamp() {
    time_t now = time(nullptr);
    tm* t = localtime(&now);
    ostringstream oss;
    oss << put_time(t, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

// Returns seconds-since-midnight from a full timestamp string "YYYY-MM-DD HH:MM:SS"
int timeToSeconds(const string& ts) {
    int h = 0, m = 0, s = 0;
    if (ts.size() >= 19)
        sscanf(ts.c_str() + 11, "%d:%d:%d", &h, &m, &s);
    return h * 3600 + m * 60 + s;
}

void printLine(char c = '-', int len = 55) {
    cout << string(len, c) << endl;
}

void printHeader(const string& title) {
    printLine('=');
    cout << "  " << title << endl;
    printLine('=');
}

// Safe integer input
int getIntInput(const string& prompt, int lo, int hi) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= lo && val <= hi) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [!] Invalid input. Enter a number between " << lo << " and " << hi << ".\n";
    }
}

// Safe float input
float getFloatInput(const string& prompt, float lo, float hi) {
    float val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= lo && val <= hi) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [!] Invalid input. Enter a value between " << lo << " and " << hi << ".\n";
    }
}

// ═══════════════════════════════════════════════════════════════════
//  PROGRAM / COURSE SELECTION MENUS
// ═══════════════════════════════════════════════════════════════════

int selectProgram() {
    cout << "\n  -- Select Program --\n";
    for (int i = 0; i < NUM_PROGRAMS; i++)
        cout << "  " << i + 1 << ". " << programs[i] << "\n";
    return getIntInput("  Choice (1-3): ", 1, NUM_PROGRAMS) - 1;
}

string selectCourse(int progIdx) {
    cout << "\n  -- Select Course for " << programs[progIdx] << " --\n";
    for (int i = 0; i < NUM_COURSES; i++)
        cout << "  " << i + 1 << ". " << courses[progIdx][i] << "\n";
    int c = getIntInput("  Choice (1-4): ", 1, NUM_COURSES);
    return courses[progIdx][c - 1];
}

// ═══════════════════════════════════════════════════════════════════
//  CLASS: Person  (base)
// ═══════════════════════════════════════════════════════════════════

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

// ═══════════════════════════════════════════════════════════════════
//  CLASS: Login
// ═══════════════════════════════════════════════════════════════════

class Login {
public:
    string username, password;
    bool   authenticated = false;
};

// ═══════════════════════════════════════════════════════════════════
//  CLASS: Student
// ═══════════════════════════════════════════════════════════════════

class Student : public Person {
    float  cgpa = 0.0f;
    string department;
public:
    void setStudentDetails(float g, const string& dept) {
        if (g < 0.0f || g > 4.0f)
            throw invalid_argument("CGPA must be between 0.0 and 4.0.");
        cgpa = g; department = dept;
    }
    float  getCGPA()  const { return cgpa; }
    string getDept()  const { return department; }

    void displayInfo() const {
        displayBasicInfo();
        cout << "  CGPA  : " << fixed << setprecision(2) << cgpa << "\n"
            << "  Dept  : " << department << "\n";
    }
    void saveToFile() const {
        ofstream f("students.txt", ios::app);
        if (!f.is_open()) throw runtime_error("Cannot open students.txt");
        f << "ID: " << id << " | Name: " << name
            << " | CGPA: " << fixed << setprecision(2) << cgpa
            << " | Dept: " << department << "\n"
            << string(50, '-') << "\n";
        cout << "  [OK] Student record saved.\n";
    }
    static void loadAll() {
        ifstream f("students.txt");
        if (!f.is_open()) { cout << "  No student records found.\n"; return; }
        string line;
        cout << "\n";
        while (getline(f, line)) cout << "  " << line << "\n";
    }
    void enrollCourse(const string& cName) const {
        cout << "  " << name << " enrolled in: " << cName << "\n";
    }
};

// ═══════════════════════════════════════════════════════════════════
//  CLASS: Administration
// ═══════════════════════════════════════════════════════════════════

class Administration : public Person {
    string role;
public:
    void setRole(const string& r) { role = r; }
    void displayInfo() const {
        displayBasicInfo();
        cout << "  Role  : " << role << "\n";
    }
    void manageRecords() const { cout << "  " << role << " managing university records.\n"; }
    void generateReport() const { cout << "  " << name << " generating report.\n"; }
};

// ═══════════════════════════════════════════════════════════════════
//  CLASS: Faculty
// ═══════════════════════════════════════════════════════════════════

class Faculty : public Person {
    string designation, department;
public:
    void setFacultyDetails(const string& desig, const string& dept) {
        designation = desig; department = dept;
    }
    string getDept() const { return department; }

    void displayInfo() const {
        displayBasicInfo();
        cout << "  Desig : " << designation << "\n"
            << "  Dept  : " << department << "\n";
    }
    void assignCourse(const string& cName) const {
        cout << "  Assigning course: " << cName << " to " << name << "\n";
    }
    void markAttendance() const {
        cout << "  " << name << " marked attendance.\n";
    }
    void saveToFile() const {
        ofstream f("faculty.txt", ios::app);
        if (!f.is_open()) throw runtime_error("Cannot open faculty.txt");
        f << "ID: " << id << " | Name: " << name
            << " | Desig: " << designation << " | Dept: " << department << "\n"
            << string(50, '-') << "\n";
        cout << "  [OK] Faculty record saved.\n";
    }
    static void loadAll() {
        ifstream f("faculty.txt");
        if (!f.is_open()) { cout << "  No faculty records found.\n"; return; }
        string line;
        cout << "\n";
        while (getline(f, line)) cout << "  " << line << "\n";
    }
};

// ═══════════════════════════════════════════════════════════════════
//  CLASS: Security
// ═══════════════════════════════════════════════════════════════════

class Security : public Person {
    string shiftTiming, assignedDept;
public:
    void setSecurityDetails(const string& shift, const string& dept) {
        shiftTiming = shift; assignedDept = dept;
    }
    void displayInfo() const {
        displayBasicInfo();
        cout << "  Shift : " << shiftTiming << "\n"
            << "  Dept  : " << assignedDept << "\n";
    }
    void monitorCampus() const {
        cout << "  " << name << " monitoring campus during " << shiftTiming << " shift.\n";
    }
    void checkEntry(const string& personName) const {
        cout << "  " << name << " checking entry for " << personName << ".\n";
    }
    void reportIssue() const {
        cout << "  " << name << " reporting an issue.\n";
    }
    void logGateEntry(const string& personName, const string& gate,
        const string& type, const string& role) const {
        ofstream f("gate_log.txt", ios::app);
        if (!f.is_open()) throw runtime_error("Cannot open gate_log.txt");
        f << "Officer: " << name << " | Person: " << personName
            << " | Role: " << role << " | Gate: " << gate
            << " | Type: " << type << " | Time: " << getCurrentTimestamp() << "\n";
        cout << "  [OK] " << type << " logged for " << personName
            << " at " << gate << ".\n";
    }
    void saveToFile() const {
        ofstream f("security.txt", ios::app);
        if (!f.is_open()) throw runtime_error("Cannot open security.txt");
        f << "ID: " << id << " | Name: " << name
            << " | Shift: " << shiftTiming << " | Dept: " << assignedDept << "\n"
            << string(50, '-') << "\n";
        cout << "  [OK] Security record saved.\n";
    }
    static void loadAll() {
        ifstream f("security.txt");
        if (!f.is_open()) { cout << "  No security records found.\n"; return; }
        string line;
        cout << "\n";
        while (getline(f, line)) cout << "  " << line << "\n";
    }
};

// ═══════════════════════════════════════════════════════════════════
//  CLASS: Admin  (extends Administration + handles authentication)
// ═══════════════════════════════════════════════════════════════════

class Admin : public Administration {
    Login loginDetails;
public:
    void setLoginDetails(const string& usr, const string& pwd) {
        loginDetails.username = usr;
        loginDetails.password = pwd;
    }
    bool authenticate(const string& usr, const string& pwd) {
        bool ok = (usr == loginDetails.username && pwd == loginDetails.password);
        // save login history
        ofstream f("login_history.txt", ios::app);
        if (f.is_open())
            f << "User: " << usr
            << " | Status: " << (ok ? "SUCCESS" : "FAILED")
            << " | Time: " << getCurrentTimestamp() << "\n";
        if (ok)
            cout << "  [OK] Admin authenticated successfully.\n";
        else
            cout << "  [!] Invalid credentials. Access denied.\n";
        return ok;
    }
};

// ═══════════════════════════════════════════════════════════════════
//  CLASS: Gates
// ═══════════════════════════════════════════════════════════════════

class Gate {
    int    gateNo;
    string location;
    bool   isOpen;
public:
    void setDetails(int no, const string& loc, bool open) {
        if (no <= 0) throw out_of_range("Gate number must be positive.");
        gateNo = no; location = loc; isOpen = open;
    }
    void open() { isOpen = true;  cout << "  Gate " << gateNo << " is now OPEN.\n"; }
    void close() { isOpen = false; cout << "  Gate " << gateNo << " is now CLOSED.\n"; }
    void displayInfo() const {
        cout << "  Gate " << gateNo << " | " << location
            << " | Status: " << (isOpen ? "OPEN" : "CLOSED") << "\n";
    }
};

// ═══════════════════════════════════════════════════════════════════
//  CLASS: Course
// ═══════════════════════════════════════════════════════════════════

class Course {
    string courseID, courseName, instructorID;
    int    creditHours = 3;
public:
    void setDetails(const string& id, const string& name,
        int credits, const string& instrID) {
        if (credits < 1 || credits > 6)
            throw invalid_argument("Credit hours must be 1–6.");
        courseID = id; courseName = name;
        creditHours = credits; instructorID = instrID;
    }
    void displayInfo() const {
        cout << "  ID      : " << courseID << "\n"
            << "  Name    : " << courseName << "\n"
            << "  Credits : " << creditHours << "\n"
            << "  Instr.  : " << instructorID << "\n";
    }
    void saveToFile() const {
        ofstream f("courses.txt", ios::app);
        if (!f.is_open()) throw runtime_error("Cannot open courses.txt");
        f << "ID: " << courseID << " | Name: " << courseName
            << " | Credits: " << creditHours
            << " | Instructor: " << instructorID << "\n"
            << string(50, '-') << "\n";
        cout << "  [OK] Course record saved.\n";
    }
    static void loadAll() {
        ifstream f("courses.txt");
        if (!f.is_open()) { cout << "  No course records found.\n"; return; }
        string line;
        cout << "\n";
        while (getline(f, line)) cout << "  " << line << "\n";
    }
    void assignInstructor(const string& instrID) {
        instructorID = instrID;
        cout << "  Instructor " << instrID << " assigned to " << courseName << ".\n";
    }
};

// ═══════════════════════════════════════════════════════════════════
//  CLASS: Report
// ═══════════════════════════════════════════════════════════════════

class Report {
    string reportID, title, description, date, type;
public:
    void setDetails(const string& id, const string& t,
        const string& desc, const string& d,
        const string& rtype = "General") {
        reportID = id; title = t; description = desc;
        date = d.empty() ? getCurrentTimestamp() : d;
        type = rtype;
    }
    void saveToFile() const {
        ofstream f("reports.txt", ios::app);
        if (!f.is_open()) throw runtime_error("Cannot open reports.txt");
        f << "Report ID  : " << reportID << "\n"
            << "Type       : " << type << "\n"
            << "Title      : " << title << "\n"
            << "Description: " << description << "\n"
            << "Date       : " << date << "\n"
            << string(50, '-') << "\n";
        cout << "  [OK] Report saved successfully.\n";
    }
    void displayInfo() const {
        cout << "  ID   : " << reportID << "\n"
            << "  Type : " << type << "\n"
            << "  Title: " << title << "\n"
            << "  Desc : " << description << "\n"
            << "  Date : " << date << "\n";
    }
    static void loadAll() {
        ifstream f("reports.txt");
        if (!f.is_open()) { cout << "  No reports found.\n"; return; }
        string line;
        cout << "\n";
        while (getline(f, line)) cout << "  " << line << "\n";
    }
};

// ═══════════════════════════════════════════════════════════════════
//  CLASS: Schedule
// ═══════════════════════════════════════════════════════════════════

class Schedule {
    string scheduleID, courseID, day, time;
    int    roomNo = 0;
    int    duration = CLASS_DURATION_MINUTES;
public:
    void setDetails(const string& sid, const string& cid,
        const string& d, const string& t,
        int room, int dur = CLASS_DURATION_MINUTES) {
        scheduleID = sid; courseID = cid; day = d;
        time = t; roomNo = room; duration = dur;
    }
    void displayInfo() const {
        cout << "  Sched ID : " << scheduleID << "\n"
            << "  Course   : " << courseID << "\n"
            << "  Day/Time : " << day << " @ " << time << "\n"
            << "  Room     : " << roomNo << "\n"
            << "  Duration : " << duration << " min\n";
    }
    void updateRoom(int newRoom) {
        if (newRoom <= 0) throw invalid_argument("Room number must be positive.");
        roomNo = newRoom;
        cout << "  Room updated to: " << newRoom << "\n";
    }
    void changeTime(const string& newTime, const string& newDay) {
        time = newTime; day = newDay;
        cout << "  Schedule updated: " << newDay << " @ " << newTime << "\n";
    }
    void saveToFile() const {
        ofstream f("schedules.txt", ios::app);
        if (!f.is_open()) throw runtime_error("Cannot open schedules.txt");
        f << "ID: " << scheduleID << " | Course: " << courseID
            << " | " << day << " @ " << time
            << " | Room: " << roomNo
            << " | Duration: " << duration << " min\n"
            << string(50, '-') << "\n";
        cout << "  [OK] Schedule saved.\n";
    }
    static void loadAll() {
        ifstream f("schedules.txt");
        if (!f.is_open()) { cout << "  No schedules found.\n"; return; }
        string line;
        cout << "\n";
        while (getline(f, line)) cout << "  " << line << "\n";
    }
};

// ═══════════════════════════════════════════════════════════════════
//  CLASS: Notification
// ═══════════════════════════════════════════════════════════════════

class Notification {
    string notifID, message, receiverID;
    bool   isRead = false;
public:
    void setDetails(const string& id, const string& msg,
        const string& recv, bool read = false) {
        notifID = id; message = msg; receiverID = recv; isRead = read;
    }
    void display() const {
        cout << "  ID      : " << notifID << "\n"
            << "  Message : " << message << "\n"
            << "  To      : " << receiverID << "\n"
            << "  Status  : " << (isRead ? "Read" : "Unread") << "\n";
    }
    void markRead() { isRead = true;  cout << "  Notification marked as Read.\n"; }
    void markUnread() { isRead = false; cout << "  Notification marked as Unread.\n"; }
};

// ═══════════════════════════════════════════════════════════════════
//  CLASS: FileManager
// ═══════════════════════════════════════════════════════════════════

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

// ═══════════════════════════════════════════════════════════════════
//  CLASS: AttendanceManager
// ═══════════════════════════════════════════════════════════════════

class AttendanceManager {
public:

    // ── Mark Check-In ────────────────────────────────────────────
    void markCheckIn(const string& studentID) {
        if (studentID.empty()) throw invalid_argument("Student ID is required.");

        cout << "\n";
        int  progIdx = selectProgram();
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

    // ── Mark Check-Out ───────────────────────────────────────────
    void markCheckOut(const string& studentID) {
        if (studentID.empty()) throw invalid_argument("Student ID is required.");

        cout << "\n";
        int    progIdx = selectProgram();
        string selectedCourse = selectCourse(progIdx);

        // verify a CHECK_IN exists without a matching CHECK_OUT
        ifstream inF("attendance.txt");
        if (!inF.is_open()) throw runtime_error("Cannot read attendance.txt");

        int checkInCount = 0, checkOutCount = 0;
        string lastCheckInTime;
        int    lastDur = CLASS_DURATION_MINUTES;
        string line;

        while (getline(inF, line)) {
            if (line.find("StudentID: " + studentID) == string::npos) continue;
            if (line.find("CourseID: " + selectedCourse) == string::npos) continue;
            if (line.find("CHECK_IN") != string::npos) {
                checkInCount++;
                lastCheckInTime = line.substr(line.rfind("Time: ") + 6);
                // extract duration
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

        // calculate duration
        int inSec = timeToSeconds(lastCheckInTime);
        int outSec = timeToSeconds(ts);
        int diff = outSec - inSec;
        if (diff < 0) diff = 0;
        int mins = diff / 60;
        int secs = diff % 60;
        int req = (int)((MIN_ATTENDANCE_PERCENT / 100.0f) * lastDur);
        bool present = (mins >= req);

        cout << "\n  ╔══════════════════════════════════════╗\n";
        cout << "  ║       ATTENDANCE RESULT              ║\n";
        cout << "  ╠══════════════════════════════════════╣\n";
        cout << "  ║  Student  : " << left << setw(24) << studentID << "║\n";
        cout << "  ║  Course   : " << left << setw(24) << selectedCourse << "║\n";
        cout << "  ║  Check-in : " << left << setw(24) << lastCheckInTime << "║\n";
        cout << "  ║  Check-out: " << left << setw(24) << ts << "║\n";
        cout << "  ║  Duration : " << left << setw(24) << (to_string(mins) + " min " + to_string(secs) + " sec") << "║\n";
        cout << "  ║  Required : " << left << setw(24) << (to_string(req) + " min") << "║\n";
        cout << "  ║  Status   : " << left << setw(24) << (present ? "PRESENT ✓" : "ABSENT ✗") << "║\n";
        cout << "  ╚══════════════════════════════════════╝\n";
    }

    // ── Calculate Presence Duration (by student ID + course) ─────
    void calculatePresenceDuration(const string& studentID, const string& courseID) {
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
            << "  Status   : " << ((mins + hours * 60) >= req ? "PRESENT ✓" : "ABSENT ✗") << "\n";
    }

    // ── View All Attendance for a Course ─────────────────────────
    void viewCourseAttendance(const string& courseID) {
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

    // ── View Full Attendance File ─────────────────────────────────
    void viewAllAttendance() {
        ifstream f("attendance.txt");
        if (!f.is_open()) { cout << "  No attendance records found.\n"; return; }
        printHeader("FULL ATTENDANCE LOG");
        string line;
        while (getline(f, line)) cout << "  " << line << "\n";
        f.close();
    }
};

// ═══════════════════════════════════════════════════════════════════
//  MENU: STUDENT
// ═══════════════════════════════════════════════════════════════════

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
                int  pi = selectProgram();
                string cid = selectCourse(pi);
                am.calculatePresenceDuration(studentID, cid);
            }
            else if (choice == 4) {
                ifstream f("attendance.txt");
                if (!f.is_open()) { cout << "  No records found.\n"; }
                else {
                    printHeader("MY ATTENDANCE LOG");
                    string line;
                    bool found = false;
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

// ═══════════════════════════════════════════════════════════════════
//  MENU: FACULTY
// ═══════════════════════════════════════════════════════════════════

void showFacultyMenu(AttendanceManager& am) {
    string facID, facName, desig, dept;
    cout << "\n  Faculty ID         : "; getline(cin, facID);
    cout << "  Name               : "; getline(cin, facName);
    cout << "  Designation        : "; getline(cin, desig);
    cout << "  Department (CS/AI/IT): "; getline(cin, dept);
    if (facID.empty()) { cout << "  [!] Faculty ID required.\n"; return; }

    Faculty fac;
    try {
        fac.setBasicInfo(facID, facName, "faculty@uni.edu", "0000-0000000");
        fac.setFacultyDetails(desig, dept);
    }
    catch (const exception& e) {
        cout << "  [!] " << e.what() << "\n";
    }

    int choice;
    do {
        cout << "\n";
        printHeader("FACULTY PORTAL  [" + facID + " - " + facName + "]");
        cout << "  1.  View Attendance for a Course\n"
            << "  2.  Check Student Attendance Duration\n"
            << "  3.  Mark Class Attendance (Session)\n"
            << "  4.  View My Info\n"
            << "  5.  Save Faculty Record to File\n"
            << "  6.  View All Faculty Records\n"
            << "  7.  View Saved Schedules\n"
            << "  0.  Logout\n";
        printLine();
        choice = getIntInput("  Choice: ", 0, 7);

        try {
            if (choice == 1) {
                cout << "\n";
                int pi = selectProgram();
                string cid = selectCourse(pi);
                am.viewCourseAttendance(cid);
            }
            else if (choice == 2) {
                string sid, cid;
                cout << "\n  Student ID  : "; getline(cin, sid);
                cout << "\n";
                int pi = selectProgram();
                cid = selectCourse(pi);
                am.calculatePresenceDuration(sid, cid);
            }
            else if (choice == 3) {
                fac.markAttendance();
                cout << "  Session recorded at: " << getCurrentTimestamp() << "\n";
                ofstream f("attendance.txt", ios::app);
                if (f.is_open())
                    f << "Faculty: " << facID << " | Session at: "
                    << getCurrentTimestamp() << "\n";
            }
            else if (choice == 4) {
                fac.displayInfo();
            }
            else if (choice == 5) {
                fac.saveToFile();
            }
            else if (choice == 6) {
                Faculty::loadAll();
            }
            else if (choice == 7) {
                Schedule::loadAll();
            }
        }
        catch (const exception& e) {
            cout << "  [!] Error: " << e.what() << "\n";
        }

        if (choice != 0) pauseScreen();

    } while (choice != 0);

    cout << "  Logged out.\n";
}

// ═══════════════════════════════════════════════════════════════════
//  MENU: SECURITY
// ═══════════════════════════════════════════════════════════════════

void showSecurityMenu() {
    string secID, secName, email, phone, shift, dept;
    cout << "\n  Security ID : "; getline(cin, secID);
    cout << "  Name        : "; getline(cin, secName);
    cout << "  Email       : "; getline(cin, email);
    cout << "  Phone       : "; getline(cin, phone);
    cout << "  Shift (Morning/Evening/Night): "; getline(cin, shift);
    cout << "  Assigned Dept: "; getline(cin, dept);

    Security sec;
    try {
        sec.setBasicInfo(secID, secName, email, phone);
        sec.setSecurityDetails(shift, dept);
    }
    catch (const exception& e) {
        cout << "  [!] " << e.what() << "\n";
        return;
    }

    // Gate objects
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
                cout << "\n  Person Name/ID: "; getline(cin, person);
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
                string types[] = { "Unauthorized Entry","Suspicious Behaviour","Equipment Damage","Other" };
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

// ═══════════════════════════════════════════════════════════════════
//  MENU: ADMINISTRATION
// ═══════════════════════════════════════════════════════════════════

void showAdminMenu(AttendanceManager& am, FileManager& fm) {
    int choice;
    do {
        cout << "\n";
        printHeader("ADMINISTRATION MENU");
        cout << "  ── Attendance ──────────────────────\n"
            << "  1.  Check Student Attendance Duration\n"
            << "  2.  View All Attendance for a Course\n"
            << "  3.  View Full Attendance Log\n"
            << "  ── Reports ─────────────────────────\n"
            << "  4.  Create & Save Report\n"
            << "  5.  View Saved Reports\n"
            << "  ── Records ─────────────────────────\n"
            << "  6.  Add Student Record\n"
            << "  7.  View All Student Records\n"
            << "  8.  Add Course Record\n"
            << "  9.  View All Course Records\n"
            << "  ── Schedule ────────────────────────\n"
            << "  10. Add / Update Class Schedule\n"
            << "  11. View All Schedules\n"
            << "  ── Personnel ───────────────────────\n"
            << "  12. View Faculty Info (from file)\n"
            << "  13. View Security Info (from file)\n"
            << "  ── File Management ─────────────────\n"
            << "  14. Clear Attendance File\n"
            << "  15. Clear ALL Files\n"
            << "  16. List All Files\n"
            << "  0.  Logout\n";
        printLine();
        choice = getIntInput("  Choice: ", 0, 16);

        try {
            // ── Attendance ────────────────────────────────────────
            if (choice == 1) {
                string sid, cid;
                cout << "\n  Student ID : "; getline(cin, sid);
                cout << "\n";
                int pi = selectProgram();
                cid = selectCourse(pi);
                am.calculatePresenceDuration(sid, cid);
            }
            else if (choice == 2) {
                cout << "\n";
                int pi = selectProgram();
                string cid = selectCourse(pi);
                am.viewCourseAttendance(cid);
            }
            else if (choice == 3) {
                am.viewAllAttendance();
            }
            // ── Reports ───────────────────────────────────────────
            else if (choice == 4) {
                Report r;
                string id, title, desc, date, rtype;
                cout << "\n  Report ID   : "; getline(cin, id);
                cout << "  Title       : "; getline(cin, title);
                cout << "  Description : "; getline(cin, desc);
                cout << "  Date (YYYY-MM-DD or blank for now): "; getline(cin, date);
                cout << "  Type (Attendance/Performance/Faculty/Security/General): ";
                getline(cin, rtype);
                if (rtype.empty()) rtype = "General";
                r.setDetails(id, title, desc, date, rtype);
                r.displayInfo();
                r.saveToFile();
            }
            else if (choice == 5) {
                Report::loadAll();
            }
            // ── Students ──────────────────────────────────────────
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
            else if (choice == 7) {
                Student::loadAll();
            }
            // ── Courses ───────────────────────────────────────────
            else if (choice == 8) {
                Course c;
                string cid, cname, instrID;
                int    credits;
                cout << "\n  Course ID   : "; getline(cin, cid);
                cout << "  Course Name : "; getline(cin, cname);
                cout << "  Instructor ID: "; getline(cin, instrID);
                credits = getIntInput("  Credit Hours (1-6): ", 1, 6);
                c.setDetails(cid, cname, credits, instrID);
                c.saveToFile();
            }
            else if (choice == 9) {
                Course::loadAll();
            }
            // ── Schedules ─────────────────────────────────────────
            else if (choice == 10) {
                Schedule sc;
                string sid, day, time;
                int    room, dur;
                cout << "\n";
                int pi = selectProgram();
                string cid = selectCourse(pi);

                cout << "\n  Schedule ID : "; getline(cin, sid);
                cout << "  Day (Monday-Friday): "; getline(cin, day);
                cout << "  Time (HH:MM): "; getline(cin, time);
                room = getIntInput("  Room No    : ", 1, 999);
                cout << "  Duration:\n"
                    << "  1. 60 min   2. 90 min   3. 120 min\n";
                int dc = getIntInput("  Choice: ", 1, 3);
                dur = (dc == 1) ? 60 : (dc == 3) ? 120 : 90;

                sc.setDetails(sid, cid, day, time, room, dur);
                sc.displayInfo();
                sc.saveToFile();
            }
            else if (choice == 11) {
                Schedule::loadAll();
            }
            // ── Personnel ─────────────────────────────────────────
            else if (choice == 12) {
                Faculty::loadAll();
            }
            else if (choice == 13) {
                Security::loadAll();
            }
            // ── File Management ───────────────────────────────────
            else if (choice == 14) {
                fm.clearFile("attendance.txt");
            }
            else if (choice == 15) {
                char confirm;
                cout << "\n  [!] This will clear ALL data files. Continue? (y/n): ";
                cin >> confirm;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (confirm == 'y' || confirm == 'Y') fm.clearAll();
                else cout << "  Cancelled.\n";
            }
            else if (choice == 16) {
                fm.listFiles();
            }
        }
        catch (const exception& e) {
            cout << "  [!] Error: " << e.what() << "\n";
        }

        if (choice != 0) pauseScreen();

    } while (choice != 0);

    cout << "  Admin logged out.\n";
}

// ═══════════════════════════════════════════════════════════════════
//  MAIN
// ═══════════════════════════════════════════════════════════════════

int main() {

    // Hardcoded admin credentials
    Admin adminUser;
    adminUser.setBasicInfo("A001", "Admin User", "admin@uni.edu", "03001234567");
    adminUser.setRole("System Administrator");
    adminUser.setLoginDetails("shumyalamir", "090078601asdF");

    AttendanceManager am;
    FileManager       fm;

    int choice;
    do {
        cout << "\n";
        printHeader("UNIVERSITY MANAGEMENT SYSTEM");
        cout << "  1. Admin Login\n"
            << "  2. Student Attendance Portal\n"
            << "  3. Faculty Portal\n"
            << "  4. Security Portal\n"
            << "  0. Exit\n";
        printLine();
        choice = getIntInput("  Choice: ", 0, 4);

        if (choice == 1) {
            string usr, pwd;
            cout << "\n  Username: "; getline(cin, usr);
            cout << "  Password: "; getline(cin, pwd);
            if (adminUser.authenticate(usr, pwd)) {
                pauseScreen();
                showAdminMenu(am, fm);
            }
        }
        else if (choice == 2) {
            showStudentMenu(am);
        }
        else if (choice == 3) {
            showFacultyMenu(am);
        }
        else if (choice == 4) {
            showSecurityMenu();
        }

    } while (choice != 0);

    cout << "\n  System exited. Goodbye!\n\n";
    return 0;
}