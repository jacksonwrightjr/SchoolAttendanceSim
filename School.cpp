#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "School.h"
#include "AttendanceRecord.h"
#include "Course.h"

using std::string, std::ostream, std::ifstream, std::istringstream, std::endl, std::cout;

// one method is provided to students; students implement all other methods
void School::addStudents(string filename) {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    throw std::invalid_argument("addStudents: can't open file");
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string uin;
    getline(ss, uin, ',');
    string name;
    getline(ss, name);
    if (!ss.fail()) {
        Student student(uin, name);
        bool exists = false;
        for (Student s : students) {
            if (s == student) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            students.push_back(student);
        }
    }
  }
}

bool School::isEnrolled(string student_id) const {

  for (size_t i = 0; i < students.size(); i++) {

    if (students[i].get_id() == student_id) {
      return true;
    }

  }

  return false;

}

void School::listStudents(std::ostream& os) const {

  if (students.size() == 0) {
    os << "No students" << endl;

  } else {
    for (size_t i = 0; i < students.size(); i++) {

      os << students[i].get_id() << "," << students[i].get_name() << endl;

    }

  }
}

void School::addCourses(string filename) {

  string placeholderID;
  string placeholderStartHr;
  string placeholderStartMin;
  string placeholderEndHr;
  string placeholderEndMin;
  string placeholderTitle;

  ifstream courseFile;
  courseFile.open(filename);

  // if filename is invalid we can't add courses
  if (!courseFile.is_open()) {
    throw std::invalid_argument("addCourses: unable to open file");
  } else {
    while (!courseFile.eof()) {

      string line;
      getline(courseFile, line);

      istringstream ss(line);
      if (ss.fail()) {
        break;
      }
      getline(ss, placeholderID, ',');
      if (placeholderID == "") {
        break;
      }
      getline(ss, placeholderStartHr, ':');
      getline(ss, placeholderStartMin, ',');
      getline(ss, placeholderEndHr, ':');
      getline(ss, placeholderEndMin, ',');
      getline(ss, placeholderTitle, '\n');

      // declare date types for start and end
      Date start(stoi(placeholderStartHr), stoi(placeholderStartMin));
      Date end(stoi(placeholderEndHr), stoi(placeholderEndMin));

      Course x(placeholderID, placeholderTitle, start, end);

      //cout << "before the other cout" << endl;

      //cout << "Pushing back course: " << placeholderID << " title: " << placeholderTitle << endl;

      //cout << "Start time is " << start.getTime() << " and end time is " << end.getTime() << endl;

      courses.push_back(x);

    }
  }

  courseFile.close();

}

void School::listCourses(std::ostream& os) const {

  // if there are no courses, output no courses
  if (courses.size() == 0) {
    os << "No courses" << endl;
  } else {
    for (size_t i = 0; i < courses.size(); i++) {

      // throw into the ostream in this format: "ID,start hour:start minute,end hour:end minute, title"
      os << courses[i].getID() << "," << courses[i].getStartTime().getTime(false) << "," << courses[i].getEndTime().getTime(false) << "," << courses[i].getTitle() << endl;

    }
  }
}

unsigned int School::addAttendanceData(string filename) {

  // declaring components of date object
  string year;
  string month;
  string day;
  string hour;
  string min;
  string sec;
  string courseID;
  string studentID;
  int invalidCount = 0;
  bool valid;

  ifstream attendanceFile;
  attendanceFile.open(filename);

  if (!attendanceFile.is_open()) {
    throw std::invalid_argument("addAttendanceData: Invalid filename");
  }

  while(!attendanceFile.eof()) {

    try {
      valid = false;
    
      // get yyyy-mm-dd
      getline(attendanceFile, year, '-');
      if (year == "") {
        break;
      }
      getline(attendanceFile, month, '-');
      getline(attendanceFile, day, ' ');

      // get hr:min:sec
      getline(attendanceFile, hour, ':');
      getline(attendanceFile, min, ':');
      getline(attendanceFile, sec, ',');

      // get course ID
      getline(attendanceFile, courseID, ',');

      // get student ID
      getline(attendanceFile, studentID, '\n');

      // check records for course ID
      for (size_t i = 0; i < courses.size(); i++) {
        if (courses.at(i).getID() == courseID) {
          valid = true;
          //cout << "The course ID is valid: " << courses.at(i).getID() << endl;
          break;
        }
      }

      // check records for student ID
      for (size_t i = 0; i < students.size(); i++) {
        // check if student in the course is a valid student
        if (isEnrolled(studentID)) {
          valid = true;
          //cout << "Student ID valid : " << students.at(i).get_id() << endl;
          break;
        }
      }

      // put together time data in Date format
      Date time(stoi(year), stoi(month), stoi(day), stoi(hour), stoi(min), stoi(sec));
      //cout << "Year: " << year << " month: " << month << " day: " << day << " hour: " << hour << " min: "<< min << " sec: " << sec << endl;

      // check date validity
      if (!time.isValid()) {
        valid = false;
        //cout << "Invalid time" << endl;
      }

      // put together a new attendance record object with course, student, and time
      AttendanceRecord ar(courseID, studentID, time);

      for (size_t i = 0; i < courses.size(); i++) {
        if (courseID == courses.at(i).getID()) {
          courses.at(i).addAttendanceRecord(ar);
        }
        //cout << "adding attendance record for " << courses.at(i).getID() << " with start time " << courses.at(i).getStartTime().getTime() << endl;
      } 

      if (!valid) {
        throw std::invalid_argument("addAttendanceData: Invalid data provided");
      }
    } catch (std::invalid_argument) {
      invalidCount += 3;
    }

  }
  return invalidCount;
}

void School::outputCourseAttendance(std::ostream& os, string course_id) const {
  bool courseNotFound = true;

  if (courses.size() == 0) {
    os << "No courses" << endl;
  } else {
    // loop through for a matching course ID
    for (size_t i = 0; i < courses.size(); i++) {

      if (courses[i].getID() == course_id) { // if course ID matches, we can output its attendance and break the loop
        courses.at(i).outputAttendance(os);
        courseNotFound = false;
        break;
      }
    
    }
    if (courseNotFound) {
      throw std::invalid_argument("outputCourseAttendance: course ID not found");
    }
  }
}

void School::outputStudentAttendance(std::ostream& os, string student_id, string course_id) const {
  bool courseNotFound = true;

  if (courses.size() == 0) {
    os << "No courses" << endl;
  } else {
    // loop for course ID
    for (size_t i = 0; i < courses.size(); i++) {

      if(courses.at(i).getID() == course_id) {
        courses.at(i).outputAttendance(os, student_id);
        courseNotFound = false;
        break;
      }

    }
    if (courseNotFound) {
      throw std::invalid_argument("outputStudentAttendance: course ID not found");
    }
  }

}