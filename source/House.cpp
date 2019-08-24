#include "House.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>

int House::count = 0;

// CONSTRUCTOR
House::House(std::string code, std::string name, std::string address)
	:code(code), name(name), address(address), roomCount(0)
{
	count++;
}

// GETTERS
std::string House::getCode() { return code; }

// STATIC FUNCTIONS
// add -> adds a house to the list of houses
void House::add(std::vector<House>& houses) {
	std::string hCode, hName, hAddress;

	system("cls");

	std::cout << "Add New House\n---\n";

	std::cout << "House Code: ";
	std::cin >> hCode;

	std::cin.ignore();
	std::cout << "House Name: ";
	std::getline(std::cin, hName);

	std::cout << "Address: ";
	std::getline(std::cin, hAddress);

	House h(hCode, hName, hAddress);
	houses.push_back(h);
}

// viewAll -> views all info of all houses in the list of houses
void House::viewAll(std::vector<House>& houses) {

	system("cls");

	printf("[---------------------BOARDING HOUSES---------------------]\n");
	printf("%-10s%-20s%-20s\n", "Code", "Name", "Address");
	printf("%-10s%-20s%-20s\n", "-----", "-----", "-----");
	for (std::vector<House>::iterator itr = houses.begin(); itr != houses.end(); itr++)
		itr->displayInfo();
	printf("\nTotal # of Houses: %d", count);

	std::cout << std::endl << std::endl;
	system("pause");
}

// search (1) -> prompts the user to enter a houseCode and searches for it from the list of houses
House* House::search(std::vector<House>& houses) {

	std::string houseCode;
	
	system("cls");

	while (true) {
		std::cout << "Enter House Code: ";
		std::cin >> houseCode;

		for (std::vector<House>::iterator itr = houses.begin(); itr != houses.end(); itr++) {
			if (houseCode == itr->code)
				return &(*itr);
		}

		std::cout << "House does not exist!\n";
	}
}

// search (2) -> searches for the specified houseCode from the list of houses
House* House::search(std::vector<House>& houses, std::string& houseCode)
{
	for (std::vector<House>::iterator itr = houses.begin(); itr != houses.end(); itr++) {
		if (houseCode == itr->code)
			return &(*itr);
	}
	return nullptr;
}

// OTHER FUNCTIONS
// displayInfo -> displays formatted info of the house
void House::displayInfo() {
	printf("%-10s%-20s%-20s\n", code.c_str(), name.c_str(), address.c_str());
}

// ROOM FUNCTIONS
// addRoom (1) -> prompts the user for the new room information and adds the room to the house
void House::addRoom() {
	std::string rNum, rCondition;
	short int rType;
	float rRentFee;
	bool rStatus;
	
	system("cls");

	std::cout << "Add New Room to House " << this->code << "\n---\n";

	std::cout << "Room Number: ";
	std::cin >> rNum;

	std::cout << "Room Type [(1) common, (2) basic, (3) grand]: ";
	std::cin >> rType;

	std::cin.ignore();
	std::cout << "Room Condition: ";
	std::getline(std::cin, rCondition);

	std::cout << "Rent Fee: ";
	std::cin >> rRentFee;

	std::cout << "Room Status [(0) occupied, (1) available]: ";
	std::cin >> rStatus;

	Room r(rNum, rType, rCondition, rRentFee, rStatus);

	addRoom(r);
}

// addRoom (2) -> adds the specified room in the house
void House::addRoom(Room & r) {
	roomList.push_back(r);
	roomCount++;
}

// viewRooms -> views all rooms of the house
void House::viewRooms() {
	system("cls");

	printf("[--------------------------%s--------------------------]\n", this->code.c_str());
	printf("%-10s%-10s%-30s%-15s%-10s\n", "Room #", "Type", "Condition", "Rental Fee", "Status");
	printf("%-10s%-10s%-30s%-15s%-10s\n", "-----", "-----", "-----", "-----", "-----");
	for (std::vector<Room>::iterator itr = roomList.begin(); itr != roomList.end(); itr++)
		itr->displayInfo();

	printf("\nTotal # of Rooms: %d", roomCount);

	std::cout << std::endl << std::endl;
	system("pause");
}


