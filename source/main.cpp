#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>

#include "House.h"
#include "Boarder.h"
#include "Date.h"
#include "Room.h"
#include "Assignment.h"
#include "Payment.h"

void readHouseFile(std::string filepath);
void readRoomFile(std::string filepath);
void readBoarderFile(std::string filepath);
void readAssignmentFile(std::string filepath);
void readPaymentFile(std::string filepath);

void mainMenu();
void houseMenu();
void boarderMenu();
void paymentMenu();

std::vector<House> houses;
std::vector<Room> rooms;
std::vector<Boarder> boarders;
std::vector<Assignment> assignmentList;
std::vector<Payment> paymentRecord;

// MAIN
int main() {
	
	readHouseFile("house.txt");				// add houses from house.txt
	readRoomFile("room.txt");				// add rooms from room.txt
	readBoarderFile("boarder.txt");			// add boarders from boarder.txt
	readAssignmentFile("assignment.txt");	// add assignments from assignment.txt
	readPaymentFile("payment.txt");			// add payments from payment.txt

	// menu
	mainMenu();
}


// SUPPLEMENTARY FUNCTIONS
// PRELIMINARIES
// readHouseFile -> reads data for boarding houses
void readHouseFile(std::string filepath) {
	std::ifstream inFile;

	inFile.open(filepath);

	inFile.ignore(1000, '\n');
	while (inFile.good()) {
		std::string code, name, address;

		std::getline(inFile, code, ',');
		std::getline(inFile, name, ',');
		std::getline(inFile, address);

		if (code != "" || name != "" || address != "") {
			House h(code, name, address);
			houses.push_back(h);
		}
	}

	inFile.close();
}

// readRoomFile -> reads data for rooms
void readRoomFile(std::string filepath) {
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
			House::search(houses, houseCode)->addRoom(r);
		}
	}

	inFile.close();
}

// readBoarderFile -> reads data for boarders
void readBoarderFile(std::string filepath) {
	std::ifstream inFile;

	inFile.open(filepath);

	inFile.ignore(1000, '\n');
	while (inFile.good()) {
		std::string bCode, bName, bBirth, bPhoneNumber, bReferrer;
		bool bStatus;

		std::getline(inFile, bCode, ',');
		std::getline(inFile, bName, ',');

		std::getline(inFile, bBirth, ',');
		Date bBirthDate(bBirth);

		std::getline(inFile, bPhoneNumber, ',');
		std::getline(inFile, bReferrer, ',');
		inFile >> bStatus;

		inFile.ignore(1000, '\n');

		// add to vector
		if (bCode != "") {
			Boarder b(bCode, bName, bBirthDate, bPhoneNumber, bReferrer, bStatus);
			boarders.push_back(b);
		}
	}

	inFile.close();
}

// readAssignmentFile -> reads data for assignments
void readAssignmentFile(std::string filepath) {
	std::ifstream inFile;

	inFile.open(filepath);

	inFile.ignore(1000, '\n');
	while (inFile.good()) {
		std::string bCode, rmNumber, aAssignDate;
		bool aStatus;

		std::getline(inFile, bCode, ',');
		std::getline(inFile, rmNumber, ',');

		std::getline(inFile, aAssignDate, ',');
		Date aAssignmentDate(aAssignDate);

		inFile >> aStatus;

		inFile.ignore(1000, '\n');

		// add to vector
		if (bCode != "" || rmNumber != "" || aAssignDate != "") {
			Boarder* b = Boarder::search(boarders, bCode);
			Room* r = Room::search(rooms, rmNumber);
			House* h = House::search(houses, r->getHouseCode());

			Assignment a(*b, *r, *h, aAssignmentDate, aStatus);

			assignmentList.push_back(a);
		}
	}

	inFile.close();
}

// readPaymentFile -> reads data for payments
void readPaymentFile(std::string filepath) {
	std::ifstream inFile;

	inFile.open(filepath);

	inFile.ignore(1000, '\n');
	while (inFile.good()) {
		std::string bCode, rmNumber, pPayDate;
		float pAmountDue, pAmountPaid;
		bool pStatus;

		std::getline(inFile, bCode, ',');
		std::getline(inFile, rmNumber, ',');

		std::getline(inFile, pPayDate, ',');
		Date pPaymentDate(pPayDate);

		char delim;
		inFile >> pAmountDue >> delim >> pAmountPaid >> delim >> pStatus;

		inFile.ignore(1000, '\n');

		// add to vector
		if (bCode != "" || rmNumber != "") {
			Boarder* b = Boarder::search(boarders, bCode);
			Room* r = Room::search(rooms, rmNumber);

			Payment p(*b, *r, pPaymentDate, pAmountDue, pAmountPaid, pStatus);

			paymentRecord.push_back(p);
		}
	}

	inFile.close();
}

// MENUS
// mainMenu -> menu prompted on startup
void mainMenu() {
	char choice;
	do {
		system("cls");

		std::cout << "[1] House\n";
		std::cout << "[2] Boarder\n";
		std::cout << "[3] Payment\n";
		std::cout << "[x] Exit\n";
		std::cout << "Choice: ";

		std::cin >> choice;

		if (choice == '1')
			houseMenu();
		if (choice == '2')
			boarderMenu();
		if (choice == '3')
			paymentMenu();
	} while (choice != 'x' && choice != 'X');

	std::cin.get();
}

// houseMenu -> menu for House option in Main Menu
void houseMenu() {
	char choice;
	do {
		system("cls");

		std::cout << "House Menu\n---\n";
		std::cout << "[1] Add House\n";
		std::cout << "[2] View All Houses\n";
		std::cout << "[3] Search House and Add a Room\n";
		std::cout << "[4] Search House and View All Rooms\n";
		std::cout << "[x] Go Back to Main Menu\n";
		std::cout << "Choice: ";

		std::cin >> choice;

		// evaluate choice
		if (choice == '1')
			House::add(houses);
		else if (choice == '2')
			House::viewAll(houses);
		else if (choice == '3')
			House::search(houses)->addRoom();
		else if (choice == '4')
			House::search(houses)->viewRooms();

	} while (choice != 'x' && choice != 'X');
}

// boarderMenu -> menu for Boarder option in Main Menu
void boarderMenu() {
	char choice;
	do {
		system("cls");

		std::cout << "Boarder Menu\n---\n";
		std::cout << "[1] Add Boarder\n";
		std::cout << "[2] View All Active Boarders and Assigned House/Room\n";
		std::cout << "[3] Assign a Boarder to a Room\n";
		std::cout << "[4] View All Current Boarders of a House\n";
		std::cout << "[x] Go Back to Main Menu\n";
		std::cout << "Choice: ";

		std::cin >> choice;

		// evaluate choice
		if (choice == '1')
			Boarder::add(boarders);
		else if (choice == '2')
			Assignment::viewActive(assignmentList);
		else if (choice == '3') {
			Boarder* b = Boarder::search(boarders);
			Room* r = Room::search(rooms);
			House* h = House::search(houses, r->getHouseCode());
			Assignment::add(assignmentList, *b, *r, *h);
		}
		else if (choice == '4')
			Assignment::viewActive(assignmentList, *House::search(houses));

	} while (choice != 'x' && choice != 'X');
}

// paymentMenu -> menu for Payment option in Main Menu
void paymentMenu() {
	char choice;
	do {
		system("cls");

		std::cout << "Payment Menu\n---\n";
		std::cout << "[1] Add Payment\n";
		std::cout << "[2] View All Payments of a Boarder\n";
		std::cout << "[3] View All Payments in a Given Month\n";
		std::cout << "[4] View All Payments in a Given Year\n";
		std::cout << "[x] Go Back to Main Menu\n";
		std::cout << "Choice: ";

		std::cin >> choice;

		// evaluate choice
		if (choice == '1')
			Payment::add(paymentRecord, assignmentList);
		else if (choice == '2')
			Payment::view(paymentRecord, *Boarder::search(boarders));
		else if (choice == '3')
			Payment::view(paymentRecord, Date::yearPrompt(), Date::monthPrompt());
		else if (choice == '4')
			Payment::view(paymentRecord, Date::yearPrompt());

	} while (choice != 'x' && choice != 'X');
}