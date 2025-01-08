#include "course.h"

void course::clean()
{
	name.clear();
	professor.clear();
	category.clear();
}

void course::set_course(string& input)
{
	int i = 0;

	while (input.at(i) != ',')
	{
		name.push_back(input.at(i));
		i++;
	}

	i += 11;

	while (input.at(i) != ',')
	{
		professor.push_back(input.at(i));
		i++;
	}

	i += 3;

	while (input.at(i) != ')')
	{
		category.push_back(input.at(i));
		i++;
	}
}

void course::info()
{
	cout << name << ", profesor:" << professor << ", (" << category << ")\n";
}

string course::get_name()
{
	return name;
}

string course::get_professor()
{
	return professor;
}

string course::get_category()
{
	return category;
}