#pragma once

#include <string>

class Date {
private:
	int month, day, year;
public:
	Date();
	Date(std::string dateString);
	std::string toString();
	std::string getMonth();

	// prompts
	static int monthPrompt();
	static int dayPrompt(int month);
	static int yearPrompt();
};
