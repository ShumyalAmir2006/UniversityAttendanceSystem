#include<iostream>
using namespace std;
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
		this->cgpa = cgpa;
		this->department = department;
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
//INDEPENDENT CLASSES

class gates {
	int gate_No;
	string location;
	bool isopen;

public:
	void setGateDetails(int gateNo, string loc, bool open) {
		gate_No = gateNo;
		location = loc;
		isopen = open;
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
	void setCoureDetails(string id, string name, int credithrs, string instructorid) {
		courseID = id;
		course_Name = name;
		creditHours = credithrs;
		instructorID = instructorid;
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

		room_No = NewRoom;
		cout << " New Room has been Assigned to class is " << NewRoom << endl;
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

int main() {

	// Create instances of classes and demonstrate functionality
	return 0;
}