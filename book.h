#ifndef BOOK_H
#define BOOK_H
#include<iostream>

using namespace std;

class book
{
public:
	void clean();
	void set_book(string& input);
	void info();

	string get_name();
	string get_grade();
	string get_author();
	string get_category();

private:
	string name;
	string grade;
	string author;
	string category;
};

#endif // !BOOK_H
