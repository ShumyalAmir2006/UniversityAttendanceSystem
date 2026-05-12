#include "Utilities.h"
#include "Constants.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <string>
using namespace std;

string programs[NUM_PROGRAMS] = { "CS", "AI", "IT" };

string courses[NUM_PROGRAMS][NUM_COURSES] = {
    { "CS101-Programming", "CS102-DataStructures", "CS103-OOP", "CS104-Algorithms"          },
    { "AI101-MachineLearning", "AI102-NeuralNetworks", "AI103-ComputerVision", "AI104-NLP"  },
    { "IT101-Networking", "IT102-DatabaseSystems", "IT103-WebDev", "IT104-CyberSecurity"    }
};

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
    tm localTime;
    localtime_s(&localTime, &now);
    ostringstream oss;
    oss << put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

int timeToSeconds(const string& ts) {
    int h = 0, m = 0, s = 0;
    if (ts.size() >= 19)
        sscanf_s(ts.c_str() + 11, "%d:%d:%d", &h, &m, &s);
    return h * 3600 + m * 60 + s;
}

void printLine(char c, int len) {
    cout << string(len, c) << endl;
}

void printHeader(const string& title) {
    printLine('=');
    cout << "  " << title << endl;
    printLine('=');
}

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