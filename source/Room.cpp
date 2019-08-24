#include "Room.h"

#include <cstdio>

// CONSTRUCTOR
Room::Room(std::string number, short int type, std::string condition, float rentFee, bool status)
	:number(number), type(type), condition(condition), rentFee(rentFee), status(status) {}

// GETTERS
// getType -> returns the room type based on designated value
std::string Room::getType() {
	switch (type) {
		case 1: return "common";
		case 2: return "basic";
		case 3: return "grand";
		default: return "";
	}
}

// getStatus -> returns available/occupied based on value
std::string Room::getStatus() {
	return (status) ? "available" : "occupied";
}

// STATIC FUNCTIONS
// search -> search room with room number from list of rooms
Room* Room::search(std::vector<Room>& rooms, std::string& roomNum) {
	for (std::vector<Room>::iterator itr = rooms.begin(); itr != rooms.end(); itr++) {
		if (itr->number == roomNum)
			return &(*itr);
	}
	return nullptr;
}

//DISPLAY
// displayInfo -> display formatted info of room in console
void Room::displayInfo() {
	printf("%-10s%-10s%-30s%-15.2f%-10s\n", number.c_str(), getType().c_str(), condition.c_str(), rentFee, getStatus().c_str());
}

