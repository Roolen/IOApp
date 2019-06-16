#include <stdint.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "Student.hpp"

typedef std::unordered_map<std::string, uint16_t> MapNames;

uint16_t get_group_more_gender(std::vector<student> students, wchar_t gender) {
	if (gender != 'M' && gender != 'F') return 0;
	if (students.size() == 0) return 0;

	int numberGenders[5]{};	// Содержит количество студентов определённого пола, по группам.
	int numberAllGenders[5]{};	// Содержит общее количество студентов по группам.

	// Расчитывает количество человек с заданным полом в группах.
	// И общее количество студентов в группах.
	for (size_t i = 0; i < students.size(); i++)
	{
		numberAllGenders[students[i].course - 1]++;

		if (students[i].gender == gender)
			numberGenders[students[i].course - 1]++;
	}

	// Поиск группы с наибольшим процентом студентов заданного пола.
	double max = 0.0;
	int indexMoreGroup = 0;
	for (size_t i = 0; i < 5; i++)
	{
		if (numberAllGenders == 0 || numberGenders[i] == 0) continue;
		if (max < (numberGenders[i] / numberAllGenders[i])) {
			indexMoreGroup = i+1;
			max = numberGenders[i] / numberAllGenders[i];
		}
	}

	return indexMoreGroup;
}


std::string get_most_popular_name(std::vector<student> students, wchar_t gender) {
	if (gender != 'M' && gender != 'F') return "Invalid gender";
	if (students.size() == 0) return "Invalid count students";

	MapNames names; // <key=имя, value=число_упоминаний>

	// Заполнение словаря значениями.
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

	// Поиск самого популярного имени.
	std::string popularName;
	for (auto name : names) {
		if (name.second > names[popularName])
			popularName = name.first;
	}

	return popularName;
}
