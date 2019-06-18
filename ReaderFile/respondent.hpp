#pragma once

struct respondent {
	const char* name;
	const char* secondName;
	const char* residence;
	bool addiction;

	void set_residence(const char* newRes) {
		delete residence;
		residence = newRes;
	}
};