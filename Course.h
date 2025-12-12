

#ifndef COURSE_H
#define COURSE_H
#include "AVLTree.h"
class Student;

class Course
{
private:
    int course_id;
    int course_points;
    AVLTree<int,Student*> enrolled_students;

public:
    Course(int id, int points) : course_id(id), course_points(points){}
    ~Course()() = default;
    Course(const Student& other) = delete;
    Course& operator=(const Course& other) = delete;
    const AVLTree<int, Student*>& get_enrolled_students() const {
        return  enrolled_students;
    }
    void addStudent(int studentId, Student* student){
        enrolled_students.insert(studentId, student);
    }
    void removeStudent(int studentId){
        enrolled_students.remove(studentId);
    }

    Student* find_student(int id) const{
        Student** ptr = enrolled_students.find(id);
        return ptr ? *ptr : nullptr;
    }

    int getPoints() const {
        return course_points;
    }

};

#endif //COURSE_H
