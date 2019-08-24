#pragma once

#include <string>
#include <vector>

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

	// getters
	std::string getType();
	std::string getStatus();

	// static functions
	static Room* search(std::vector<Room>& rooms, std::string& roomNum);

	// other functions
	void displayInfo();
};
