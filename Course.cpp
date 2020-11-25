#include <iostream>
#include <string>
#include <vector>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"

using std::string, std::ostream, std::endl, std::cout;

// course constructor
Course::Course(string id, string title, Date startTime, Date endTime) : id(id), title(title), startTime(startTime), endTime(endTime) {}

// ********************** getters **********************
string Course::getID() const { return id; }

string Course::getTitle() const { return title; }

Date Course::getStartTime() const { return startTime; }

Date Course::getEndTime() const { return endTime; }

void Course::addAttendanceRecord(AttendanceRecord ar) {
    bool x = false;
    if (ar.getDate().getHour() < startTime.getHour() || ar.getDate().getHour() > endTime.getHour()) {
        //cout << "Hour error: " << ar.getDate().getTime() << " start: " << startTime.getTime() << " end: " << endTime.getTime() << endl;
        x = true;
    } else if ((ar.getDate().getMin() < startTime.getMin() && ar.getDate().getHour() == startTime.getHour()) || (ar.getDate().getMin() > endTime.getMin() && ar.getDate().getHour() == endTime.getHour())) {
        //cout << "Minute error: " << ar.getDate().getTime() << " start: " << startTime.getTime() << " end: " << endTime.getTime() << endl;
        x = true;
    } else if ((ar.getDate().getSec() < startTime.getSec() && ar.getDate().getMin() == startTime.getMin()) || (ar.getDate().getSec() > endTime.getSec() && ar.getDate().getMin() == endTime.getMin())) {
        if ((ar.getDate().getHour() == startTime.getHour()) && ar.getDate().getMin() > startTime.getMin()) {
            x = false;
        } else if (ar.getDate().getHour() > startTime.getHour() && ar.getDate().getHour() < endTime.getHour()) {
            x = false;
        } else {
            x = true;
            //cout << "Second error: " << ar.getDate().getTime() << " start: " << startTime.getTime() << " end: " << endTime.getTime() << endl;
        }
    }

    if (x) {
        //cout << "ERROR FOR COURSE ID: " << ar.getCourseID() << endl;
        throw std::invalid_argument("addAttendanceRecord: Invalid time provided");
    } else {
        attendanceRecords.push_back(ar);
    }
   //cout << ar.getDate() << endl;
   //attendanceRecords.push_back(ar);
   
}

void Course::outputAttendance(std::ostream& os) const {

    // if there are no records tell the user
    if (attendanceRecords.size() == 0) {
        os << "No records" << endl;
    } else {
        for (size_t i = 0; i < attendanceRecords.size(); i++) {

            os << attendanceRecords.at(i).getDate().getDateTime() << "," << attendanceRecords.at(i).getCourseID() << "," << attendanceRecords[i].getStudentID() << endl;

        }
    }
}

void Course::outputAttendance(std::ostream& os, string student_id) const {

    bool foundStudent = false;

    // search for the student
    for (size_t i = 0; i < attendanceRecords.size(); i++) {
        if (student_id == attendanceRecords.at(i).getStudentID()) {
            foundStudent = true;
            break;
        }
    }

    // if there are no records tell the user
    if (attendanceRecords.size() == 0 || !foundStudent) {
        os << "No records" << endl;
    } else {
        for (size_t i = 0; i < attendanceRecords.size(); i++) {

            // only output the record if it belongs to the student
            if (student_id == attendanceRecords.at(i).getStudentID()) {
                os << attendanceRecords.at(i).getDate().getDateTime() << "," << attendanceRecords.at(i).getCourseID() << "," << attendanceRecords[i].getStudentID() << endl;
            }

        }
    }

}

/*
int main() {
    Course g("551", "Biochem", Date(15, 0), Date(15, 50));
    cout << g.getStartTime().getTime() << endl;
    AttendanceRecord ar("551", "1", Date(2020, 8, 5, 15, 8, 0));
    g.addAttendanceRecord(ar);
    g.outputAttendance(cout);

    Date a(9, 35, 0);
    Date greaterthana(2019, 11, 5, 9, 35, 23);
    AttendanceRecord x("121", "1", Date(2019,11,5,9,35,23));
    AttendanceRecord y("121", "3", Date(2019, 11, 6, 9, 40, 0));
    if (greaterthana <= a) {
        cout << "Working"<< endl;
    } else {
        Course c("121", "Intro to programming", Date(9, 35, 0), Date(10, 50, 0));
        c.addAttendanceRecord(x);
        c.addAttendanceRecord(y);
        c.outputAttendance(cout);
    }

    return 0;
}
*/