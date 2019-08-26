#include "Room.h"

#include <iostream>
#include <fstream>
#include <cstdio>

// CONSTRUCTOR
Room::Room(std::string number, std::string houseCode, short int type, std::string condition, float rentFee, bool status)
	:number(number), houseCode(houseCode), type(type), condition(condition), rentFee(rentFee), status(status) {}

std::string Room::getNumber() { return number; }
std::string Room::getHouseCode() { return houseCode; }
float Room::getFee() { return rentFee; }

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
// search(1) -> prompts the user to enter room number and return room that corresponds to it
Room * Room::search(std::vector<Room>& rooms) {

	std::string roomNumber;

	while (true) {
		std::cout << "Enter Room Number: ";
		std::cin >> roomNumber;

		for (std::vector<Room>::iterator itr = rooms.begin(); itr != rooms.end(); itr++) {
			if (roomNumber == itr->number)
				return &(*itr);
		}

		std::cout << "Room does not exist!\n";
	}
}

// search(2) -> search room with room number from list of rooms
Room* Room::search(std::vector<Room>& rooms, std::string& roomNum) {
	for (std::vector<Room>::iterator itr = rooms.begin(); itr != rooms.end(); itr++) {
		if (itr->number == roomNum)
			return &(*itr);
	}
	return nullptr;
}

// add -> adds room object to list
void Room::add(std::vector<Room>& rooms, Room & r) { rooms.push_back(r); }

// readFile -> reads data for rooms
void Room::readFile(std::vector<Room>& rooms, std::string filepath) {
	std::ifstream inFile;

	inFile.open(filepath);

	inFile.ignore(1000, '\n');
	while (inFile.good()) {
		std::string rmNumber, houseCode, rmCondition;
		short int rmType;
		float rmRentFee;
		bool rmStatus;
		char delim;

		std::getline(inFile, rmNumber, ',');
		std::getline(inFile, houseCode, ',');
		inFile >> rmType >> delim;
		std::getline(inFile, rmCondition, ',');
		inFile >> rmRentFee >> delim >> rmStatus;

		inFile.ignore(1000, '\n');

		// add to vector
		if (houseCode != "") {
			Room r(rmNumber, houseCode, rmType, rmCondition, rmRentFee, rmStatus);
			Room::add(rooms, r);
		}
	}

	inFile.close();
}

// writeFile -> writes the room list data to file
void Room::writeFile(std::vector<Room>& rooms, std::string filepath) {
	std::ofstream outFile;
	outFile.open(filepath);

	outFile << "roomnumber,housecode,roomtype,condition,monthly_rent,status\n";

	for (std::vector<Room>::iterator itr = rooms.begin(); itr != rooms.end(); itr++)
		outFile << itr->number << ',' << itr->houseCode << ',' << itr->type << ',' << itr->condition << ',' << itr->rentFee << ',' << itr->status << '\n';
}

//DISPLAY
// displayInfo -> display formatted info of room in console
void Room::displayInfo() {
	printf("%-10s%-10s%-30s%-15.2f%-10s\n", number.c_str(), getType().c_str(), condition.c_str(), rentFee, getStatus().c_str());
}

