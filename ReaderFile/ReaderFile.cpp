//Во входном файле записана следующая информация : ФИО респондента,
//город  в  котором  он  проживает, употребляет  или  не  употребляет
//наркотики(1 - употребляет, 0 - не  употребляет).Определить  города  с
//максимальной тенденцией к употреблению наркотиков


#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <string>

#include "respondent.hpp"

using addictionCityMap = std::unordered_map<std::string, uint32_t>;

respondent* enter_data();
addictionCityMap get_addicton_in_city(std::vector<respondent> respondents);
std::string* get_city_more_addiction(addictionCityMap cities);

const char* PATH = "file.bdf";

int main()
{
	FILE* file_w, *file_r;
	fopen_s(&file_w, PATH, "wb+,ccs=UTF-8");

	if (file_w == nullptr) {
		std::cout << "Read file is failure!\n";
		return 1;
	}


	int32_t tmpSize = 0;
	std::cout << "Enter count respondents:";
	std::cin >> tmpSize;

	if (tmpSize <= 0) {
		std::cout << "Entered of number respondents is invalid!";
		return 2;
	}
	size_t size = tmpSize;
	respondent* respondents = enter_data();

	fwrite(respondents, sizeof(respondent), size, file_w);

	delete[] respondents;

	fclose(file_w);

	fopen_s(&file_r, PATH, "rb,ccs=UTF-8");

	if (file_r == nullptr) {
		std::cout << "Read file is failure";
		return 1;
	}

	std::vector<respondent> readRespondents(size);
	if (file_r != nullptr) {
		for (size_t i = 0; i < size; i++)
		{
			fread(&readRespondents[i], sizeof(respondent), 1, file_r);
		}
	}

	for (size_t i = 0; i < readRespondents.size(); i++)
	{
		std::cout << readRespondents[i].name << "\t\t" << readRespondents[i].secondName << "\t\t"
			<< readRespondents[i].residence << "\t" << readRespondents[i].addiction
			<< std::endl;
	}
	std::cout << "\n";

	addictionCityMap cities = get_addicton_in_city(readRespondents);
	
	auto citiesMoreAddiction = get_city_more_addiction(cities);

	std::cout << "Three cities with the highest drug use trends:\n";
	for (size_t i = 0; i < 3; i++)
	{
		std::cout << citiesMoreAddiction[i] << "\n";
	}

	fclose(file_r);
}


respondent* enter_data() {
	// FREE MEMORY AFTER USE
	respondent* respondents = new respondent[7]; 

	if (respondents != nullptr)	
	{
		*respondents = { "Mask", "Ilon", "Magnitogorsk", false};
		*(respondents + 1) = { "Andrei", "Andreiv", "Magnitogorsk", true};
		*(respondents + 2) = { "Andrei", "Gruchevski", "Moscow", true};
		*(respondents + 3) = { "Anna", "Zaparoshskuya", "Moscow", true};
		*(respondents + 4) = { "Ulia", "Kalmukova", "Sochi", false};
		*(respondents + 5) = { "Radion", "Raskolnikov", "Orsk", true};
		*(respondents + 6) = { "Ulia", "Terechkova", "Sochi", false};
	}

	return respondents;
}

addictionCityMap get_addicton_in_city(std::vector<respondent> respondents) {
	addictionCityMap cities;

	for (size_t i = 0; i < respondents.size(); i++)
	{
		if (respondents[i].addiction == 0) continue;

		if (cities.count(respondents[i].residence))
			cities.at(respondents[i].residence)++;
		else {
			auto cityMake = std::make_pair(respondents[i].residence, 1);
			cities.insert(cityMake);
		}
	}

	return cities;
}

std::string* get_city_more_addiction(addictionCityMap cities) {
	std::string* cit = new std::string[3];

	for (size_t i = 0; i < 3; i++)
	{
		for (auto city : cities) {
			if (cit[i] == "")
				cit[i] = city.first;

			else if (cities[cit[i]] < city.second)
				cit[i] = city.first;
		}
		cities.erase(cit[i]);
	}

	return cit;
}