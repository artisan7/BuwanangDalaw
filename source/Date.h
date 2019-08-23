#pragma once

#include <string>

class Date {
private:
	int month, day, year;
public:
	Date(std::string dateString);
	std::string toString();
	std::string getMonth();
};
