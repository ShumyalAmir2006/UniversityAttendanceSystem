#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

class Gate {
    int    gateNo = 0;
    string location;
	bool   isOpen = false;
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