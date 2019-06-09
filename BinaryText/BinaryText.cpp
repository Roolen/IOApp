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

#include "Student.hpp"

student* enter_data();
student* enter_data(size_t* size);

const char* PATH = "File.bdf";

int main()
{
	FILE *file_w, *file_r;
	// Открывает поток на запись для файла.
	fopen_s(&file_w, PATH, "wb+,ccs=UTF-8");

	// Возвращает 1, если чтение файла не удалось.
	if (file_w == nullptr) {
		std::cout << "Read file is failure";
		return 1;
	}

	// Пользователь вводит количество студентов.
	int32_t tmpSize = 0;
	std::cout << "Enter count students:";
	std::cin >> tmpSize;
	// Если число пользователей меньше нуля - ошибка.
	if (tmpSize <= 0) {
		std::cout << "Entered of number students is invalid!";
		return 2;
	}
	size_t size = tmpSize;
	// Заполняем массив информацией о студентах.
	student* students = enter_data();

	// Записываем данные о студентах в двоичный файл.
	fwrite(students, sizeof(student), size, file_w);

	delete[] students;

	fclose(file_w);
	// Открываем поток на чтение для файла.
	fopen_s(&file_r, PATH, "rb,ccs=UTF-8");

	// Считываем данные о студентах, из двоичного файла.
	std::vector<student> readStudents(size);
	if (file_r != nullptr) {
		for (size_t i = 0; i < size; i++)
		{
			fread(&readStudents[i], sizeof(student), 1, file_r);
		}
	}

	// Выводим данные о студентах на консоль.
	for (size_t i = 0; i < readStudents.size(); i++)
	{
		std::cout << readStudents[i].name << " " << (int)readStudents[i].age << " " 
			<< (char)readStudents[i].gender << " " << (int)readStudents[i].course
			<< std::endl;
	}

	std::cout << "Group with more procent men: " << get_group_more_gender(readStudents, 'M') << std::endl;
	std::cout << "Most popular name of men: " << get_most_popular_name(readStudents, 'M') << std::endl;
	std::cout << "Most popular name of girl: " << get_most_popular_name(readStudents, 'F') << std::endl;

	_fcloseall();
}

// For DEBUG.
student* enter_data() {
	// FREE MEMORY AFTER USE
	student* students = new student[7];

	if (students != nullptr)
	{
		*students = { "Mask", "Ilon", 'M', 20, 3 };
		*(students + 1) = { "Andrei", "Andreiv",'M', 19, 1 };
		*(students + 2) = { "Andrei", "Gruchevski", 'M', 23, 2 };
		*(students + 3) = { "Anna", "Zaparoshskuya", 'F', 17, 1 };
		*(students + 4) = { "Ulia", "Kalmukova", 'F', 21, 4 };
		*(students + 5) = { "Radion", "Raskolnikov", 'M', 20, 3 };
		*(students + 6) = { "Ulia", "Terechkova", 'F', 24, 3 };
	}

	return students;
}

student* enter_data(size_t* size) {
	student *students = new student[*size];

	wchar_t gender = ' ';
	uint16_t age, course;
	for (size_t i = 0; i < *size; i++)
	{
		char* name = new char[12];
		char* secondName = new char[12];

		std::cout << "Student " << i+1 << std::endl
			<< "Enter name and second name of student:";
		std::cin >> name >> secondName;
		std::cout << "Enter student gender(M or F in uppercase): ";
		std::cin.get();
		std::wcin >> gender;
		std::cout << "Enter student age(16-35) and course(1-5): ";
		std::cin >> age >> course;

		*(students + i) = {name, secondName, (wchar_t)gender, (uint8_t)age, (uint8_t)course};
	}

	return students;
}