#ifndef STUDENT_H
#define STUDENT_H
#include"user.h"
#include"book.h"
#include"course.h"
#include<vector>

class student : public user
{
public:
	student();
	student(user& _user);

	void show();
	void recommend();

	void borrow_a_book();
	void book_a_course();

	void return_a_book();
	void release_a_course();

	int size_books();
	int size_courses();
	bool at_school();

	void save_info_student();

private:
	vector <book> books;
	vector <course> courses;
	string min_grade;
	int interest_in_subjects[26];
	
	void decrease_object(string& line);
	void increase_object(string& line);

	int book_is_borrow(string& book_name, string& book_grade, string& book_author);
	int course_is_book(string& course_name, string& course_proffesor);
};

#endif // !STUDENT_H