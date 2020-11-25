#include <string>
#include <iostream>
#include "AttendanceRecord.h"
#include "Date.h"

using std::cout, std::string;

// constructor
AttendanceRecord::AttendanceRecord(string course_id, string student_id, Date time) : course_id(course_id), student_id(student_id), time(time) {}

string AttendanceRecord::getCourseID() const {
    return course_id;
}

string AttendanceRecord::getStudentID() const {
    return student_id;
}

Date AttendanceRecord::getDate() const {
    return time;
}

std::ostream& operator<<(std::ostream& os, AttendanceRecord& ar) {

    os << ar.getDate().getDateTime() << "," << ar.getCourseID() << "," << ar.getStudentID();
    return os;

}