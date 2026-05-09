#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>      
#include <sstream>    
#include <iomanip>    


using namespace std;
class person {
protected:
	string id;
	string name;
	string Email;
	string phone;

public:
	void setBasicInfo(string id, string name, string email, string phone) {
		try {
			if (id.empty() || name.empty() || email.empty() || phone.empty())
				throw invalid_argument("All fields (ID, Name, Email, Phone) are required.");
			this->id = id;
			this->name = name;
			this->Email = email;
			this->phone = phone;
		}
		catch (const invalid_argument& e) {
			cout << "Input Error: " << e.what() << endl;
		}
	}
	void saveToFile() {
		ofstream file("persons.txt", ios::app); // app = append mode
		try {
			if (!file.is_open())
				throw runtime_error("Could not open persons.txt");

			file << "ID: " << id << ", Name: " << name
				<< ", Email: " << Email << ", Phone: " << phone << "\n";
			file << "-------------------------\n";
			cout << "Person record saved successfully." << endl;
			file.close();
		}
		catch (const runtime_error& e) {
			cout << "File Error: " << e.what() << endl;
		}
	}

	void displaybasicinfo() {
		cout << "ID: " << id << endl;
		cout << "Name: " << name << endl;
		cout << "Email: " << Email << endl;
		cout << "Phone: " << phone << endl;
	}
};
class login {
public:
	string user_name;
	string password;
	bool isauthenticated;


};
//CLASSES INHERITED BY THE PERSON CLASS

class student :public person {

	float cgpa;
	string department;
public:
	void setStudentDetails(float cgpa, string department) {
    try {
        if (cgpa < 0.0 || cgpa > 4.0)
            throw invalid_argument("CGPA must be between 0.0 and 4.0");
        this->cgpa = cgpa;
        this->department = department;
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }
}
	void saveStudentToFile() {
		ofstream file("students.txt", ios::app);
		try {
			if (!file.is_open())
				throw runtime_error("Could not open students.txt");

			file << "ID: " << id << ", Name: " << name
				<< ", CGPA: " << cgpa
				<< ", Department: " << department << "\n";
			file << "-------------------------\n";
			cout << "Student record saved." << endl;
			file.close();
		}
		catch (const runtime_error& e) {
			cout << "File Error: " << e.what() << endl;
		}
	}

	void loadStudentsFromFile() {
		ifstream file("students.txt");
		try {
			if (!file.is_open())
				throw runtime_error("Could not open students.txt");

			string line;
			cout << "=== Student Records ===" << endl;
			while (getline(file, line)) {
				cout << line << endl;
			}
			file.close();
		}
		catch (const runtime_error& e) {
			cout << "File Error: " << e.what() << endl;
		}
	}
	void enrollCourse(string course_Name) {
		//  to enroll in a course
		cout << "Enrolling in course: " << course_Name << endl;
	}
	void viewResult() {
		// to view results
		cout << "Viewing results for student: " << cgpa << endl;
	}
	void DisplayStudentInfo() {
		displaybasicinfo();
		cout << "CGPA: " << cgpa << endl;
		cout << "Department: " << department << endl;
	}
};
class administration : public person {
	string role;
public:
	void setRole(string role) {
		this->role = role;
	}
	void ManageRecords() {
		// to manage records
		cout << role << "Managing records for university " << endl;
	}
	void GenerateReport() {
		// to generate reports
		cout << name << "Generating report: " << endl;
	}
	void DisplayAdminInfo() {
		displaybasicinfo();
		cout << "Role: " << role << endl;
	}

};
class faculty :public person {
	string designation;
	string department;
public:
	void setFacultyDetails(string desig, string dept) {
		designation = desig;
		department = dept;
	}
	void AssignCourse(string course_Name) {
		// to assign a course
		cout << "Assigning course: " << course_Name << endl;
	}
	void MarkAttendence() {
		cout << name << "Marked Attendence" << endl;
	}
	void DisplayFacultyInfo() {
		displaybasicinfo();
		cout << "Designation: " << designation << endl;
		cout << "Department: " << department << endl;
	}
};
class security : public person {
	string shift_timing;
	string assigned_department;
public:
	void setSecurityDetails(string shift, string dept) {
		shift_timing = shift;
		assigned_department = dept;
	}
	void MonitorCampus() {
		// to monitor campus
		cout << name << " is monitoring the campus during " << shift_timing << " shift." << endl;
	}
	void DisplaySecurityInfo() {
		displaybasicinfo();
		cout << "Shift Timing: " << shift_timing << endl;
		cout << "Assigned Department: " << assigned_department << endl;
	}
	void checkEntry(string person_name) {
		// to check entry
		cout << name << " is checking entry for " << person_name << endl;
	}
	void RepertIssue() {
		// to reissue a report
		cout << name << " is reissuing a report." << endl;
	}


};
//ADMIN CONTROL

class admin : public administration {

	login login_details;
public:
	void setLoginDetails(string username, string password) {
		login_details.user_name = username;
		login_details.password = password;
	}
	void saveLoginHistory(string inputUser, bool success) {
		ofstream file("login_history.txt", ios::app);
		try {
			if (!file.is_open())
				throw runtime_error("Could not open login_history.txt");

			file << "User: " << inputUser
				<< " | Status: " << (success ? "SUCCESS" : "FAILED")
				<< " | Time: " << __DATE__ << " " << __TIME__ << "\n";
			file.close();
		}
		catch (const runtime_error& e) {
			cout << "File Error: " << e.what() << endl;
		}
	}

	void Authenticate(string inputUser, string inputPass) {
		try {
			if (inputUser != login_details.user_name || inputPass != login_details.password)
				throw runtime_error("Invalid credentials. Access denied.");

			cout << "Admin authenticated successfully." << endl;
			saveLoginHistory(inputUser, true);   // log success
		}
		catch (const runtime_error& e) {
			cout << "Authentication Failed: " << e.what() << endl;
			saveLoginHistory(inputUser, false);  // log failure
		}
	}

	void DisplayAdminControl() {
		DisplayAdminInfo();
		cout << "Admin Control Panel" << endl;
	}
	void AddUser() {
		// to add a user
		cout << "Adding a new user to the system" << endl;
	}
	void RemoveUser() {
		// to remove a user
		cout << "Removing a user from the system" << endl;
	}
};
//INDEPENDENT CLASSES

class gates {
	int gate_No;
	string location;
	bool isopen;

public:
	void setGateDetails(int gateNo, string loc, bool open) {
		try {
			if (gateNo <= 0)
				throw out_of_range("Gate number must be a positive integer.");
			gate_No = gateNo;
			location = loc;
			isopen = open;
		}
		catch (const out_of_range& e) {
			cout << "Gate Error: " << e.what() << endl;
		}
	}
	void Opengate() {
		isopen = true;
		cout << "Gate " << gate_No << " is now open." << endl;
	}
	void Closegate() {
		isopen = false;
		cout << "Gate " << gate_No << " is now closed." << endl;
	}
	void DisplayGateInfo() {
		cout << "Gate No: " << gate_No << endl;
		cout << "Location: " << location << endl;
		cout << "Status: " << (isopen ? "Open" : "Closed") << endl;
	}


};
class course {
private:

	string courseID;
	string course_Name;
	int creditHours;
	string instructorID;
public:
	void setCourseDetails(string id, string name, int credithrs, string instructorid) {
		try {
			if (credithrs <= 0 || credithrs > 6)
				throw invalid_argument("Credit hours must be between 1 and 6.");
			courseID = id;
			course_Name = name;
			creditHours = credithrs;
			instructorID = instructorid;
		}
		catch (const invalid_argument& e) {
			cout << "Course Error: " << e.what() << endl;
		}
	}
	void saveCourseToFile() {
		ofstream file("courses.txt", ios::app);
		try {
			if (!file.is_open())
				throw runtime_error("Could not open courses.txt");

			file << "Course ID: " << courseID
				<< ", Name: " << course_Name
				<< ", Credit Hours: " << creditHours
				<< ", Instructor ID: " << instructorID << "\n";
			file << "-------------------------\n";
			file.close();
		}
		catch (const runtime_error& e) {
			cout << "File Error: " << e.what() << endl;
		}
	}
	void displayCourseDetails() {
		cout << "ID of course is " << courseID << endl;
		cout << " Name course is " << course_Name << endl;
		cout << " credit hours of course is" << creditHours << endl;
		cout << " course's instructor's ID id " << instructorID << endl;
	}
	void AssignInstructor(string Instructorid) {
		instructorID = Instructorid;
		cout << " instructor with ID" << instructorID << "is assigned to course" << course_Name << endl;
	}
};
class report {
	string reportID;
	string title;
	string description;
	string date;
public:
	void SetReportDetails(string id, string T, string desc, string D) {
		reportID = id;
		title = T;
		description = desc;
		date = D;
	}
	void saveReportToFile() {
		ofstream file("reports.txt", ios::app);
		try {
			if (!file.is_open())
				throw runtime_error("Could not open reports.txt");

			file << "Report ID: " << reportID << "\n"
				<< "Title: " << title << "\n"
				<< "Description: " << description << "\n"
				<< "Date: " << date << "\n"
				<< "-------------------------\n";
			cout << "Report saved to file." << endl;
			file.close();
		}
		catch (const runtime_error& e) {
			cout << "File Error: " << e.what() << endl;
		}
	}

	void Generate_Report() {
		cout << " report of title " << title << " has been generated succesfully" << endl;
	}

	void DisplayReportDetails() {
		cout << " ID of repert is" << reportID << endl;
		cout << "Title of Report is " << title << endl;
		cout << " Description of  report is " << description << endl;
		cout << " Date of generation of report is" << date << endl;
	}


};

class department {

	string deptID;
	string dept_Name;
	string Headofdept;
public:
	void SetDepartmentDetails(string deptid, string deptName, string HOD) {
		deptID = deptid;
		dept_Name = deptName;
		Headofdept = HOD;
	}
	void DiplayDepartmentDetails() {
		cout << " ID of department is " << deptID << endl;
		cout << " Name of Department is " << dept_Name << endl;
		cout << " Head of Department is " << Headofdept << endl;
	}
	void ChangeHOD(string NewHOD) {
		Headofdept = NewHOD;
	}
	void ShoeNewHOD() {
		cout << " New Assigned heaad of department is  " << Headofdept << endl;
	}



};
class schedual {
	string schedualID;
	string courseID;
	string day;
	string time;
	int room_No;
public:
	void SetSchedualDetails(string SID, string Courseid, string d, string t, int R_No) {
		schedualID = SID;
		courseID = Courseid;
		day = d;
		time = t;
		room_No = R_No;
	}
	void DisplaySchedualDetails() {
		cout << "Id of Schedual is " << schedualID << endl;
		cout << "course id is " << courseID << endl;
		cout << " Day of class is " << day << endl;
		cout << " class time is " << time << endl;
		cout << "Class in room number " << room_No << endl;
	}
	void UpdateRoom(int NewRoom) {
		try {
			if (NewRoom <= 0)
				throw invalid_argument("Room number must be positive.");
			room_No = NewRoom;
			cout << "New room assigned: " << NewRoom << endl;
		}
		catch (const invalid_argument& e) {
			cout << "Room Update Error: " << e.what() << endl;
		}
	}
	void ChangeClassTime(string NewTime, string  NewDay) {
		time = NewTime;
		day = NewDay;

		cout << " updated time of class is" << NewTime << " " << " On day" << NewDay << endl;
	}




};
class notification {
	string notificationID;
	string message;
	string recieverID;
	bool isRead;
public:
	void SetNotificationDetails(string notif, string msg, string recid, bool Isread) {
		notificationID = notif;

		message = msg;
		recieverID = recid;
		isRead = Isread;
	}
	void showNotufucation() {
		cout << " ID for nitification is " << notificationID << endl;
		cout << " Message is " << message << endl;
		cout << "Reciever id is " << recieverID << endl;
		cout << "Status: "
			<< (isRead ? "Read" : "Unread") << endl;
	}
	void MarkAsRead() {
		isRead = true;
		cout << "Notificstion has been marked as read" << isRead << endl;
	}
	void MarkAsUnrerad() {
		isRead = false;
		cout << " Notification has been marked as unread" << isRead << endl;
	}

};
class fileManager {
	vector<string> fileNames;

public:
	// Constructor — register all your project files
	fileManager() {
		fileNames.push_back("students.txt");
		fileNames.push_back("persons.txt");
		fileNames.push_back("courses.txt");
		fileNames.push_back("reports.txt");
		fileNames.push_back("login_history.txt");
		fileNames.push_back("attendance.txt");
	}

	// Clear ONE specific file
	void clearFile(string fileName) {
		try {
			ofstream file(fileName, ios::trunc);  // trunc = wipes file completely
			if (!file.is_open())
				throw runtime_error("Could not open " + fileName);

			cout << fileName << " has been cleared." << endl;
			file.close();
		}
		catch (const runtime_error& e) {
			cout << "Error: " << e.what() << endl;
		}
	}

	// Clear ALL files at once
	void clearAllFiles() {
		try {
			cout << "=== Clearing All Files ===" << endl;
			for (int i = 0; i < fileNames.size(); i++) {
				ofstream file(fileNames[i], ios::trunc);
				if (!file.is_open())
					throw runtime_error("Could not clear " + fileNames[i]);

				cout << fileNames[i] << " cleared successfully." << endl;
				file.close();
			}
			cout << "=== All History Deleted ===" << endl;
		}
		catch (const runtime_error& e) {
			cout << "Error: " << e.what() << endl;
		}
	}

	// View which files exist
	void listFiles() {
		cout << "=== Registered Files ===" << endl;
		for (int i = 0; i < fileNames.size(); i++) {
			ifstream file(fileNames[i]);
			cout << fileNames[i] << " --> "
				<< (file.is_open() ? "Exists" : "Not Found") << endl;
			file.close();
		}
	}
};
struct AttendanceRecord {
	string studentID;
	string courseID;
	string type;
	string timestamp;
};

class AttendanceManager {
private:
	string getCurrentTimestamp() {
		time_t now = time(nullptr);
		tm* t = localtime(&now);
		ostringstream oss;
		oss << put_time(t, "%Y-%m-%d %H:%M:%S");
		return oss.str();
	}

	int timeToSeconds(const string& ts) {
		int h, m, s;
		sscanf(ts.c_str() + 11, "%d:%d:%d", &h, &m, &s);
		return h * 3600 + m * 60 + s;
	}

public:
	void markCheckIn(const string& studentID, const string& courseID) {
		try {
			if (studentID.empty() || courseID.empty())
				throw invalid_argument("Student ID and Course ID are required.");

			ofstream file("attendance.txt", ios::app);
			if (!file.is_open())
				throw runtime_error("Could not open attendance.txt");

			string ts = getCurrentTimestamp();
			file << "StudentID: " << studentID
				<< " | CourseID: " << courseID
				<< " | Type: CHECK_IN"
				<< " | Time: " << ts << "\n";
			file.close();
			cout << "CHECK-IN: " << studentID << " checked into "
				<< courseID << " at " << ts << endl;
		}
		catch (const exception& e) {
			cout << "Attendance Error: " << e.what() << endl;
		}
	}

	void markCheckOut(const string& studentID, const string& courseID) {
		try {
			if (studentID.empty() || courseID.empty())
				throw invalid_argument("Student ID and Course ID are required.");

			ifstream inFile("attendance.txt");
			if (!inFile.is_open())
				throw runtime_error("Could not read attendance.txt");

			bool hasCheckIn = false;
			string line;
			while (getline(inFile, line)) {
				if (line.find("StudentID: " + studentID) != string::npos &&
					line.find("CourseID: " + courseID) != string::npos &&
					line.find("CHECK_IN") != string::npos) {
					hasCheckIn = true;
				}
			}
			inFile.close();

			if (!hasCheckIn)
				throw runtime_error("No CHECK_IN found for " + studentID +
					" in " + courseID + ". Cannot check out.");

			ofstream outFile("attendance.txt", ios::app);
			if (!outFile.is_open())
				throw runtime_error("Could not open attendance.txt");

			string ts = getCurrentTimestamp();
			outFile << "StudentID: " << studentID
				<< " | CourseID: " << courseID
				<< " | Type: CHECK_OUT"
				<< " | Time: " << ts << "\n";
			outFile.close();
			cout << "CHECK-OUT: " << studentID << " left "
				<< courseID << " at " << ts << endl;
		}
		catch (const exception& e) {
			cout << "Attendance Error: " << e.what() << endl;
		}
	}

	void calculatePresenceDuration(const string& studentID, const string& courseID) {
		try {
			ifstream file("attendance.txt");
			if (!file.is_open())
				throw runtime_error("Could not open attendance.txt");

			string checkInTime = "";
			string checkOutTime = "";
			string line;

			while (getline(file, line)) {
				if (line.find("StudentID: " + studentID) == string::npos) continue;
				if (line.find("CourseID: " + courseID) == string::npos) continue;

				string ts = line.substr(line.rfind("Time: ") + 6);
				if (line.find("CHECK_IN") != string::npos) checkInTime = ts;
				if (line.find("CHECK_OUT") != string::npos) checkOutTime = ts;
			}
			file.close();

			cout << "\n=== Attendance Report ===" << endl;
			cout << "Student  : " << studentID << endl;
			cout << "Course   : " << courseID << endl;

			if (checkInTime.empty()) {
				cout << "Status   : No check-in record found." << endl;
				return;
			}

			cout << "Check-in : " << checkInTime << endl;

			if (checkOutTime.empty()) {
				cout << "Check-out: Still in class / no early exit logged." << endl;
				return;
			}

			cout << "Check-out: " << checkOutTime << endl;

			int inSec = timeToSeconds(checkInTime);
			int outSec = timeToSeconds(checkOutTime);
			int diff = outSec - inSec;

			if (diff < 0) {
				cout << "Error    : Check-out is before check-in." << endl;
				return;
			}

			int hours = diff / 3600;
			int minutes = (diff % 3600) / 60;
			int seconds = diff % 60;

			cout << "Duration : " << hours << "h " << minutes
				<< "m " << seconds << "s" << endl;

			if (diff < 1800)
				cout << "WARNING: Student was present for less than 30 minutes!" << endl;
		}
		catch (const exception& e) {
			cout << "Report Error: " << e.what() << endl;
		}
	}

	void viewCourseAttendance(const string& courseID) {
		try {
			ifstream file("attendance.txt");
			if (!file.is_open())
				throw runtime_error("Could not open attendance.txt");

			cout << "\n=== Attendance for Course: " << courseID << " ===" << endl;
			string line;
			bool found = false;
			while (getline(file, line)) {
				if (line.find("CourseID: " + courseID) != string::npos) {
					cout << line << endl;
					found = true;
				}
			}
			if (!found)
				cout << "No records found for course " << courseID << endl;
			file.close();
		}
		catch (const exception& e) {
			cout << "View Error: " << e.what() << endl;
		}
	}
};

int main() {

	

	return 0;
}