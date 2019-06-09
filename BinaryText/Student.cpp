#include <stdint.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "Student.hpp"

typedef std::unordered_map<std::string, uint16_t> MapNames;


uint16_t get_group_more_man(std::vector<student> students) {
	int group[4]{};
	for (size_t i = 0; i < students.size(); i++)
	{
		if (students[i].gender == 'M')
			group[students[i].course]++;
	}

	int moreGroup = 0;
	for (size_t i = 0; i < 5; i++)
	{
		if (moreGroup < group[i])
			moreGroup = group[i];
	}

	return moreGroup;
}

std::string get_most_popular_name(std::vector<student> students, wchar_t gender) {
	MapNames names;

	for (size_t i = 0; i < students.size(); i++)
	{
		if (students[i].gender != gender) continue;

		if (names.count(students[i].name))
			names.at(students[i].name)++;
		else
		{
			std::pair<std::string, uint16_t> name = std::make_pair(students[i].name, 1);
			names.insert(name);
		}
	}

	std::string popularName;
	for (auto name : names) {
		if (name.second > names[popularName])
			popularName = name.first;
	}

	return popularName;
}