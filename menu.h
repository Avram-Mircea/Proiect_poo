#ifndef MENU_H
#define MENU_H

#include"student.h"
#include"admin.h"

class menu
{
public:
	menu();

	void menu_log();
	
private:
	user log_in();
	void create_account(user& _user);

	void menu_student(student& _student);
	void menu_admin(admin& _admin);

	void show_file_content(string option);
	void show_file_content(string option, string filter);

	void wait_a_key();
};

#endif // !

