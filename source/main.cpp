#include <iostream>

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

// MAIN
int main() {
	
	// read from files
	Room::readFile("room.txt");																						// add rooms from room.txt
	House::readFile("house.txt", Room::getMasterList());															// add houses from house.txt
	Boarder::readFile("boarder.txt");																				// add boarders from boarder.txt
	Assignment::readFile("assignment.txt", House::getMasterList(), Boarder::getMasterList(), Room::getMasterList());// add assignments from assignment.txt
	Payment::readFile("payment.txt", Boarder::getMasterList(), Room::getMasterList(), Assignment::getMasterList());	// add payments from payment.txt

	//  main interface
	mainMenu();

	// write to files
	House::writeFile("house.txt");
	Room::writeFile("room.txt");
	Boarder::writeFile("boarder.txt");
	Assignment::writeFile("assignment.txt");
	Payment::writeFile("payment.txt");
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
			House::add();
		else if (choice == '2')
			House::viewAll();
		else if (choice == '3') {
			House* h = House::search();
			if (h != nullptr) h->addRoom();
		}
		else if (choice == '4') {
			House* h = House::search();
			if (h != nullptr) h->viewRooms();
		}
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
			Boarder::add();
		else if (choice == '2')
			Assignment::viewActive();
		else if (choice == '3') {
			Boarder* b = Boarder::search();
			if (b != nullptr) {
				Room* r = Room::search();
				if (r != nullptr)
					Assignment::add(*b, *r, *House::search(r->getHouseCode()));
			}
		}
		else if (choice == '4')
			Assignment::viewActive(*House::search());

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
			Payment::add(Assignment::getMasterList(), Boarder::getMasterList(), Room::getMasterList());
		else if (choice == '2')
			Payment::view(*Boarder::search());
		else if (choice == '3') {
			system("cls");
			int month = Date::monthPrompt();
			int year = Date::yearPrompt();
			Date d(year, month);
			Payment::view(d);
		}
		else if (choice == '4') {
			system("cls");
			Date d(Date::yearPrompt());
			Payment::view(d);
		}

	} while (choice != 'x' && choice != 'X');
}