#include "admin.h"

extern char trash;

admin::admin()
{
	name = "";
	password = "";
	position = "";
}

admin::admin(user& _user)
{
	name = _user.get_name();
	password = _user.get_password();
	position = "admin";
}

void admin::create_new_admin()
{
	string _name, _passowrd;

	cout << "Numele noului admin: ";
	get_console_line(_name);

	ifstream file(_name + ".txt");
	
	if (!file)
	{
		ofstream file(_name + ".txt");
		cout << "Parola noului cont: ";
		get_console_line(_passowrd);

		file << _passowrd << endl << "admin";
		cout << "\033[92mCont creat cu succes!\033[0m";
	}
	else
		cout << "\033[91mCont deja existent cu acest nume!\033[0m";
	
	file.close();
}

void admin::change_account_password()
{
	string _name, file_content, line;

	cout << "Numele contului: ";
	get_console_line(_name);
	ifstream file(_name + ".txt");

	if (file)
	{
		cout << "Parola noua a contului: ";
		get_console_line(file_content);

		getline(file,line);

		while (!file.eof())
		{
			getline(file, line);
			file_content += '\n';
			file_content += line;
		}

		file.close();

		ofstream file(_name + ".txt");
		file << file_content;
		file.close();
		cout << "\033[92mParola schimbata cu succes!\033[0m";
	}
	else
		cout << "\033[91mFisier inexistent!\033[0m";

	file.close();
}

void admin::remove_account()
{
	string file_name;

	cout << "Numele contului pe care doriti sa-l stergeti: ";
	get_console_line(file_name);
	file_name += ".txt";

	if (file_name.compare("carti.txt") && file_name.compare("cursuri.txt"))
		if (remove(file_name.c_str()))
			cout << "\033[91mCont inexistent!\033[0m";
		else
			cout << "\033[92mCont sters cu succes!\033[0m";
	else
		cout << "\033[91mFisierele cartilor si al cursurilor nu se pot sterge!\033[0m";
}

void admin::add_book()
{
	ifstream file("carti.txt");
	string line, name_book, grade_book, author_book, category_book, number_of_books, file_content;
	int was_put = 0;

	cout << "Numele noi carti: ";
	get_console_line(name_book);

	cout << "Clasa: ";
	get_console_line(grade_book);

	cout << "Numele autorului: ";
	get_console_line(author_book);

	cout << "Categoria: ";
	get_console_line(category_book);

	cout << "Numarul de exemplare disponibile: ";
	get_console_line(number_of_books);

	while (!file.eof())
	{
		getline(file,line);

		switch (compare(line, name_book, grade_book, author_book, was_put))
		{
		case -1:
			file_content += line;
			file_content += '\n';
			break;
		case 0:
			cout << "\033[91mCarte deja existenta!\033[0m";
			file_content += line;
			file_content += '\n';
			was_put = 1;
			break;
		case 1:
			file_content += name_book;
			file_content += ", clasa ";
			file_content += grade_book;
			file_content += ", autor:";
			file_content += author_book;
			file_content += ", (";
			file_content += category_book;
			file_content += ")-disponibile: ";
			file_content += number_of_books;
			file_content += '\n';
			file_content += line;
			file_content += '\n';
			was_put = 1;
			break;
		default:
			break;
		}
	}

	if (was_put)
		cout << "\033[92mCarte adaugata cu succes!\033[0m";

	if (!was_put)
	{
		file_content += name_book;
		file_content += ", clasa ";
		file_content += grade_book;
		file_content += ", autor:";
		file_content += author_book;
		file_content += ", (";
		file_content += category_book;
		file_content += ")-disponibile: ";
		file_content += number_of_books;
		cout << "\033[92mCarte adaugata cu succes!\033[0m";
	}

	if (file_content[file_content.size() - 1] == '\n')
		file_content.pop_back();

	file.close();
	
	ofstream file_w("carti.txt");
	file_w << file_content;
	file_w.close();
}

void admin::add_course()
{
	ifstream file("cursuri.txt");
	string line, name_course, professor_course, category_course, number_of_course, file_content;
	int was_put = 0;

	cout << "Numele noului curs: ";
	get_console_line(name_course);

	cout << "Numele profesorului: ";
	get_console_line(professor_course);

	cout << "Categoria: ";
	get_console_line(category_course);

	cout << "Numarul de locuri disponibile: ";
	get_console_line(number_of_course);

	while (!file.eof())
	{
		getline(file, line);

		switch (compare(line, name_course, professor_course, was_put))
		{
		case -1:
			file_content += line;
			file_content += '\n';
			break;
		case 0:
			cout << "\033[91mCurs deja existent!\033[0m";
			file_content += line;
			file_content += '\n';
			was_put = 1;
			break;
		case 1:
			file_content += name_course;
			file_content += ", profesor:";
			file_content += professor_course;
			file_content += ", (";
			file_content += category_course;
			file_content += ")-locuri: ";
			file_content += number_of_course;
			file_content += '\n';
			file_content += line;
			file_content += '\n';
			was_put = 1;
			break;
		default:
			break;
		}
	}

	if (was_put)
		cout << "\033[92mCurs adaugat cu succes!\033[0m";

	if (!was_put)
	{
		file_content += name_course;
		file_content += ", profesor:";
		file_content += professor_course;
		file_content += ", (";
		file_content += category_course;
		file_content += ")-locuri: ";
		file_content += number_of_course;
		cout << "\033[92mCurs adaugat cu succes!\033[0m";
	}

	if (file_content[file_content.size() - 1] == '\n')
		file_content.pop_back();

	file.close();
	ofstream file_w("cursuri.txt");
	file_w << file_content;
	file_w.close();
}

void admin::remove_book()
{
	ifstream file("carti.txt");
	string line, name_book, grade_book, author_book, file_content;
	bool book_exist = false;

	cout << "Numele cartii eliminate: ";
	get_console_line(name_book);

	cout << "Clasa: ";
	get_console_line(grade_book);

	cout << "Numele autorului: ";
	get_console_line(author_book);

	while (!file.eof())
	{
		getline(file, line);

		if (compare(line, name_book, grade_book, author_book))
		{
			file_content += line;
			file_content += '\n';
		}
		else
			book_exist = true;
	}

	file.close();

	file_content.pop_back();

	if (book_exist)
	{
		ofstream file_w("carti.txt");
		file_w << file_content;
		file_w.close();
		cout << "\033[92mCarte stearsa cu succes!\033[0m";
	}
	else
		cout << "\033[91mCarte deja inexistenta!\033[0m";
}

void admin::remove_course()
{
	ifstream file("cursuri.txt");
	string line, name_course, professor_course, file_content;
	bool course_exist = false;

	cout << "Numele cursului eliminate: ";
	get_console_line(name_course);

	cout << "Numele profesorului: ";
	get_console_line(professor_course);

	while (!file.eof())
	{
		getline(file, line);

		if (compare(line, name_course, professor_course))
		{
			file_content += line;
			file_content += '\n';
		}
		else
			course_exist = true;
	}

	file.close();

	file_content.pop_back();

	if (course_exist)
	{
		ofstream file_w("cursuri.txt");
		file_w << file_content;
		file_w.close();
		cout << "\033[92mCurs sters cu succes!\033[0m";
	}
	else
		cout << "\033[91mCurs deja inexistenta!\033[0m";
}

void admin::change_number_of_book()
{
	ifstream file("carti.txt");
	string line, name_book, grade_book, author_book, file_content, number;
	bool book_exist = false;

	cout << "Numele cartii pentru schimbare: ";
	get_console_line(name_book);

	cout << "Clasa: ";
	get_console_line(grade_book);

	cout << "Numele autorului: ";
	get_console_line(author_book);

	cout << "Noul numar: ";
	get_console_line(number);

	while (!file.eof())
	{
		getline(file, line);

		if (!compare(line, name_book, grade_book, author_book))
		{
			change_number(line,number);
			book_exist = true;
		}
		file_content += line;
		file_content += '\n';
	}

	file.close();

	file_content.pop_back();

	if (book_exist)
	{
		ofstream file_w("carti.txt");
		file_w << file_content;
		file_w.close();
		cout << "\033[92mCarte schimbata cu succes!\033[0m";
	}
	else
		cout << "\033[91mCarte inexistenta!\033[0m";
}

void admin::change_number_of_course()
{
	ifstream file("cursuri.txt");
	string line, name_course, professor_course, file_content, number;
	bool course_exist = false;

	cout << "Numele cursului pentru schimbare: ";
	get_console_line(name_course);

	cout << "Numele profesorului: ";
	get_console_line(professor_course);

	cout << "Noul numar: ";
	get_console_line(number);

	while (!file.eof())
	{
		getline(file, line);

		if (!compare(line, name_course, professor_course))
		{
			change_number(line, number);
			course_exist = true;
		}
		file_content += line;
		file_content += '\n';
	}

	file.close();

	file_content.pop_back();

	if (course_exist)
	{
		ofstream file_w("cursuri.txt");
		file_w << file_content;
		file_w.close();
		cout << "\033[92mCurs schimbat cu succes!\033[0m";
	}
	else
		cout << "\033[91mCurs inexistenta!\033[0m";
}

int admin::compare(string line, string name_book, string grade_book, string author_book, int was_put)
{
	int i = 0, j = 0;

	if (was_put)
		return -1;

	while (line[i] != ',')
	{
		if (line[i] != name_book[i])
			if (line[i] - name_book[i] > 0)
				return 1;
			else
				return -1;
		i++;
	}

	if (i != name_book.size())
		return -1;

	i += 8;

	if (!grade_book.compare("IX") && line[i] == 'V')
		return -1;

	if (grade_book[0] == 'V' && line[i] == 'I' && line[i + 1] == 'X')
		return 1;

	while (line[i] != ',')
	{
		if (line[i] != grade_book[j])
			if (line[i] - grade_book[j] > 0)
				return 1;
			else
				return -1;
		i++;
		j++;
	}
	
	if (j != grade_book.size())
		return -1;

	i += 8;
	j = 0;

	while (line[i] != ',')
	{
		if (line[i] != author_book[j])
			if (line[i] - author_book[j] > 0)
				return 1;
			else
				return -1;
		i++;
		j++;
	}

	if (j != author_book.size())
		return -1;

	return 0;
}

int admin::compare(string line, string name_course, string professor_course, int was_put)
{
	int i = 0, j = 0;

	if (was_put)
		return -1;

	while (line[i] != ',')
	{
		if (line[i] != name_course[i])
			if (line[i] - name_course[i] > 0)
				return 1;
			else
				return -1;
		i++;
	}

	if (i != name_course.size())
		return -1;

	i += 11;

	while (line[i] != ',')
	{
		if (line[i] != professor_course[j])
			if (line[i] - professor_course[j] > 0)
				return 1;
			else
				return -1;
		i++;
		j++;
	}

	if (j != professor_course.size())
		return -1;

	return 0;
}

int admin::compare(string line, string name_book, string grade_book, string author_book)
{
	int i = 0, j = 0;

	while (line[i] != ',')
	{
		if (line[i] != name_book[i])
			return 1;
		i++;
	}

	if (i != name_book.size())
		return 1;

	i += 8;

	while (line[i] != ',')
	{
		if (line[i] != grade_book[j])
			return 1;
		i++;
		j++;
	}

	if (j != grade_book.size())
		return 1;

	i += 8;
	j = 0;

	while (line[i] != ',')
	{
		if (line[i] != author_book[j])
			return 1;
		i++;
		j++;
	}

	if (j != author_book.size())
		return 1;

	return 0;
}

int admin::compare(string line, string name_course, string professor_course)
{
	int i = 0, j = 0;

	while (line[i] != ',')
	{
		if (line[i] != name_course[i])
			return 1;
		i++;
	}

	if (i != name_course.size())
		return 1;

	i += 11;

	while (line[i] != ',')
	{
		if (line[i] != professor_course[j])
			return 1;
		i++;
		j++;
	}

	if (j != professor_course.size())
		return 1;

	return 0;
}

void admin::change_number(string& line, string number)
{
	int i;

	i = (int)line.size() - 1;

	while (line[i] != ' ')
	{
		line.pop_back();
		i--;
	}

	line += number;
}
