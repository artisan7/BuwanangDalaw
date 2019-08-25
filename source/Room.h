#pragma once

#include <string>
#include <vector>

class Room {
private:
	std::string number;
	std::string houseCode;
	std::string condition;
	short int type;
	float rentFee;
	bool status;

public:
	// constructor
	Room(std::string number, std::string houseCode, short int type, std::string condition, float rentFee, bool status);

	// getters
	std::string getNumber();
	std::string getHouseCode();
	std::string getType();
	std::string getStatus();

	// static functions
	static Room* search(std::vector<Room>& rooms);
	static Room* search(std::vector<Room>& rooms, std::string& roomNum);
	static void add(std::vector<Room>& rooms, Room& r);

	// other functions
	void displayInfo();
};
