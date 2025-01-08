#include "user.h"

char trash;

void get_console_line(string& input)
{
	char c;
	c = getchar();
	while (c != '\n')
	{
		input.push_back(c);
		c = getchar();
	}
}

user::user()
{
	name = "";
	password = "";
	position = "";
}

void user::set_user(string _name, string _password, string _position)
{
	name = _name;
	password = _password;
	position = _position;
}

int user::exist()
{
	return name.compare("");
}

bool user::is_student()
{
	if (!position.compare("student"))
		return true;
	else
		return false;
}

void user::show()
{
	cout << name << endl << password << endl << position;
}

string user::get_name()
{
	return name;
}

string user::get_password()
{
	return password;
}
