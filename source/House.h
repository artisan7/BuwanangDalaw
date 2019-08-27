#pragma once

#include <string>
#include <vector>

#include "Room.h"

class House {
private:
	std::string code;
	std::string name;
	std::string address;

	std::vector<Room> roomList;

	static std::vector<House> masterList;

public:
	// constructor
	House(std::string code, std::string name, std::string address);

	// getters
	std::string getCode();
	std::string getAddress();
	static std::vector<House>& getMasterList();

	// static functions
	static void add();
	static void viewAll();
	static House* search();
	static House* search(std::string houseCode);

	static void readFile(std::string filepath, std::vector<Room>& rooms);
	static void writeFile(std::string filepath);

	void displayInfo();

	// room functions
	void addRoom();
	void addRoom(Room& r);
	void viewRooms();

	// overloaded operators
	bool operator==(House& other);
};
