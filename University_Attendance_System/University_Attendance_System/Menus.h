#pragma once
#include "AttendanceManager.h"
#include "FileManager.h"
#include "Admin.h"

void showStudentMenu(AttendanceManager& am);
void showFacultyMenu(AttendanceManager& am);
void showSecurityMenu();
void showAdminMenu(AttendanceManager& am, FileManager& fm);