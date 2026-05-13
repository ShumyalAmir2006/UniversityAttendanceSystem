#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <limits>
#include "Constants.h"
#include "Utilities.h"
#include "Admin.h"
#include "AttendanceManager.h"
#include "FileManager.h"
#include "Menus.h"
#include "DataSeeder.h"

using namespace std;

int main() {

    DataSeeder seeder;
    seeder.seedAll();

    Admin adminUser;
    adminUser.setBasicInfo("A001", "Admin User", "admin@uni.edu", "03001234567");
    adminUser.setRole("System Administrator");
    adminUser.setLoginDetails("Hijab", "shumyal123");

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
        else if (choice == 2) { showStudentMenu(am); }
        else if (choice == 3) { showFacultyMenu(am); }
        else if (choice == 4) { showSecurityMenu(); }

    } while (choice != 0);

    cout << "\n  System exited. Goodbye!\n\n";
    return 0;
}