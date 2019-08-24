#include "Boarder.h"

#include <cstdio>

// CONSTRUCTOR
Boarder::Boarder(std::string code, std::string name, Date bDate, std::string pNumber, std::string referrer, bool status)
	: code(code), name(name), birthDate(bDate), phoneNumber(pNumber), referrer(referrer), status(status) {}

// GETTERS
// getStatus -> returns married/single depending on value
std::string Boarder::getStatus() {
	return (status) ? "married" : "single";
}

// STATIC FUNCTIONS
// viewAll -> displays all boarders in the boarder list
void Boarder::viewAll(std::vector<Boarder>& boarders) {
	printf("%-10s%-20s%-20s%-15s%-20s%-10s\n", "#", "Full Name", "Birth Date", "Phone Number", "Referrer", "Status");
	printf("%-10s%-20s%-20s%-15s%-20s%-10s\n", "-----", "-----", "-----", "-----", "-----", "-----");

	for (std::vector<Boarder>::iterator itr = boarders.begin(); itr != boarders.end(); itr++)
		itr->display();
}

// search -> searches a boarder with boarder code from the list of boarders
Boarder* Boarder::search(std::vector<Boarder>& boarders, std::string& boarderCode) {
	for (std::vector<Boarder>::iterator itr = boarders.begin(); itr != boarders.end(); itr++) {
		if (itr->code == boarderCode)
			return &(*itr);
	}
	return nullptr;
}

// OTHER FUNCTIONS
// display -> display a boarder's information
void Boarder::display() {
	printf("%-10s%-20s%-20s%-15s%-20s%-10s\n", code.c_str(), name.c_str(), birthDate.toString().c_str(), phoneNumber.c_str(), referrer.c_str(), getStatus().c_str());
}
