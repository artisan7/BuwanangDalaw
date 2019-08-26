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
	float getFee();
	std::string getType();
	std::string getStatus();

	// static functions
	static Room* search(std::vector<Room>& rooms);
	static Room* search(std::vector<Room>& rooms, std::string& roomNum);
	static void add(std::vector<Room>& rooms, Room& r);

	static void readFile(std::vector<Room>& rooms, std::string filepath);
	static void writeFile(std::vector<Room>& rooms, std::string filepath);

	// other functions
	void displayInfo();
};
