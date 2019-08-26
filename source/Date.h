#pragma once

#include <string>

class Date {
private:
	int month, day, year;
public:
	// constructors
	Date();
	Date(std::string dateString);
	Date(int year, int month = 0, int day = 0);

	// to string
	std::string toString();
	std::string toSlashFormat();

	// getters
	std::string getMonth();
	int getMonthNum();
	int getDay();
	int getYear();

	// prompts
	static int monthPrompt();
	static int dayPrompt(int month);
	static int yearPrompt();
};
