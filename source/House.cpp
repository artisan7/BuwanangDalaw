#include "House.h"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

std::vector<House> House::masterList;

// CONSTRUCTOR
House::House(std::string code, std::string name, std::string address)
	:code(code), name(name), address(address)
{
	masterList.push_back(*this);
}

// GETTERS
std::string House::getCode() { return code; }
std::string House::getAddress() { return address; }
std::vector<House>& House::getMasterList() { return masterList; }

// STATIC FUNCTIONS
// add -> adds a house to the list of houses
void House::add() {
	std::string code, name, address;

	system("cls");

	std::cout << "Add New House\n---\n";

	bool exists;
	do {
		std::cout << "House Code: ";
		std::cin >> code;

		if (search(code) != nullptr) {
			exists == true;
			std::cout << "ERROR: House Already Exists!\n";
		}
		else exists == false;

	} while (exists);

	std::cin.ignore();
	std::cout << "House Name: ";
	std::getline(std::cin, name);

	std::cout << "Address: ";
	std::getline(std::cin, address);

	House h(code, name, address);
}

// viewAll -> views all info of all houses in the list of houses
void House::viewAll() {

	system("cls");

	printf("|---------------------BOARDING HOUSES---------------------|\n");
	printf("%-10s%-20s%-20s\n", "Code", "Name", "Address");
	printf("%-10s%-20s%-20s\n", "-----", "-----", "-----");
	for (std::vector<House>::iterator itr = masterList.begin(); itr != masterList.end(); itr++)
		itr->displayInfo();
	printf("\nTotal # of Houses: %d", masterList.size());

	std::cout << std::endl << std::endl;
	system("pause");
}

// search (1) -> prompts the user to enter a houseCode and searches for it from the list of houses
House* House::search() {
	system("cls");

	std::cout << "|--SELECT A HOUSE--|\n";

	int count = 0;
	for (std::vector<House>::iterator itr = masterList.begin(); itr != masterList.end(); itr++)
		std::cout << ++count << ".) " << itr->code << " - " << itr->name << '\n';
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

// search (2) -> searches for the specified houseCode from the list of houses
House* House::search(std::string houseCode) {
	for (std::vector<House>::iterator itr = masterList.begin(); itr != masterList.end(); itr++) {
		if (houseCode == itr->code)
			return &(*itr);
	}
	return nullptr;
}

// readFile -> reads data for boarding houses
void House::readFile(std::string filepath, std::vector<Room>& rooms) {
	std::ifstream inFile;

	inFile.open(filepath);

	inFile.ignore(1000, '\n');
	while (inFile.good()) {
		std::string code, name, address;

		std::getline(inFile, code, ',');
		std::getline(inFile, name, ',');
		std::getline(inFile, address);

		if (code != "" || name != "" || address != "")
			House h(code, name, address);
	}

	inFile.close();

	// assign rooms to houses
	for (std::vector<Room>::iterator itr = rooms.begin(); itr != rooms.end(); itr++)
		House::search(itr->getHouseCode())->addRoom(*itr);
}

// writeFile -> writes the house list data to file
void House::writeFile(std::string filepath) {
	std::ofstream outFile;
	outFile.open(filepath);

	outFile << "housecode,housename,address\n";

	for (std::vector<House>::iterator itr = masterList.begin(); itr != masterList.end(); itr++)
		outFile << itr->code << ',' << itr->name << ',' << itr->address << '\n';
}

// OTHER FUNCTIONS
// displayInfo -> displays formatted info of the house
void House::displayInfo() {
	printf("%-10s%-20s%-20s\n", code.c_str(), name.c_str(), address.c_str());
}

// ROOM FUNCTIONS
// addRoom (1) -> prompts the user for the new room information and adds the room to the house
void House::addRoom() {
	std::string number, condition;
	short int type;
	float rentFee;
	bool status;
	
	system("cls");

	std::cout << "Add New Room to House " << this->code << "\n---\n";

	bool exists;
	do {
		std::cout << "Room Number:";
		std::cin >> number;

		if (Room::search(roomList, number) != nullptr) {
			exists == true;
			std::cout << "ERROR: Room Already Exists!\n";
		}
		else exists = false;
	} while (exists);

	std::cout << "Room Type [(1) common, (2) basic, (3) grand]: ";
	std::cin >> type;

	std::cin.ignore();
	std::cout << "Room Condition: ";
	std::getline(std::cin, condition);

	std::cout << "Rent Fee: ";
	std::cin >> rentFee;

	std::cout << "Room Status [(0) occupied, (1) available]: ";
	std::cin >> status;

	Room r(number, this->code, type, condition, rentFee, status);

	addRoom(r);
}

// addRoom (2) -> adds the specified room in the house
void House::addRoom(Room& r) { roomList.push_back(r); }

// viewRooms -> views all rooms of the house
void House::viewRooms() {
	system("cls");

	printf("|--------------------------%s--------------------------|\n", this->code.c_str());
	printf("%-10s%-10s%-30s%-15s%-10s\n", "Room #", "Type", "Condition", "Rental Fee", "Status");
	printf("%-10s%-10s%-30s%-15s%-10s\n", "-----", "-----", "-----", "-----", "-----");
	for (std::vector<Room>::iterator itr = roomList.begin(); itr != roomList.end(); itr++)
		itr->displayInfo();

	printf("\nTotal # of Rooms: %d", roomList.size());

	std::cout << std::endl << std::endl;
	system("pause");
}

// OVERLOADED OPERATORS
bool House::operator==(House& other) { return this->code == other.code; }