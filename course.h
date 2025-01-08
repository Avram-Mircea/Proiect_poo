#ifndef COURSE_H
#define COURSE_H
#include<iostream>

using namespace std;

class course
{
public:
	void clean();
	void set_course(string& input);
	void info();

	string get_name();
	string get_professor();
	string get_category();

private:
	string name;
	string professor;
	string category;
};

#endif // !COURSE_H
