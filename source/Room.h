#pragma once

#include <string>

class Room {
private:
	std::string number;
	std::string condition;
	short int type;
	float rentFee;
	bool status;

public:
	// constructor
	Room(std::string number, short int type, std::string condition, float rentFee, bool status);

	// setters

	// getters
	std::string getType();
	std::string getStatus();

	// other functions
	void displayInfo();
};
