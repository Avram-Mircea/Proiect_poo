#include "book.h"

void book::clean()
{
	name = "";
	grade = "";
	author = "";
	category = "";
}

void book::set_book(string& input)
{
	int i = 0;

	while (input.at(i) != ',')
	{
		name.push_back(input.at(i));
		i++;
	}

	i+=8;

	while (input.at(i) != ',')
	{
		grade.push_back(input.at(i));
		i++;
	}

	i+=8;

	while (input.at(i) != ',')
	{
		author.push_back(input.at(i));
		i++;
	}

	i+=3;

	while (input.at(i) != ')')
	{
		category.push_back(input.at(i));
		i++;
	}
}

void book::info()
{
	cout << name << ", clasa " << grade << ", autor:" << author << ", (" << category << ")\n";
}

string book::get_name()
{ 
	return name;
}

string book::get_grade()
{
	return grade;
}

string book::get_author()
{
	return author;
}

string book::get_category()
{
	return category;
}