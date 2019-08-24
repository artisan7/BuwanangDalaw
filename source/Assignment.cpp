#include "Assignment.h"

#include <cstdio>

// CONSTRUCTOR
Assignment::Assignment(std::string bCode, std::string rmNumber, Date assignDate, bool status)
	: boarderCode(bCode), roomNumber(rmNumber), assignDate(assignDate), status(status), boarder(nullptr), room(nullptr) {}

// getters
// getStatus -> returns active/inactive depending on value
std::string Assignment::getStatus() {
	return (status) ? "active" : "inactive";
}

Boarder & Assignment::getBoarder() {
	return *boarder;
}

// static functions
// viewAll -> displays all assignments in the assignment record
void Assignment::viewAll(std::vector<Assignment>& assignList) {
	printf("%-15s%-15s%-20s%-10s\n", "Boarder Code", "Room Number", "Assignment Date", "Status");
	printf("%-15s%-15s%-20s%-10s\n", "-----", "-----", "-----", "-----");
		
	for (std::vector<Assignment>::iterator itr = assignList.begin(); itr != assignList.end(); itr++)
		itr->display();
}

// display -> display assignment information
void Assignment::display() {
	printf("%-15s%-15s%-20s%-10s\n", boarderCode.c_str(), roomNumber.c_str(), assignDate.toString().c_str(), getStatus().c_str());
}
