#ifndef SCHOOL_H
#define SCHOOL_H
#include <ostream>
#include <string>
#include <vector>
#include "Course.h"
#include "Student.h"

class School {
  std::vector<Course> courses;
  std::vector<Student> students;
  
public:
  void addCourses(std::string filename);
  void addStudents(std::string filename);
  bool isEnrolled(std::string student_id) const;
  unsigned int addAttendanceData(std::string filename);
  void listCourses(std::ostream& os) const;
  void listStudents(std::ostream& os) const;
  void outputCourseAttendance(std::ostream& os, std::string course_id) const;
  void outputStudentAttendance(std::ostream& os, std::string student_id, std::string course_id) const;
};

#endif