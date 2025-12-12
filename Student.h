//
// Created by sharo on 09/12/2025.
//

#ifndef STUDENT_H
#define STUDENT_H
#include "AVLTree.h"


class Course;

class Student{
private:
    int student_id;
    int points_earned;
    int bonus_offset;

    AVLTree<int,Course*> enrolled_courses;



public:
    Student(int id, int global_points)
            : student_id(id),points_earned(0),bonus_offset(global_points){}
    ~Student() = default;
    Student(const Student& other) = delete;
    Student& operator=(const Student& other) = delete;
    const AVLTree<int,Course*>& get_enrolled_courses() const {
        return enrolled_courses;
    }
    void addCourse(int courseId, Course* course){
        enrolled_courses.insert(courseId, course);
    }
    void removeCourse(int courseId){
        enrolled_courses.remove(courseId);
    }
    void addPoints(int points) {
        points_earned += points;
    }
    int getPointsEarned() const {
        return points_earned;
    }

    int getBonusOffset() const {
        return bonus_offset;
    }

};


#endif //STUDENT_H
