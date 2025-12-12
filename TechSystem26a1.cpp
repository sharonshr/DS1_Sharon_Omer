// You can edit anything you want in this file.
// However you need to implement all public StudentCourseManager function, as provided below as a template

#include "TechSystem26a1.h"
#include "Student.h"
#include "Course.h"


TechSystem::TechSystem(){
    global_dean_bonus = 0;
}

TechSystem::~TechSystem() {
    students.destroyValues();
    courses.destroyValues();
}

StatusType TechSystem::addStudent(int studentId)
{
    if (studentId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (students.contains(studentId)) {
        return StatusType::FAILURE;
    }
    Student* student = nullptr;
    try {
        student = new Student(studentId, global_dean_bonus);
    } catch (const std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }

    students.insert(studentId, student);

    return StatusType::SUCCESS;
}
StatusType TechSystem::removeStudent(int studentId)
{
    if (studentId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    Student** studentPtr = students.find(studentId);
    if (studentPtr == nullptr) {
        return StatusType::FAILURE;
    }

    Student* student = *studentPtr;

    if (!student->get_enrolled_courses().isEmpty()) {
        return StatusType::FAILURE;
    }
    students.remove(studentId);
    delete student;
    return StatusType::SUCCESS;
}

StatusType TechSystem::addCourse(int courseId, int points)
{
    if (courseId <= 0 || points <= 0) {
        return StatusType::INVALID_INPUT;
    }

    if (courses.contains(courseId)) {
        return StatusType::FAILURE;
    }
    Course* course = nullptr;
    try {
        course = new Course(courseId, points);
    } catch (const std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }
    courses.insert(courseId, course);
    return StatusType::SUCCESS;
}

StatusType TechSystem::removeCourse(int courseId)
{
    if (courseId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    Course** coursePtr = courses.find(courseId);
    if (coursePtr == nullptr) {
        return StatusType::FAILURE;
    }
    Course* course = *coursePtr;

    if (!course->get_enrolled_students().isEmpty()) {
        return StatusType::FAILURE;
    }
    courses.remove(courseId);

    delete course;

    return StatusType::SUCCESS;
}

StatusType TechSystem::enrollStudent(int studentId, int courseId)
{

    if (studentId <= 0 || courseId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    Student** studentPtr = students.find(studentId);
    if (studentPtr == nullptr) {
        return StatusType::FAILURE;
    }

    Course** coursePtr = courses.find(courseId);
    if (coursePtr == nullptr) {
        return StatusType::FAILURE;
    }

    Student* student = *studentPtr;
    Course* course   = *coursePtr;

    if (student->get_enrolled_courses().contains(courseId)) {
        return StatusType::FAILURE;
    }

    try {
        student->addCourse(courseId, course);
        course->addStudent(studentId, student);
    } catch (const std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType TechSystem::completeCourse(int studentId, int courseId)
{
    if (studentId <= 0 || courseId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    Course** coursePtr = courses.find(courseId);
    if (coursePtr == nullptr) {
        return StatusType::FAILURE;
    }

    Course* course = *coursePtr;
    Student* student = course->find_student(studentId);
    if (student == nullptr) {
        return StatusType::FAILURE;
    }
    student->addPoints(course->getPoints());

    student->removeCourse(courseId);
    course->removeStudent(studentId);

    return StatusType::SUCCESS;
}


StatusType TechSystem::awardAcademicPoints(int points)
{
    if (points <= 0) {
        return StatusType::INVALID_INPUT;
    }
    global_dean_bonus += points;
    return StatusType::SUCCESS;
}

output_t<int> TechSystem::getStudentPoints(int studentId)
{
    if (studentId <= 0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    Student** studentPtr = students.find(studentId);
    if (studentPtr == nullptr) {
        return output_t<int>(StatusType::FAILURE);
    }

    Student* student = *studentPtr;

    int totalPoints =
        student->getPointsEarned()
        + (global_dean_bonus - student->getBonusOffset());

    return output_t<int>(totalPoints);
}
