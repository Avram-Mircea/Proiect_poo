#ifndef USER_H
#define USER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

void get_console_line(string& input);

class user
{
public:
	user();
	void set_user(string _name, string _password, string _position);

	int exist();
	bool is_student();

	void show();

	string get_name();
	string get_password();
	
protected:
	string name;
	string password;
	string position;
};


#endif // !USER_H