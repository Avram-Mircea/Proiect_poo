#include "student.h"

extern char trash;

student::student() 
{
	name = "";
	password = "";
	position = "";
	min_grade = "Z";

	for (int i = 0; i < 26; i++)
		interest_in_subjects[i] = 0;
}

student::student(user& _user)
{
	ifstream file(_user.get_name() + ".txt");
	string line;
	book _book;
	course _course;

	name = _user.get_name();
	password = _user.get_password();
	position = "student";
	min_grade = "Z";

	for (int i = 0; i < 26; i++)
		interest_in_subjects[i] = 0;

	getline(file, line); //read password
	getline(file, line); //read position
	getline(file, line); //read '\n'
	getline(file, line); //read "Carti:"
	getline(file, line); //read first book

	while (line.compare("")) //read all student books
	{
		_book.set_book(line);
		if (_book.get_grade().compare("IX"))
		{
			if(min_grade.compare(_book.get_grade()) == 1)
				min_grade = _book.get_grade();
		}
		else
		{
			if (min_grade != "V" && min_grade != "VI" && min_grade != "VII" && min_grade != "VIII")
				if(min_grade.compare(_book.get_grade()) == 1)
					min_grade = _book.get_grade();
		}
		interest_in_subjects[_book.get_category().at(0) - 'a']++;
		books.push_back(_book);
		_book.clean();
		getline(file, line);
	}

	getline(file, line); //read "Cursui:"

	while (!file.eof()) //read all student courses
	{
		getline(file, line);
		_course.set_course(line);
		interest_in_subjects[_course.get_category().at(0) - 'a']++;
		courses.push_back(_course);
		_course.clean();
	}

	file.close();
	recommend();
}

void student::show()
{
	int i;
	cout << "Numele contului: " << name << endl;
	cout << "Parola cont: " << password << endl;
	cout << "Functia: " << position << endl;

	cout << "\nCarti imprumutate(" << books.size() << "):\n";

	for (i = 0; i < books.size(); i++)
	{
		books[i].info();
	}

	cout << "\nInscrieri la cursuri(" << courses.size() << "):\n";

	for (i = 0; i < courses.size(); i++)
	{
		courses[i].info();
	}
}

void student::recommend()
{
	int i, most_interesting_subject, max_interest = 0;

	for (i = 0; i < 26; i++)
		if (max_interest < interest_in_subjects[i])
		{
			most_interesting_subject = i;
			max_interest = interest_in_subjects[i];
		}
	
	if (max_interest)
	{
		ifstream file("carti.txt");
		string line, object_name, book_grade, object_holder;
		book _book;
		course _course;
		int found = 0;

		while (!found && !file.eof())
		{
			getline(file, line);
			_book.clean();
			_book.set_book(line);

			if ((_book.get_category().at(0) == (most_interesting_subject + 'a')) && !min_grade.compare(_book.get_grade()))
				if (line[line.size() - 1] != '0' || line[line.size() - 2] != ' ')
				{
					object_name = _book.get_name();
					book_grade = _book.get_grade();
					object_holder = _book.get_author();
					if (!book_is_borrow(object_name, book_grade, object_holder))
						found = 1;
				}
		}

		file.close();

		if (found)
		{
			cout << "Iti recomandan cartea:\n";
			_book.info();
		}

		if (!at_school())
		{
			found = 0;
			file.open("cursuri.txt");

			while (!found && !file.eof())
			{
				getline(file, line);
				_course.clean();
				_course.set_course(line);

				if ((_course.get_category().at(0) == (most_interesting_subject + 'a')))
					if (line[line.size() - 1] != '0' || line[line.size() - 2] != ' ')
					{
						object_name = _course.get_name();
						object_holder = _course.get_professor();
						if (!course_is_book(object_name,object_holder))
							found = 1;
					}
			}

			file.close();

			if (found)
			{
				cout << "Iti recomandan cursul:\n";
				_course.info();
			}
		}
	}
	trash = getchar();
}

void student::borrow_a_book()
{
	string file_line, file_content, wanted_book, wanted_grade, wanted_author;
	ifstream file("carti.txt");
	book _book;
	bool end_file = false, found = false;
	int object_statement = 0;
	char c;

	cout << "Ce carte doriti sa imprumutati: ";
	get_console_line(wanted_book);

	cout << "Ce clasa sa fie cartea: ";
	get_console_line(wanted_grade);

	cout << "Preferinte de autor?[D/N]\n";
	c = getchar();
	trash = getchar();
	if (c == 'D')
	{
		cout << "Numele autorului: ";
		get_console_line(wanted_author);
	}

	if (book_is_borrow(wanted_book, wanted_grade, wanted_author))
	{
		wanted_book.clear();
		object_statement = 3;
	}

	while (!end_file && !wanted_book.empty()) //!wanted_book.empty() to assure we have a valid string
	{
		getline(file, file_line);
		_book.clean();
		_book.set_book(file_line);

		if (!wanted_book.compare(_book.get_name()) && !wanted_grade.compare(_book.get_grade()) && !found) //if current line match name and grade and no other book was borrowed
		{
			if (!wanted_author.empty()) //wanted author
			{
				if (!wanted_author.compare(_book.get_author())) //current line author match
				{
					if (file_line[file_line.length() - 1] == '0' && file_line[file_line.length() - 2] == ' ') //the wanted object is on 0
					{
						object_statement = 1;
					}
					else
					{
						object_statement = 2;
						found = true;
						decrease_object(file_line);
						books.push_back(_book);
					}
				}
			}
			else //no wanted author
			{
				if (file_line[file_line.length() - 1] == '0' && file_line[file_line.length() - 2] == ' ') //the wanted object is on 0
				{
					object_statement = 1;
				}
				else
				{
					object_statement = 2;
					found = true;
					decrease_object(file_line);
					books.push_back(_book);
				}
			}
		}

		if (file_line.compare("\n"))
		{
			file_content += file_line;

			if (!file.eof()) //see if there are any more lines in the file to don't put extra enters
				file_content += '\n';
		}

		end_file = file.eof();
	}

	file.close();

	switch (object_statement)
	{
	case 0:
		cout << "\033[91mNu exista cartea!\033[0m";
		break;
	case 1:
		cout << "\033[91mNu se poate aloca cartea!\nNumarul cartilor este 0!\033[0m";
		break;
	case 2:
		cout << "\033[92mCarte alocata cu succes!\033[0m";
		break;
	case 3:
		cout << "\033[91mCartea este deja imprumutata!\033[0m";
	}

	if (!wanted_book.empty()) //if empty means no changes needed
	{
		ofstream file_w("carti.txt");
		file_w << file_content;
		file_w.close();
	}
}

void student::book_a_course()
{
	string file_line, file_content, wanted_course, wanted_professor;
	ifstream file("cursuri.txt");
	course _course;
	bool end_file = false, found = false;
	int object_statement = 0;
	char c;

	cout << "La ce curs doriti sa va inscrieti: ";
	get_console_line(wanted_course);

	cout << "Preferinte de profesor?[D/N]\n";
	c = getchar();
	trash = getchar();
	if (c == 'D')
	{
		cout << "Numele profesorului: ";
		get_console_line(wanted_professor);
	}

	if (course_is_book(wanted_course, wanted_professor))
	{
		wanted_course.clear();
		object_statement = 3;
	}

	while (!end_file && !wanted_course.empty()) //!wanted_course.empty() to assure we have a valid string
	{
		getline(file, file_line);
		_course.clean();
		_course.set_course(file_line);

		if (!wanted_course.compare(_course.get_name()) && !found) //if current line match name and no other course was book
		{
			if (!wanted_professor.empty()) //wanted professor
			{
				if (!wanted_professor.compare(_course.get_professor())) //current line professor match
				{
					if (file_line[file_line.length() - 1] == '0' && file_line[file_line.length() - 2] == ' ') //the wanted object is on 0
					{
						object_statement = 1;
					}
					else
					{
						object_statement = 2;
						found = true;
						decrease_object(file_line);
						courses.push_back(_course);
					}
				}
			}
			else //no wanted professor
			{
				if (file_line[file_line.length() - 1] == '0' && file_line[file_line.length() - 2] == ' ') //the wanted object is on 0
				{
					object_statement = 1;
				}
				else
				{
					object_statement = 2;
					found = true;
					decrease_object(file_line);
					courses.push_back(_course);
				}
			}
		}

		if (file_line.compare("\n"))
		{
			file_content += file_line;

			if (!file.eof()) // see if there are any more lines in the file to don't put extra enters
				file_content += '\n';
		}

		end_file = file.eof();
	}

	file.close();

	switch (object_statement)
	{
	case 0:
		cout << "\033[91mNu exista cursul!\033[0m";
		break;
	case 1:
		cout << "\033[91mNu se poate aloca locul!\nNumarul locurilor este 0!\033[0m";
		break;
	case 2:
		cout << "\033[92mLoc alocat cu succes!\033[0m";
		break;
	case 3:
		cout << "\033[91mSunteti inscrisi la curs!\033[0m";
		break;
	}

	if (!wanted_course.empty()) //if empty means no changes needed
	{
		ofstream file_w("cursuri.txt");
		file_w << file_content;
		file_w.close();
	}
}

void student::return_a_book()
{
	string file_line, file_content, wanted_book, wanted_grade, wanted_author;
	ifstream file("carti.txt");
	book _book;
	bool end_file = false;
	int i, object_statement = 0;

	cout << "Ce carte doriti sa returnati: ";
	get_console_line(wanted_book);

	cout << "Ce clasa este cartea: ";
	get_console_line(wanted_grade);

	cout << "Numele autorului: ";
	get_console_line(wanted_author);

	for (i = 0; i < books.size(); i++)
	{
		if (!wanted_book.compare(books[i].get_name()) && !wanted_grade.compare(books[i].get_grade()) && !wanted_author.compare(books[i].get_author())) //if student have the book
		{
			books.erase(books.begin() + i);
			object_statement = 1;
		}
	}

	while (!end_file && object_statement)
	{
		getline(file, file_line);
		_book.clean();
		_book.set_book(file_line);

		if (!wanted_book.compare(_book.get_name()) && !wanted_grade.compare(_book.get_grade()) && !wanted_author.compare(_book.get_author())) //if current line is the return book
			increase_object(file_line);

		if (file_line.compare("\n"))
		{
			file_content += file_line;

			if (!file.eof()) // see if there are any more lines in the file to don't put extra enters
				file_content += '\n';
		}

		end_file = file.eof();
	}

	file.close();

	switch (object_statement)
	{
	case 0:
		cout << "\033[91mNu ati imprumutat aceasta cartea!\033[0m";
		break;
	case 1:
		cout << "\033[92mCarte returnata cu succes!\033[0m";
		break;
	}

	if (object_statement) //if 0 means no changes needed
	{
		ofstream file_w("carti.txt");
		file_w << file_content;
		file_w.close();
	}
}

void student::release_a_course()
{
	string file_line, file_content, wanted_course, wanted_professor;
	ifstream file("cursuri.txt");
	course _course;
	bool end_file = false;
	int i, object_statement = 0;

	cout << "La ce curs doriti sa eliberati locul: ";
	get_console_line(wanted_course);

	cout << "Numele profesorului: ";
	get_console_line(wanted_professor);

	for (i = 0; i < courses.size(); i++)
	{
		if (!wanted_course.compare(courses[i].get_name()) && !wanted_professor.compare(courses[i].get_professor())) //if student have the course
		{
			courses.erase(courses.begin() + i);
			object_statement = 1;
		}
	}

	while (!end_file && object_statement)
	{
		getline(file, file_line);
		_course.clean();
		_course.set_course(file_line);

		if (!wanted_course.compare(_course.get_name()) && !wanted_professor.compare(_course.get_professor())) //if current line is the release course
			increase_object(file_line);

		if (file_line.compare("\n"))
		{
			file_content += file_line;

			if (!file.eof()) // see if there are any more lines in the file to don't put extra enters
				file_content += '\n';
		}

		end_file = file.eof();
	}

	file.close();

	switch (object_statement)
	{
	case 0:
		cout << "\033[91mNu sunteti inscrisi la curs!\033[0m";
		break;
	case 1:
		cout << "\033[92mLoc eliberat cu succes!\033[0m";
		break;
	}

	if (object_statement) //if 0 means no changes needed
	{
		ofstream file_w("cursuri.txt");
		file_w << file_content;
		file_w.close();
	}
}

int student::size_books()
{
	return (int)books.size();
}

int student::size_courses()
{
	return (int)courses.size();
}

bool student::at_school()
{
	if (min_grade != "I" && min_grade != "II" && min_grade != "III" && min_grade != "IV" && min_grade != "V" && min_grade != "VI" && min_grade != "VII" && min_grade != "VIII")
		return false;
	else
		return true;
}

void student::save_info_student()
{
	int i;
	ofstream file(name + ".txt");
	file << password << '\n' << position << '\n' << "\nCarti:\n";

	for (i = 0; i < books.size(); i++)
	{
		file << books[i].get_name() << ", clasa " << books[i].get_grade() << ", autor:" << books[i].get_author() << ", (" << books[i].get_category() << ")\n";
	}

	file << "\nCursuriu:";

	for (i = 0; i < courses.size(); i++)
	{
		file << '\n' << courses[i].get_name() << ", profesor:" << courses[i].get_professor() << ", (" << courses[i].get_category() << ')';
	}

	file.close();
}

void student::decrease_object(string& line)
{
	int length, i;
	length = (int)line.length();

	if (line.at(length - 1) != '0') //the number of object don't end with 0 eg: 1234 becomes 1233
	{
		line.at(length - 1)--;
	}
	else
	{
		for (i = 1; line.at(length - i) == '0'; i++)
			line[length - i] = '9';

		if (line[length - i - 1] != ' ') //next digit after zeros eg: 1200 becomes 1199 or 1100 becomes 1099
			line[length - i]--;
		else if (line[length - i] != '1') //next digit after zeros is different from one and there is noanother digit after it eg: 600 becomes 599
			line[length - i]--;
		else //next digit after zeros is one and there is noanother digit after it eg: 100 becomes 99
		{
			line[length - i] = '9';
			line.pop_back();
		}
	}
}

void student::increase_object(string& line)
{
	int length, i;
	length = (int)line.length();

	if (line.at(length - 1) != '9') //the number of object don't end with 9 eg: 1234 becomes 1235
	{
		line.at(length - 1)++;
	}
	else
	{
		for (i = 1; line.at(length - i) == '9'; i++)
			line[length - i] = '0';

		if(line[length - i] != ' ') //next digit after nines eg: 1199 becomes 1200
			line[length - i]++;
		else //next char after nines is space eg: 99 becomes 100
		{
			line[length  - i + 1] = '1';
			line.push_back('0');
		}
	}
}

int student::book_is_borrow(string& book_name, string& book_grade, string& book_author)
{
	int i;

	for (i = 0; i < books.size(); i++)
	{
		if (book_author.empty()) //no author wanted
		{
			if (!book_name.compare(books[i].get_name()) && !book_grade.compare(books[i].get_grade()))
				return 1;
		}
		else //author wanted
		{
			if (!book_name.compare(books[i].get_name()) && !book_grade.compare(books[i].get_grade()) && !book_author.compare(books[i].get_author()))
				return 1;
		}
	}

	return 0;
}

int student::course_is_book(string& course_name, string& course_professor)
{
	int i;

	for (i = 0; i < courses.size(); i++)
	{
		if (course_professor.empty()) //no professor wanted
		{
			if (!course_name.compare(courses[i].get_name()))
				return 1;
		}
		else //professor wanted
		{
			if (!course_name.compare(courses[i].get_name()) && !course_professor.compare(courses[i].get_professor()))
				return 1;
		}
	}

	return 0;
}
