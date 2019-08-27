#include "Room.h"

#include <iostream>
#include <fstream>
#include <cstdio>

std::vector<Room> Room::masterList;

// CONSTRUCTOR
Room::Room(std::string number, std::string houseCode, short int type, std::string condition, float rentFee, bool status)
	:number(number), houseCode(houseCode), type(type), condition(condition), rentFee(rentFee), status(status)
{
	masterList.push_back(*this);
}

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

bool Room::getStatus() { return status; }
std::vector<Room>& Room::getMasterList() { return masterList; }

// STATIC FUNCTIONS
// search(1) -> prompts the user to enter room number and return room that corresponds to it
Room* Room::search() {
	system("cls");

	std::cout << "|--SELECT A ROOM--|\n";
	int count = 0;
	for (std::vector<Room>::iterator itr = masterList.begin(); itr != masterList.end(); itr++) {
		if (!itr->status)
			std::cout << ++count << ".) " << itr->number << '\n';
	}
	std::cout << "0.) Go Back\n\n";

	unsigned short int choice;
	while (true) {
		std::cout << "Choice: ";
		std::cin >> choice;

		if (choice == 0)
			break;
		else if (choice > 0 && choice <= masterList.size())
			return &masterList[choice-1];
	}

	return nullptr;
}

// search(2) -> search room with room number from list of rooms
Room* Room::search(std::string& roomNum) {
	for (std::vector<Room>::iterator itr = masterList.begin(); itr != masterList.end(); itr++) {
		if (itr->number == roomNum)
			return &(*itr);
	}
	return nullptr;
}

// search (3) -> search room from specified list of rooms
Room* Room::search(std::vector<Room> rooms, std::string& roomNum) {
	for (std::vector<Room>::iterator itr = rooms.begin(); itr != rooms.end(); itr++) {
		if (itr->number == roomNum)
			return &(*itr);
	}
	return nullptr;
}

// readFile -> reads data for rooms
void Room::readFile(std::string filepath) {
	std::ifstream inFile;

	inFile.open(filepath);

	inFile.ignore(1000, '\n');
	while (inFile.good()) {
		std::string number, houseCode, condition;
		short int type;
		float rentFee;
		bool status;
		char delim;

		std::getline(inFile, number, ',');
		std::getline(inFile, houseCode, ',');
		inFile >> type >> delim;
		std::getline(inFile, condition, ',');
		inFile >> rentFee >> delim >> status;

		inFile.ignore(1000, '\n');

		if (houseCode != "")
			Room r(number, houseCode, type, condition, rentFee, status);
	}

	inFile.close();
}

// writeFile -> writes the room list data to file
void Room::writeFile(std::string filepath) {
	std::ofstream outFile;
	outFile.open(filepath);

	outFile << "roomnumber,housecode,roomtype,condition,monthly_rent,status\n";

	for (std::vector<Room>::iterator itr = masterList.begin(); itr != masterList.end(); itr++)
		outFile << itr->number << ',' << itr->houseCode << ',' << itr->type << ',' << itr->condition << ',' << itr->rentFee << ',' << itr->status << '\n';
}

//DISPLAY
// displayInfo -> display formatted info of room in console
void Room::displayInfo() {
	printf("%-10s%-10s%-30s%-15.2f%-10s\n", number.c_str(), getType().c_str(), condition.c_str(), rentFee, getStatus().c_str());
}