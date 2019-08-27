#include "Boarder.h"

#include <iostream>
#include <fstream>
#include <cstdio>

std::vector<Boarder> Boarder::masterList;

// CONSTRUCTOR
Boarder::Boarder(std::string code, std::string name, Date birthDate, std::string pNumber, std::string referrer, bool status)
	: code(code), name(name), birthDate(birthDate), phoneNumber(pNumber), referrer(referrer), status(status)
{
	masterList.push_back(*this);
}

// GETTERS
std::string Boarder::getCode() { return code; }
std::string Boarder::getName() { return name; }
std::string Boarder::getPhoneNumber() { return phoneNumber; }
Date & Boarder::getBirthDate() { return birthDate; }
bool Boarder::getStatus() { return status; }
std::vector<Boarder>& Boarder::getMasterList() { return masterList; }

// SETTERS
void Boarder::setStatus(bool status) { this->status = status; }

// STATIC FUNCTIONS
// add -> prompts the user for new boarder information and adds them to the boarder list
void Boarder::add() {
	std::string code, name, phoneNumber, referrer;

	system("cls");

	std::cout << "Add New Boarder\n---\n";

	std::cout << "Boarder Code: ";
	std::cin >> code;

	std::cin.ignore();
	bool exists;
	do {
		std::cout << "Boarder Name:";
		std::getline(std::cin, name);

		if (search(code) != nullptr) {
			exists == true;
			std::cout << "ERROR: Boarder Already Exists!\n";
		}
		else exists = false;
	} while (exists);

	std::cout << "Birthdate:\n";
	Date birthDate;

	std::cout << "Contact Number: ";
	std::cin >> phoneNumber;

	std::cin.ignore();
	std::cout << "Referrer: (none if no referrer)";
	std::getline(std::cin, referrer);

	Boarder b(code, name, birthDate, phoneNumber, referrer, 0);
}

// search (1) -> prompts the user to enter boarder code and return boarder that corresponds to it
Boarder* Boarder::search() {
	system("cls");

	std::cout << "|--SELECT A BOARDER--|\n";

	int count = 0;
	for (std::vector<Boarder>::iterator itr = masterList.begin(); itr != masterList.end(); itr++)
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

// search (2) -> searches a boarder with boarder code from the list of boarders
Boarder* Boarder::search(std::string& boarderCode) {
	for (std::vector<Boarder>::iterator itr = masterList.begin(); itr != masterList.end(); itr++) {
		if (itr->code == boarderCode)
			return &(*itr);
	}
	return nullptr;
}

// viewAll -> displays all boarders in the boarder list
void Boarder::viewAll() {
	printf("%-10s%-20s%-20s%-15s%-20s%-10s\n", "#", "Full Name", "Birth Date", "Phone Number", "Referrer", "Status");
	printf("%-10s%-20s%-20s%-15s%-20s%-10s\n", "-----", "-----", "-----", "-----", "-----", "-----");

	for (std::vector<Boarder>::iterator itr = masterList.begin(); itr != masterList.end(); itr++)
		itr->display();
}

// readFile -> reads data for boarders
void Boarder::readFile(std::string filepath) {
	std::ifstream inFile;

	inFile.open(filepath);

	inFile.ignore(1000, '\n');
	while (inFile.good()) {
		std::string code, name, birth, phoneNumber, referrer;
		bool status;

		std::getline(inFile, code, ',');
		std::getline(inFile, name, ',');

		std::getline(inFile, birth, ',');
		Date birthDate(birth);

		std::getline(inFile, phoneNumber, ',');
		std::getline(inFile, referrer, ',');
		inFile >> status;

		inFile.ignore(1000, '\n');

		if (code != "")
			Boarder b(code, name, birthDate, phoneNumber, referrer, status);
	}

	inFile.close();
}

// writeFile -> writes the boarder list data to file
void Boarder::writeFile(std::string filepath) {
	std::ofstream outFile;
	outFile.open(filepath);

	outFile << "boarder_code,boarder_name,bdate,pnumber,referrer,status\n";

	for (std::vector<Boarder>::iterator itr = masterList.begin(); itr != masterList.end(); itr++)
		outFile << itr->code << ',' << itr->name << ',' << itr->birthDate.toSlashFormat() << ',' << itr->phoneNumber << ',' << itr->referrer << ',' << itr->status << '\n';
}

// OTHER FUNCTIONS
// display -> display a boarder's information
void Boarder::display() {
	printf("%-10s%-20s%-20s%-15s%-20s\n", code.c_str(), name.c_str(), birthDate.toString().c_str(), phoneNumber.c_str(), referrer.c_str());
}

// OVERLOADED OPERATORS
bool Boarder::operator==(Boarder& other) { return this->code == other.code; }