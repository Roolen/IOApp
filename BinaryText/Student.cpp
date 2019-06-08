#include <stdint.h>
#include <string>

#pragma pack(push, 1)
struct student {
	const char* name;
	const char* secondName;
	wchar_t gender;
	uint8_t age;
	uint8_t course;
};
#pragma pack(pop)