#include <iostream>
#include <string>
#include "Student.h"

using std::cout, std::endl;

Student::Student(std::string student_id, std::string name) : id(student_id), name(name), course_ids(0, "") {}

void Student::addCourse(std::string course_id) {

    // loop through length of course_ids vector to try and find a match for the input course id
    for (size_t i = 0; i < course_ids.size(); i++) {
        
        // throw invalid argument if the course already exists
        if (course_ids.at(i) == course_id) {

            throw std::invalid_argument("This course already exists for the student");
        
        }

    }

    course_ids.push_back(course_id);

}

void Student::listCourses(std::ostream& os) const {

    os << "Courses for " << id << endl;

    if (course_ids.size() == 0) {

        os << "No courses" << endl;

    } else {
        for (size_t i = 0; i < course_ids.size(); i++) {

            os << course_ids.at(i) << endl;

        }
    }
}

std::string Student::get_id() const {

    return id;

}

std::string Student::get_name() const {

    return name;
    
}