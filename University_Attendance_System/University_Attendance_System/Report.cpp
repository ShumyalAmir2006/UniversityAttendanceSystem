#include "Report.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

void Report::setDetails(const string& id, const string& t,
    const string& desc, const string& d,
    const string& rtype) {
    reportID = id; title = t; description = desc;
    date = d.empty() ? getCurrentTimestamp() : d;
    type = rtype;
}

void Report::displayInfo() const {
    cout << "  ID   : " << reportID << "\n"
        << "  Type : " << type << "\n"
        << "  Title: " << title << "\n"
        << "  Desc : " << description << "\n"
        << "  Date : " << date << "\n";
}

void Report::saveToFile() const {
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

void Report::loadAll() {
    ifstream f("reports.txt");
    if (!f.is_open()) { cout << "  No reports found.\n"; return; }
    string line;
    cout << "\n";
    while (getline(f, line)) cout << "  " << line << "\n";
}