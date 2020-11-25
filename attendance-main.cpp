#include <iostream>
#include <string>
#include "School.h"
#include "Date.h"

using std::cin, std::cout,std::endl, std::string;

void printMenu() {
  cout << "--------------------------------------------------" << endl;
  cout << " '1': Load Courses" << endl;
  cout << " '2': Load Students" << endl;
  cout << " '3': Load Attendance File" << endl;
  cout << " '4': Output Attendance for Student in Course" << endl;
  cout << " '5': Output Course Attendance" << endl;
  cout << " '6': List Courses" << endl;
  cout << " '7': List Students" << endl;
  cout << " 'Q': Quit" << endl;
  cout << "--------------------------------------------------" << endl;
  cout << endl << "Please enter your choice: ";
}

void processLoadCourses(School& school) {
  string filename;
  cout << "Please enter filename: ";
  cin >> filename;
  try {
    school.addCourses(filename);
  } catch (std::invalid_argument& e) {
    cout << "Exception in processLoadCourses: " << e.what() << endl;
  }
}

void processLoadStudents(School& school) {
  string filename;
  cout << "Please enter filename: ";
  cin >> filename;
  try {
    school.addStudents(filename);
  } catch (std::invalid_argument& e) {
    cout << "Exception in processLoadStudents: " << e.what() << endl;
  }
}

void processLoadAttendance(School& school) {
  string filename;
  cout << "Please enter filename: ";
  cin >> filename;
  try {
    unsigned int nb_invalid_entries = school.addAttendanceData(filename);
    if (nb_invalid_entries != 0) {
      cout << "File " << filename << " contains " << nb_invalid_entries
        << " invalid entries" << endl;
    }
  } catch (std::invalid_argument& e) {
    cout << "Exception in processLoadAttendance: " << e.what() << endl;
  }
}

void processOutputAttendanceStudent(School& school) {
  string studentID, courseID;
  cout << "Please enter student UIN: ";
  cin >> studentID;
  if (!school.isEnrolled(studentID)) {
    cout << "Invalid student id " << studentID << endl; 
    return;
  }

  cout << "Please enter course id: ";
  cin >> courseID;
  try {
    school.outputStudentAttendance(cout, studentID, courseID);
  } catch (std::invalid_argument& e) {
    // course id
    cout << "Exception in processOutputAttendanceStudent: " << e.what() << endl; 
  }
}

void processOutputAttendanceCourse(School& school) {
  string courseID;
  cout << "Please enter course id: ";
  cin >> courseID;
  try {
    school.outputCourseAttendance(cout, courseID);
  } catch (std::invalid_argument& e) {
    // invalid  course id
    cout << "Exception in processOutputAttendanceCourse: " << e.what() << endl; 
  }
}

int main() {   
  School school;
  char choice = 'a';
  
  do {
    printMenu();
    cin >> choice;
    switch (tolower(choice)) {
      case '1': processLoadCourses(school); break;
      case '2': processLoadStudents(school); break;
      case '3': processLoadAttendance(school); break;
      case '4': processOutputAttendanceStudent(school); break;
      case '5': processOutputAttendanceCourse(school); break;
      case '6': school.listCourses(cout); break;
      case '7': school.listStudents(cout); break;
      case 'q': break; // do nothing
      default:
        cout << choice << " is an invalid option. Please try again." << endl;
    }
  } while (tolower(choice) != 'q');
}
