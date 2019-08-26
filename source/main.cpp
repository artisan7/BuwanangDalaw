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
	
	// read from files
	House::readFile(houses, "house.txt");				// add houses from house.txt
	Room::readFile(rooms, "room.txt");				// add rooms from room.txt
	for (std::vector<Room>::iterator itr = rooms.begin(); itr != rooms.end(); itr++)
		House::search(houses, itr->getHouseCode())->addRoom(*itr);
	Boarder::readFile(boarders, "boarder.txt");			// add boarders from boarder.txt
	Assignment::readFile(assignmentList, "assignment.txt", houses, boarders, rooms);	// add assignments from assignment.txt
	Payment::readFile(paymentRecord, "payment.txt", boarders, rooms, assignmentList);			// add payments from payment.txt

	// menu
	mainMenu();

	// write to files
	House::writeFile(houses, "house.txt");
	Room::writeFile(rooms, "room.txt");
	Boarder::writeFile(boarders, "boarder.txt");
	Assignment::writeFile(assignmentList, "assignment.txt");
	Payment::writeFile(paymentRecord, "payment.txt");
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
			Payment::add(paymentRecord, assignmentList, boarders, rooms);
		else if (choice == '2')
			Payment::view(paymentRecord, *Boarder::search(boarders));
		else if (choice == '3') {
			system("cls");
			int month = Date::monthPrompt();
			int year = Date::yearPrompt();
			Date d(year, month);
			Payment::view(paymentRecord, d);
		}
		else if (choice == '4') {
			system("cls");
			Date d(Date::yearPrompt());
			Payment::view(paymentRecord, d);
		}

	} while (choice != 'x' && choice != 'X');
}