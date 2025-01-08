#include "menu.h"
char option;
extern char trash;

menu::menu()
{ }

void menu::menu_log()
{
	user _user;

	system("cls");
	cout << "1.Logare cont\n2.Creare cont\n3.Iesire aplicatie\n\nOptiune: ";
	cin >> option;

	switch (option)
	{
	case '1':
		_user = log_in();
		if (_user.exist())
		{
			if (_user.is_student())
			{
				student _student(_user);
				menu_student(_student);
			}
			else
			{
				admin _admin(_user);
				menu_admin(_admin);
			}
		}
		else
			menu_log();
		break;
	case '2':
		create_account(_user);
		if (_user.exist())
		{
			student _student(_user);
			menu_student(_student);
		}
		else
			menu_log();
		break;
	case '3':
		//return 0;
		break;
	default:
		cout << "\033[91mObtiune invalida!\033[0m";
		wait_a_key();
		menu_log();
		break;
	}
}

user menu::log_in()
{
	string user_name, password_try, password_real, _position;
	user _user;
	char result;

	system("cls");
	cout << "Numele contului: ";
	cin >> user_name;

	ifstream file(user_name + ".txt");
	if (file.is_open())
	{
		//account exists
		getline(file, password_real);

		do
		{
			//test the password
			cout << "Parola: ";
			cin >> password_try;
			result = password_real.compare(password_try);
			if (result)
			{
				//wrong password
				cout << "\033[91mParola gresita\033[0m";
				wait_a_key();
				cout << "\x1b[2K";
				cout << "\x1b[1A" << "\x1b[2K";
				cout << "\x1b[1A" << "\x1b[2K";
			}
		} while (result);

		//see what position the user have
		getline(file, _position);
		if (_position.compare("admin"))
			_user.set_user(user_name, password_real, "student");
		else
			_user.set_user(user_name, password_real, "admin");

		file.close();
		system("cls");
		cout << "Buna " << user_name << "!\n\n";
		trash = getchar();
	}
	else
	{
		//account does not exist
		cout << "\033[91mNu exista cont!\033[0m" << endl << endl << "Creati cont?[D/N] ";
		cin >> result;

		if (result == 'D')
			create_account(_user);//create a new account
		else
		{
			cout << endl << "\033[91mNu puteti imprumuta carti sau sa va inscrieti la cursuri fara cont!\033[0m";
			wait_a_key();
		}
	}

	return _user;
}

void menu::create_account(user& _user)
{
	string name, password;
	ifstream possible_account;

	system("cls");
	cout << "Numele dumneavoastra: ";
	cin >> name;
	possible_account.open(name + ".txt");

	if (!possible_account.is_open()) //no account with this name
	{
		cout << "Parola contului: ";
		cin >> password;

		//create a new file with username and enter the password and position in it
		ofstream file(name + ".txt");
		file << password << endl << "student" << endl;
		file.close();

		_user.set_user(name, password, "student");
	}
	else
	{
		cout << "\033[91mCont deja existent cu acest nume!\nIncercati sa va logati sau creati un cont cu alt nume.\033[0m";
		_user.set_user("", "", "");
		wait_a_key();
	}
}

void menu::menu_student(student& _student)
{
	system("cls");

	cout << "1.Lista carti\n2.Lista cursuri\n3.Informatii cont\n4.Alocare carte\n5.Inscriere la curs\n6.Returnare carte\n7.Stergere curs\n8.Delogare\n\nOptiune: ";
	cin >> option;
	trash = getchar();

	switch (option)
	{
	case '1':
		cout << "Doriti filtru?[D/N] ";
		cin >> option;
		trash = getchar();
		if (option == 'D')
		{
			string filter;
			cout << "Categoria de carti: ";
			cin >> filter;
			trash = getchar();
			show_file_content("carti", filter);
		}
		else
			show_file_content("carti");
		menu_student(_student);
		break;
	case '2':
		cout << "Doriti filtru?[D/N] ";
		cin >> option;
		trash = getchar();
		if (option == 'D')
		{
			string filter;
			cout << "Categoria de cursuri: ";
			cin >> filter;
			trash = getchar();
			show_file_content("cursuri", filter);
		}
		else
			show_file_content("cursuri");
		menu_student(_student);
		break;
	case '3':
		_student.show();
		trash = getchar();
		menu_student(_student);
		break;
	case '4':
		if(_student.size_books() < 3)
			_student.borrow_a_book();
		else
			cout << "\033[91mNumar maxim de carti imprumutate este 3!\033[0m";
		trash = getchar();
		menu_student(_student);
		break;
	case '5':
		if (!_student.at_school())
		{
			if (_student.size_courses() < 3)
				_student.book_a_course();
			else
				cout << "\033[91mNumar maxim de cursuri rezervate este 3!\033[0m";
		}
		else
			cout << "\033[91mNu aveti pregatirea necesara pentru a va inscrie la cursuri!\033[0m";
		trash = getchar();
		menu_student(_student);
		break;
	case'6':
		if (_student.size_books() > 0)
			_student.return_a_book();
		else
			cout << "\033[91mNu aveti carti imprumutate!\033[0m";
		trash = getchar();
		menu_student(_student);
		break;
	case'7':
		if (_student.size_courses() > 0)
			_student.release_a_course();
		else
			cout << "\033[91mNu aveti locuri la cursuri rezervate!\033[0m";
		trash = getchar();
		menu_student(_student);
		break;
	case '8':
		_student.save_info_student();
		menu_log();
		break;
	default:
		cout << "\033[91mObtiune invalida!\033[0m";
		trash = getchar();
		menu_student(_student);
		break;
	}
}

void menu::menu_admin(admin& _admin)
{
	string choice;
	system("cls");

	cout << "1.Lista carti\n2.Lista cursuri\n3.Creare nou cont admin\n4.Schimbare parola pentru un cont\n5.Stergerea unui cont\n";
	cout << "6.Adaugarea de noi carti/cursuri\n7.Stergere carti/cursuri\n8.Schimbarea de carti/locuri pentru cursuri\n9.Delogare\n\nOptiune: ";
	cin >> option;
	trash = getchar();

	switch (option)
	{
	case '1':
		cout << "Doriti filtru?[D/N] ";
		cin >> option;
		trash = getchar();
		if (option == 'D')
		{
			string filter;
			cout << "Categoria de carti: ";
			cin >> filter;
			trash = getchar();
			show_file_content("carti", filter);
		}
		else
			show_file_content("carti");
		menu_admin(_admin);
		break;
	case '2':
		cout << "Doriti filtru?[D/N] ";
		cin >> option;
		trash = getchar();
		if (option == 'D')
		{
			string filter;
			cout << "Categoria de cursuri: ";
			cin >> filter;
			trash = getchar();
			show_file_content("cursuri", filter);
		}
		else
			show_file_content("cursuri");
		menu_admin(_admin);
		break;
	case '3':
		_admin.create_new_admin();
		trash = getchar();
		menu_admin(_admin);
		break;
	case '4':
		_admin.change_account_password();
		trash = getchar();
		menu_admin(_admin);
		break;
	case '5':
		_admin.remove_account();
		trash = getchar();
		menu_admin(_admin);
		break;
	case'6':
		cout << "Ce doriti sa adaugati?(carti/cursuri)";
		get_console_line(choice);
		if (!choice.compare("carti"))
			_admin.add_book();
		else if (!choice.compare("cursuri"))
			_admin.add_course();
		else
			cout << "\033[91mObtiune invalida!\033[0m";
		trash = getchar();
		menu_admin(_admin);
		break;
	case'7':
		cout << "Ce doriti sa stergeti?(carti/cursuri)";
		get_console_line(choice);
		if (!choice.compare("carti"))
			_admin.remove_book();
		else if (!choice.compare("cursuri"))
			_admin.remove_course();
		else
			cout << "\033[91mObtiune invalida!\033[0m";
		trash = getchar();
		menu_admin(_admin);
		break;
	case '8':
		cout << "Ce doriti sa schimbati?(carti/cursuri)";
		get_console_line(choice);
		if (!choice.compare("carti"))
			_admin.change_number_of_book();
		else if (!choice.compare("cursuri"))
			_admin.change_number_of_course();
		else
			cout << "\033[91mObtiune invalida!\033[0m";
		break;
	case '9':
		menu_log();
		break;
	default:
		cout << "\033[91mObtiune invalida!\033[0m";
		trash = getchar();
		menu_admin(_admin);
		break;
	}
}

void menu::show_file_content(string option)
{
	ifstream file(option + ".txt");
	string line;

	while (!file.eof())
	{
		getline(file, line);
		cout << endl << line;
	}
	trash = getchar();

	file.close();
}

void menu::show_file_content(string option, string filter)
{
	ifstream file(option + ".txt");
	string line;

	while (!file.eof())
	{
		getline(file, line);
		if(!line.compare(line.find('(') + 1, filter.size(), filter))
			cout << endl << line;
	}
	trash = getchar();

	file.close();
}

void menu::wait_a_key()
{
	trash = getchar();
	trash = getchar();
}