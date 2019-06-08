//Во  входном  файле  записана  следующая  информация  о  каждом  из  2000
//студентов  некоторого  вуза : фамилия, имя, отчество, пол, возраст, курс.
//Причем в фамилии, имени и отчестве – не более 12 букв, пол указывается
//буквами  М  и  Ж, возраст  –  целое  от  16  до  35, курс  –  целое  от  1  до  5.
//Написать  программу, которая  вводит  эту  информацию  и  печатает
//следующие  данные : номер  курса, на  котором  наибольший  процент
//мужчин; самые распространенные мужское и женское имена

#ifdef _DEBUG
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#endif

#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "BinaryText.hpp"

student* enter_data(size_t* size);
uint16_t get_group_more_man(std::vector<student>);
std::string get_most_popular_name(std::vector<student>, wchar_t);
typedef std::unordered_map<std::string, uint16_t> MapNames;

const char* PATH = "File.bdf";

int main()
{
	FILE *file_w, *file_r;
	// Открывает поток для файла.
	fopen_s(&file_w, PATH, "wb+,ccs=UTF-8");

	// Возвращает 1, если чтение файла не удалось.
	if (file_w == nullptr) return 1;

	size_t size = 7;
	student* students = enter_data(&size);

	for (size_t i = 0; i < size; i++)
	{
		fwrite(&students[i], sizeof(student), 1, file_w);
	}
	delete[] students;

	fclose(file_w);
	fopen_s(&file_r, PATH, "rb,ccs=UTF-8");

	std::vector<student> readStudents(size);
	if (file_r != nullptr) {
		for (size_t i = 0; i < size; i++)
		{
			fread(&readStudents[i], sizeof(student), 1, file_r);
		}
	}

	for (size_t i = 0; i < readStudents.size(); i++)
	{
		std::cout << readStudents[i].name << " " << (int)readStudents[i].age << " " 
			<< (char)readStudents[i].gender << " " << (int)readStudents[i].course
			<< std::endl;
	}

	uint16_t groupWithMoreMan = get_group_more_man(readStudents);
	std::cout << "Group with more procent men: " << groupWithMoreMan << std::endl;
	std::cout << "Most popular name of men: " << get_most_popular_name(readStudents, 'M') << std::endl;
	std::cout << "Most popular name of girl: " << get_most_popular_name(readStudents, 'F') << std::endl;


	_fcloseall();
}

student* enter_data(size_t* size) {
	// FREE MEMORY AFTER USE
	student* students = new student[*size];

	if (students != nullptr)
	{
	*students = { "Mask", "Ilon", 'M', 20, 3 };
	*(students + 1) = { "Andrei", "Andreiv",'M', 19, 1 };
	*(students + 2) = { "Andrei", "Gruchevski", 'M', 23, 2 };
	*(students + 3) = { "Anna", "Zaparoshskuya", 'F', 17, 1 };
	*(students + 4) = { "Ulia", "Kalmukova", 'F', 21, 4 };
	*(students + 5) = { "Radion", "Raskolnikov", 'M', 20, 2 };
	*(students + 6) = { "Ulia", "Terechkova", 'F', 24, 3 };
	}

	return students;
}

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
