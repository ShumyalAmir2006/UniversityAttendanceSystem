#pragma once
#include "Student.h"
#include "Faculty.h"
#include "Security.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class DataSeeder {
private:

    // Pakistani first names
    string firstNames[50] = {
        "Ahmed", "Muhammad", "Ali", "Hassan", "Usman",
        "Bilal", "Hamza", "Zain", "Omar", "Tariq",
        "Fahad", "Asad", "Imran", "Junaid", "Kamran",
        "Nabeel", "Omer", "Qasim", "Raza", "Saad",
        "Talha", "Umair", "Waqar", "Yasir", "Zubair",
        "Ayesha", "Fatima", "Zainab", "Sana", "Hira",
        "Nadia", "Rabia", "Sadia", "Amna", "Bushra",
        "Farah", "Gul", "Huma", "Iqra", "Javeria",
        "Kiran", "Laiba", "Mariam", "Noor", "Pakistan",
        "Rimsha", "Saba", "Tooba", "Urwa", "Zara"
    };

    // Pakistani last names
    string lastNames[50] = {
        "Khan", "Ahmed", "Ali", "Hussain", "Malik",
        "Chaudhry", "Sheikh", "Qureshi", "Siddiqui", "Ansari",
        "Butt", "Rana", "Mirza", "Baig", "Rizvi",
        "Hashmi", "Abbasi", "Farooqi", "Gillani", "Javed",
        "Khalid", "Lodhi", "Memon", "Niazi", "Pasha",
        "Rauf", "Sabir", "Tahir", "Usmani", "Wali",
        "Yousaf", "Zaidi", "Bhatti", "Dar", "Gul",
        "Haider", "Iqbal", "Janjua", "Kazmi", "Laghari",
        "Mughal", "Naqvi", "Paracha", "Rajput", "Satti",
        "Tiwana", "Virk", "Warraich", "Zaman", "Gondal"
    };

    // Faculty designations
    string designations[6] = {
        "Professor", "Associate Professor", "Assistant Professor",
        "Lecturer", "Senior Lecturer", "Lab Engineer"
    };

    // Departments
    string departments[3] = { "CS", "AI", "IT" };

    // Shifts
    string shifts[3] = { "Morning", "Evening", "Night" };

    // Check if file already has records
    bool fileHasRecords(const string& filename) {
        ifstream f(filename);
        if (!f.is_open()) return false;
        string line;
        bool hasContent = false;
        while (getline(f, line)) {
            if (!line.empty() && line.find("---") == string::npos) {
                hasContent = true;
                break;
            }
        }
        f.close();
        return hasContent;
    }

    string generateEmail(const string& first, const string& last,
        const string& prefix, int num) {
        string email = "";
        for (char c : first) email += tolower(c);
        email += ".";
        for (char c : last) email += tolower(c);
        email += to_string(num) + "@" + prefix + ".edu.pk";
        return email;
    }

    string generatePhone(int num) {
        // Pakistani mobile format 03XX-XXXXXXX
        string bases[5] = { "0300", "0301", "0311", "0321", "0333" };
        string base = bases[num % 5];
        string suffix = to_string(1000000 + num);
        return base + "-" + suffix;
    }

    float generateCGPA(int num) {
        // Range between 1.5 and 4.0
        float cgpas[10] = { 3.9f, 3.7f, 3.5f, 3.2f, 3.0f,
                            2.8f, 2.5f, 2.2f, 2.0f, 1.5f };
        return cgpas[num % 10];
    }

public:

    void seedStudents() {
        if (fileHasRecords("students.txt")) {
            cout << "  [SKIP] students.txt already has records.\n";
            return;
        }

        cout << "  Seeding 1000 students...\n";
        int count = 0;

        for (int i = 0; i < 1000; i++) {
            string first = firstNames[i % 50];
            string last = lastNames[(i / 50) % 50];
            string name = first + " " + last;
            string id = "S" + string(4 - to_string(i + 1).size(), '0') + to_string(i + 1);
            string email = generateEmail(first, last, "student", i + 1);
            string phone = generatePhone(i + 1);
            string dept = departments[i % 3];
            float  cgpa = generateCGPA(i);

            Student s;
            s.setBasicInfo(id, name, email, phone);
            s.setStudentDetails(cgpa, dept);
            s.saveToFile();
            count++;

            // Progress every 100
            if (count % 100 == 0)
                cout << "  [" << count << "/1000] students added...\n";
        }

        cout << "  [OK] 1000 students seeded successfully.\n";
    }

    void seedFaculty() {
        if (fileHasRecords("faculty.txt")) {
            cout << "  [SKIP] faculty.txt already has records.\n";
            return;
        }

        cout << "  Seeding 50 faculty members...\n";

        for (int i = 0; i < 50; i++) {
            string first = firstNames[(i + 10) % 50];
            string last = lastNames[(i + 5) % 50];
            string name = first + " " + last;
            string id = "F" + string(3 - to_string(i + 1).size(), '0') + to_string(i + 1);
            string email = generateEmail(first, last, "faculty", i + 1);
            string phone = generatePhone(i + 1001);
            string desig = designations[i % 6];
            string dept = departments[i % 3];

            Faculty f;
            f.setBasicInfo(id, name, email, phone);
            f.setFacultyDetails(desig, dept);
            f.saveToFile();
        }

        cout << "  [OK] 50 faculty members seeded successfully.\n";
    }

    void seedSecurity() {
        if (fileHasRecords("security.txt")) {
            cout << "  [SKIP] security.txt already has records.\n";
            return;
        }

        cout << "  Seeding 50 security guards...\n";

        for (int i = 0; i < 50; i++) {
            string first = firstNames[(i + 20) % 50];
            string last = lastNames[(i + 15) % 50];
            string name = first + " " + last;
            string id = "SEC" + string(3 - to_string(i + 1).size(), '0') + to_string(i + 1);
            string email = generateEmail(first, last, "security", i + 1);
            string phone = generatePhone(i + 2001);
            string shift = shifts[i % 3];
            string dept = departments[i % 3];

            Security sec;
            sec.setBasicInfo(id, name, email, phone);
            sec.setSecurityDetails(shift, dept);
            sec.saveToFile();
        }

        cout << "  [OK] 50 security guards seeded successfully.\n";
    }

    void seedAll() {
        cout << "\n";
        cout << "  ==========================================\n";
        cout << "        UNIVERSITY DATA SEEDER\n";
        cout << "  ==========================================\n";
        seedStudents();
        seedFaculty();
        seedSecurity();
        cout << "  ==========================================\n";
        cout << "        ALL RECORDS SEEDED\n";
        cout << "  ==========================================\n\n";
    }
};