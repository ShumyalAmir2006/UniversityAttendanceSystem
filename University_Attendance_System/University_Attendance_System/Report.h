#pragma once
#include <string>
using namespace std;

class Report {
    string reportID, title, description, date, type;
public:
    void setDetails(const string& id, const string& t,
        const string& desc, const string& d,
        const string& rtype = "General");
    void displayInfo() const;
    void saveToFile()  const;
    static void loadAll();
};