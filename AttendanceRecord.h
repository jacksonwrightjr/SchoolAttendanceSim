#ifndef ATTENDANCERECORD_H
#define ATTENDANCERECORD_H

#include <string>
#include <iostream>
#include "Date.h"

class AttendanceRecord {
  std::string course_id;
  std::string student_id;
  Date time;

public:
  AttendanceRecord(std::string course_id, std::string student_id, Date time);
  std::string getCourseID() const;
  std::string getStudentID() const;
  Date getDate() const;
};

std::ostream& operator<<(std::ostream& os, const AttendanceRecord& ar);

#endif