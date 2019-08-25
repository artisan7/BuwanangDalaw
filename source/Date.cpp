#include "Date.h"

#include <iostream>
#include <sstream>

//CONSTRUCTORS
Date::Date() {
	int month = monthPrompt();
	int day = dayPrompt(month);
	int year = yearPrompt();
}

Date::Date(std::string dateString) {
	std::stringstream ss;
	ss << dateString;

	char delim;
	ss >> month >> delim >> day >> delim >> year;
}

// TO STRING
std::string Date::toString() {
	std::stringstream ss;
	ss << getMonth() << ' ' << day << ", " << year;
	return ss.str();
}

// GETTERS
std::string Date::getMonth() {
	switch (month) {
	case 1:		return "January";
	case 2:		return "February";
	case 3:		return "March";
	case 4:		return "April";
	case 5:		return "May";
	case 6:		return "June";
	case 7:		return "July";
	case 8:		return "August";
	case 9:		return "September";
	case 10:	return "October";
	case 11:	return "November";
	case 12:	return "December";
	default:	return ".";
	}
}

// PROMPTS
int Date::monthPrompt() {
	int month = 0;

	do {
		std::cout << "Month (1-12): ";
		std::cin >> month;
	} while (month < 1 || month > 12);

	return month;
}

int Date::dayPrompt(int month) {
	int maxDay = 31;
	switch (month) {
	case 2: maxDay--;
	case 4:
	case 6:
	case 9:
	case 11: maxDay--;
	default: break;
	}

	int day = 0;
	do {
		std::cout << "Day (1-" << maxDay << "): ";
		std::cin >> day;
	} while (day < 1 || day > maxDay);

	return day;
}

int Date::yearPrompt() {
	int year = 0;
	do {
		std::cout << "Year (1960-2019): ";
		std::cin >> year;
	} while (year < 1960 || year > 2019);

	return year;
}

