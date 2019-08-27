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
	bool status;		// (0) available (1) occupied

	static std::vector<Room> masterList;

public:
	// constructor
	Room(std::string number, std::string houseCode, short int type, std::string condition, float rentFee, bool status);

	// getters
	std::string getNumber();
	std::string getHouseCode();
	float getFee();
	std::string getType();
	bool getStatus();
	static std::vector<Room>& getMasterList();

	// static functions
	static Room* search();
	static Room* search(std::string& roomNum);
	static Room* search(std::vector<Room> rooms, std::string& roomNum);

	static void readFile(std::string filepath);
	static void writeFile(std::string filepath);

	// other functions
	void displayInfo();
};
