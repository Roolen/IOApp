//Во  входном  файле  записана  следующая  информация  о  каждом  из  2000
//студентов  некоторого  вуза : фамилия, имя, отчество, пол, возраст, курс.
//Причем в фамилии, имени и отчестве – не более 12 букв, пол указывается
//буквами  М  и  Ж, возраст  –  целое  от  16  до  35, курс  –  целое  от  1  до  5.
//Написать  программу, которая  вводит  эту  информацию  и  печатает
//следующие  данные : номер  курса, на  котором  наибольший  процент
//мужчин; самые распространенные мужское и женское имена


#include <stdio.h>
#include <iostream>
#include <vector>

#include "BinaryText.h"

student* EnterData(size_t* size);

const char* PATH = "File.bdf";

int main()
{
	FILE* file;
	// Открывает поток для файла.
	fopen_s(&file, PATH, "wb+,ccs=UTF-8");

	// Возвращает 1, если чтение файла не удалось.
	if (file == nullptr) return 1;

	size_t size = 5;
	student* students = EnterData(&size);

	for (size_t i = 0; i < size; i++)
	{
		fwrite(&students[i], sizeof(student), 1, file);
	}

	fseek(file, 0, SEEK_SET);

	std::vector<student> readStudents;
	readStudents.resize(size);
	for (size_t i = 0; i < size; i++)
	{
		fread(&readStudents[i], sizeof(student), 1, file);
	}

	for (size_t i = 0; i < readStudents.size(); i++)
	{
		std::cout << readStudents[i].name << " " << (int)readStudents[i].age << " " 
			<< (char)readStudents[i].gender << " " << (int)readStudents[i].course
			<< std::endl;
	}

	fclose(file);
}

student* EnterData(size_t* size) {
	// FREE MEMORY AFTER USE
	student* students = new student[5];
	*size = 5;

	if (students != nullptr)
	{
	*students = { "Mask", "Ilon", 'M', 20, 3 };
	*(students + 1) = { "Andrei", "Andreiv",'M', 19, 1 };
	*(students + 2) = { "Michail", "Gruchevski", 'M', 23, 2 };
	*(students + 3) = { "Anna", "Zaparoshskuya", 'F', 17, 1 };
	*(students + 4) = { "Ulia", "Kalmukova", 'F', 21, 4 };
	}

	return students;
}
