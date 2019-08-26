#include "Boarder.h"

#include <iostream>
#include <fstream>
#include <cstdio>

// CONSTRUCTOR
Boarder::Boarder(std::string code, std::string name, Date birthDate, std::string pNumber, std::string referrer, bool status)
	: code(code), name(name), birthDate(birthDate), phoneNumber(pNumber), referrer(referrer), status(status) {}

std::string Boarder::getCode() { return code; }

std::string Boarder::getName() { return name; }

std::string Boarder::getPhoneNumber() { return phoneNumber; }

Date & Boarder::getBirthDate() { return birthDate; }

// GETTERS
// getStatus -> returns status
bool Boarder::getStatus() { return status; }

// STATIC FUNCTIONS
// viewAll -> displays all boarders in the boarder list
void Boarder::viewAll(std::vector<Boarder>& boarders) {
	printf("%-10s%-20s%-20s%-15s%-20s%-10s\n", "#", "Full Name", "Birth Date", "Phone Number", "Referrer", "Status");
	printf("%-10s%-20s%-20s%-15s%-20s%-10s\n", "-----", "-----", "-----", "-----", "-----", "-----");

	for (std::vector<Boarder>::iterator itr = boarders.begin(); itr != boarders.end(); itr++)
		itr->display();
}

// search(1) -> prompts the user to enter boarder code and return boarder that corresponds to it
Boarder* Boarder::search(std::vector<Boarder>& boarders) {
	
	std::string boarderCode;

	system("cls");
	
	while (true) {
		std::cout << "Enter Boarder Code: ";
		std::cin >> boarderCode;

		for (std::vector<Boarder>::iterator itr = boarders.begin(); itr != boarders.end(); itr++) {
			if (boarderCode == itr->code)
				return &(*itr);
		}

		std::cout << "Boarder does not exist!\n";
	}
}

// search(2) -> searches a boarder with boarder code from the list of boarders
Boarder* Boarder::search(std::vector<Boarder>& boarders, std::string& boarderCode) {
	for (std::vector<Boarder>::iterator itr = boarders.begin(); itr != boarders.end(); itr++) {
		if (itr->code == boarderCode)
			return &(*itr);
	}
	return nullptr;
}

// add -> prompts the user for new boarder information and adds them to the boarder list
void Boarder::add(std::vector<Boarder>& boarders) {
	std::string bCode, bName, bPhoneNumber, bReferrer;

	system("cls");

	std::cout << "Add New Boarder\n---\n";

	std::cout << "Boarder Code: ";
	std::cin >> bCode;

	std::cin.ignore();
	std::cout << "Boarder Name:";
	std::getline(std::cin, bName);

	// prompt for birth date
	std::cout << "Birthdate:\n";
	Date bBirthDate;

	std::cout << "Contact Number: ";
	std::cin >> bPhoneNumber;

	std::cin.ignore();
	std::cout << "Referrer: (none if no referrer)";
	std::getline(std::cin, bReferrer);

	Boarder b(bCode, bName, bBirthDate, bPhoneNumber, bReferrer, 0);

	boarders.push_back(b);
}

// readFile -> reads data for boarders
void Boarder::readFile(std::vector<Boarder>& boarders, std::string filepath) {
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

		// add to vector
		if (code != "") {
			Boarder b(code, name, birthDate, phoneNumber, referrer, status);
			boarders.push_back(b);
		}
	}

	inFile.close();
}

// writeFile -> writes the boarder list data to file
void Boarder::writeFile(std::vector<Boarder>& boarders, std::string filepath) {
	std::ofstream outFile;
	outFile.open(filepath);

	outFile << "boarder_code,boarder_name,bdate,pnumber,referrer,status\n";

	for (std::vector<Boarder>::iterator itr = boarders.begin(); itr != boarders.end(); itr++)
		outFile << itr->code << ',' << itr->name << ',' << itr->birthDate.toSlashFormat() << ',' << itr->phoneNumber << ',' << itr->referrer << ',' << itr->status << '\n';
}

// OTHER FUNCTIONS
// display -> display a boarder's information
void Boarder::display() {
	printf("%-10s%-20s%-20s%-15s%-20s\n", code.c_str(), name.c_str(), birthDate.toString().c_str(), phoneNumber.c_str(), referrer.c_str());
}

bool Boarder::operator==(Boarder& other) {
	return this->code == other.code;
}
