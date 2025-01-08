#ifndef ADMIN_H
#define ADMIN_H
#include"user.h"
#include"book.h"
#include"course.h"

class admin : public user
{
public:
	admin();
	admin(user& _user);

	void create_new_admin();
	void change_account_password();
	void remove_account();

	void add_book();
	void add_course();

	void remove_book();
	void remove_course();

	void change_number_of_book();
	void change_number_of_course();

private:
	int compare(string line, string name_book, string grade_book, string author_book, int was_put);
	int compare(string line, string name_book, string author_book, int was_put);
	int compare(string line, string name_book, string grade_book, string author_book);
	int compare(string line, string name_book, string author_book);
	void change_number(string& line, string number);

};

#endif // !ADMIN_H