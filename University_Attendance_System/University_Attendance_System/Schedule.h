#pragma once
#include <string>
#include "Constants.h"
using namespace std;

class Schedule {
    string scheduleID, courseID, day, time;
    int    roomNo = 0;
    int    duration = CLASS_DURATION_MINUTES;
public:
    void setDetails(const string& sid, const string& cid,
        const string& d, const string& t,
        int room, int dur = CLASS_DURATION_MINUTES);
    void displayInfo() const;
    void updateRoom(int newRoom);
    void changeTime(const string& newTime, const string& newDay);
    void saveToFile()  const;
    static void loadAll();
};
