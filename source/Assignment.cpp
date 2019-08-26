#include "Assignment.h"

#include <iostream>
#include <fstream>
#include <cstdio>

// CONSTRUCTOR
Assignment::Assignment(Boarder& b, Room& r, House& h, Date assignDate, bool status)
	:boarder(b), room(r), house(h), assignDate(assignDate), status(status) {}

// GETTERS
Room& Assignment::getRoom() { return room; }
House & Assignment::getHouse() { return house;  }
Date& Assignment::getAssignDate() { return assignDate; }
Boarder & Assignment::getBoarder() { return boarder; }
bool Assignment::getStatus() { return status; }

// STATIC FUNCTIONS
// add -> adds a new assignment to the list
void Assignment::add(std::vector<Assignment>& assignments, Boarder& boarder,  Room& room, House& house) {
	Date assignDate;
	Assignment a(boarder, room, house, assignDate, 1);
	assignments.push_back(a);
}

// search -> searches for an assignment using boarder and room information
Assignment* Assignment::search(std::vector<Assignment>& assignments, Boarder& b, Room& r) {
	for (std::vector<Assignment>::iterator itr = assignments.begin(); itr != assignments.end(); itr++) {
		if (itr->boarder.getCode() == b.getCode() && itr->room.getNumber() == r.getNumber())
			return &(*itr);
	}
	return nullptr;
}

// viewAll -> displays all assignments in the assignment record
void Assignment::viewAll(std::vector<Assignment>& assignments) {
	printf("-------------------VIEW ACTIVE BOARDERS---------------------");
	printf("%-15s%-15s%-20s%-10s\n", "Boarder Code", "Room Number", "Assignment Date", "Status");
	printf("%-15s%-15s%-20s%-10s\n", "-----", "-----", "-----", "-----");
	
	for (std::vector<Assignment>::iterator itr = assignments.begin(); itr != assignments.end(); itr++)
		itr->display();
}

// viewActive (1) -> views all active assignments
void Assignment::viewActive(std::vector<Assignment>& assignments) {
	system("cls");

	printf("----------------------------------VIEW ACTIVE BOARDERS------------------------------------\n");
	printf("%-15s%-20s%-20s%-15s%s\n", "Boarder Code", "Boarder Name", "Birth Date", "Contact #", "Rent Details");
	printf("%-15s%-20s%-20s%-15s%s\n", "-----", "-----", "-----", "-----", "-----");

	int count = 0;
	for (std::vector<Assignment>::iterator itr = assignments.begin(); itr != assignments.end(); itr++) {
		if (itr->getStatus()) {
			Boarder& b = itr->getBoarder();
			House& h = itr->getHouse();
			std::string roomNumber = itr->getRoom().getNumber();

			printf("%-15s%-20s%-20s%-15s%s @ %s\n", b.getCode().c_str(), b.getName().c_str(), b.getBirthDate().toString().c_str(), b.getPhoneNumber().c_str(), roomNumber.c_str(), h.getAddress().c_str());
			count++;
		}
	}

	printf("# of Assignments: %d", count);

	std::cout << std::endl << std::endl;
	system("pause");
}

// viewActive (2) -> views all active assignments in a specified house
void Assignment::viewActive(std::vector<Assignment>& assignments, House& h) {

	system("cls");

	printf("-------------------VIEW ACTIVE BOARDERS---------------------\n");
	printf("%-15s%-20s%s\n", "Room Number", "Date Started", "Boarder");
	printf("%-15s%-20s%s\n", "-----", "-----", "-----");

	int count = 0;
	for (std::vector<Assignment>::iterator itr = assignments.begin(); itr != assignments.end(); itr++) {
		if (itr->getHouse().getCode() == h.getCode() && itr->getStatus()) {
			std::string roomNumber = itr->room.getNumber();
			std::string assignDate = itr->assignDate.toString();
			Boarder& b = itr->boarder;

			printf("%-15s%-20s%s: %s; %s %s\n", roomNumber.c_str(), assignDate.c_str(), b.getCode().c_str(), b.getName().c_str(), b.getBirthDate().toString().c_str(), b.getPhoneNumber().c_str());
			count++;
		}
	}
	printf("# of Active Assignments in %s: %d", h.getCode().c_str(), count);

	std::cout << std::endl << std::endl;
	system("pause");
}

// readFile -> reads data for assignments
void Assignment::readFile(std::vector<Assignment>& assignments, std::string filepath, std::vector<House>& houses, std::vector<Boarder>& boarders, std::vector<Room>& rooms) {
	std::ifstream inFile;

	inFile.open(filepath);

	inFile.ignore(1000, '\n');
	while (inFile.good()) {
		std::string boarderCode, roomNumber, assignDate;
		bool status;

		std::getline(inFile, boarderCode, ',');
		std::getline(inFile, roomNumber, ',');

		std::getline(inFile, assignDate, ',');
		Date assignmentDate(assignDate);

		inFile >> status;

		inFile.ignore(1000, '\n');

		// add to vector
		if (boarderCode != "" || roomNumber != "" || assignDate != "") {
			Boarder* b = Boarder::search(boarders, boarderCode);
			Room* r = Room::search(rooms, roomNumber);
			House* h = House::search(houses, r->getHouseCode());

			Assignment a(*b, *r, *h, assignmentDate, status);
			assignments.push_back(a);
		}
	}

	inFile.close();
}

// writeFile -> writes the assignment list data to file
void Assignment::writeFile(std::vector<Assignment>& assignments, std::string filepath) {
	std::ofstream outFile;
	outFile.open(filepath);

	outFile << "boarder_code,roomnumber,assign_date,status\n";

	for (std::vector<Assignment>::iterator itr = assignments.begin(); itr != assignments.end(); itr++)
		outFile << itr->boarder.getCode() << ',' << itr->room.getNumber() << ',' << itr->assignDate.toSlashFormat() << ',' << itr->status << '\n';
}

// OTHER FUNCTIONS
// display -> display assignment information
void Assignment::display() {
	printf("%-15s%-15s%-20s\n", boarder.getCode().c_str(), room.getNumber().c_str(), assignDate.toString().c_str());
}