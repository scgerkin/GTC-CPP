#ifndef STUDENT_COURSE_GRADES_H
#define STUDENT_COURSE_GRADES_H
#include <string>



struct StudentCourseGrade {
    // structure to store information about a student, their tests, average
    // score and grade

    std::string name;
    unsigned int idNum;
    double * testScores;
    double average;
    char grade;

    ~StudentCourseGrade() {
        // free memory used by testScores if not already done
        if (testScores != NULL) {
            delete[] testScores;
        }
    }
};

#endif // !STUDENT_COURSE_GRADES_H
