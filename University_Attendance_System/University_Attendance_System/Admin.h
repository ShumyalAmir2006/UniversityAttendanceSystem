#pragma once
#include "Administration.h"
#include "Login.h"
#include "Utilities.h"
#include <fstream>

class Admin : public Administration {
    Login loginDetails;
public:
    void setLoginDetails(const string& usr, const string& pwd) {
        loginDetails.username = usr;
        loginDetails.password = pwd;
    }
    bool authenticate(const string& usr, const string& pwd) {
        bool ok = (usr == loginDetails.username && pwd == loginDetails.password);
        ofstream f("login_history.txt", ios::app);
        if (f.is_open())
            f << "User: " << usr
            << " | Status: " << (ok ? "SUCCESS" : "FAILED")
            << " | Time: " << getCurrentTimestamp() << "\n";
        if (ok) cout << "  [OK] Admin authenticated successfully.\n";
        else    cout << "  [!] Invalid credentials. Access denied.\n";
        return ok;
    }
};