#include<iostream>
using namespace std;

// BASE CLASS
class person {
protected:
	string id;
	string name;
	string Email;
	string phone;

public:
	void setBasicINfo(string id, string name, string email, string phone) {
		this->id = id;
		this->name = name;
		this->Email = email;
		this->phone = phone;
	}

	void displaybasicinfo() {
		cout << "ID: " << id << endl;
		cout << "Name: " << name << endl;
		cout << "Email: " << Email << endl;
		cout << "Phone: " << phone << endl;
	}
};

// LOGIN CLASS
class login {
public:
	string user_name;
	string password;
	bool isauthenticated;
};

// CLASSES INHERITED BY THE PERSON CLASS

class student :public person {
	float cgpa;
	string department;
public:
	void setStudentDetails(float cgpa, string department) {
		this->cgpa = cgpa;
		this->department = department;
	}
	void enrollCourse(string course_Name) {
		// to enroll in a course
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

// ADMIN CONTROL
class admin : public administration {
	login login_details;
public:
	void setLoginDetails(string username, string password) {
		login_details.user_name = username;
		login_details.password = password;
	}
	void Authenticate() {
		// to authenticate admin
		cout << "Authenticating admin: " << name << endl;
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

// INDEPENDENT CLASSES
class gates {
	int gate_No;
	string location;
	bool isopen;
public:
};

class course {
	string courseID;
	string course_Name;
	int creditHours;
	string instructorID;
};

class report {
	string repertID;
	string title;
	string description;
	string date;
};

class department {
	string dpetID;
	string dept_Name;
	string Headofdept;
};

class schedual {
	string schedualID;
	string courseID;
	string day;
	string time;
	int room_No;
};

class notification {
private:
	string notificationID;
	string message;
	string recieverID;
	bool isRead;
};

int main() {

	// your code here to test classes

	return 0;
}