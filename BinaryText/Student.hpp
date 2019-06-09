#pragma once

#pragma pack(push, 1)
struct student {
	const char* name;
	const char* secondName;
	wchar_t gender;
	uint8_t age;
	uint8_t course;
};
#pragma pack(pop)

student* enter_data(size_t* size);
uint16_t get_group_more_man(std::vector<student> students);
std::string get_most_popular_name(std::vector<student> students, wchar_t gender);