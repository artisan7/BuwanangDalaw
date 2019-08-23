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

void mainMenu();
void houseMenu();

std::vector<House> houses;
std::vector<Boarder> boarders;
std::vector<Assignment> assignmentList;
std::vector<Payment> paymentRecord;

int main() {

	std::ifstream inFile;

	// add boarding houses from file
	inFile.open("house.txt");

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

	// add rooms from file
	inFile.open("room.txt");

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

		if (houseCode != "") {
			Room r(rmNumber, rmType, rmCondition, rmRentFee, rmStatus);
			House::search(houses, houseCode).addRoom(r);
		}
	}

	inFile.close();

	// add boarders from file
	inFile.open("boarder.txt");

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

		if (bCode != "") {
			Boarder b(bCode, bName, bBirthDate, bPhoneNumber, bReferrer, bStatus);
			boarders.push_back(b);
		}
	}

	inFile.close();
	
	// add assignments from file
	inFile.open("assignment.txt");

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
		
		if (bCode != "" || rmNumber != "" || aAssignDate != "") {
			Assignment a(bCode, rmNumber, aAssignmentDate, aStatus);
			assignmentList.push_back(a);
		}
	}

	inFile.close();
	
	// add payments from file
	inFile.open("payment.txt");

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
		
		if (bCode != "" || rmNumber != "") {
			Payment p(bCode, rmNumber, pPaymentDate, pAmountDue, pAmountPaid, pStatus);
			paymentRecord.push_back(p);
		}
	}

	inFile.close();

	Payment::viewAll(paymentRecord);

	/*
	// MENU
	mainMenu();

	std::cin.get();
}

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

		switch (choice) {
		case '1':
			houseMenu();
			break;
		case '2':
			//boarderMenu();
			break;
		case '3':
			//paymentMenu();
			break;
		}
	} while (choice != 'x' && choice != 'X');
	*/

	std::cin.get();
}

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

		switch (choice) {
		case '1':
			House::add(houses);
			break;
		case '2':
			House::viewAll(houses);
			break;
		case '3':
			House::search(houses).addRoom();
			break;
		case '4':
			House::search(houses).viewRooms();
		}
	} while (choice != 'x' && choice != 'X');
}
