#include "Schedule.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

void Schedule::setDetails(const string& sid, const string& cid,
    const string& d, const string& t,
    int room, int dur) {
    scheduleID = sid; courseID = cid;
    day = d; time = t; roomNo = room; duration = dur;
}

void Schedule::displayInfo() const {
    cout << "  Sched ID : " << scheduleID << "\n"
        << "  Course   : " << courseID << "\n"
        << "  Day/Time : " << day << " @ " << time << "\n"
        << "  Room     : " << roomNo << "\n"
        << "  Duration : " << duration << " min\n";
}

void Schedule::updateRoom(int newRoom) {
    if (newRoom <= 0) throw invalid_argument("Room number must be positive.");
    roomNo = newRoom;
    cout << "  Room updated to: " << newRoom << "\n";
}

void Schedule::changeTime(const string& newTime, const string& newDay) {
    time = newTime; day = newDay;
    cout << "  Schedule updated: " << newDay << " @ " << newTime << "\n";
}

void Schedule::saveToFile() const {
    ofstream f("schedules.txt", ios::app);
    if (!f.is_open()) throw runtime_error("Cannot open schedules.txt");
    f << "ID: " << scheduleID << " | Course: " << courseID
        << " | " << day << " @ " << time
        << " | Room: " << roomNo
        << " | Duration: " << duration << " min\n"
        << string(50, '-') << "\n";
    cout << "  [OK] Schedule saved.\n";
}

void Schedule::loadAll() {
    ifstream f("schedules.txt");
    if (!f.is_open()) { cout << "  No schedules found.\n"; return; }
    string line;
    cout << "\n";
    while (getline(f, line)) cout << "  " << line << "\n";
}