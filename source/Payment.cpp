#include "Payment.h"

#include <iostream>
#include <cstdio>

// CONSTRUCTOR
Payment::Payment(Boarder& b, Room& r, Date paymentDate, float amountDue, float amountPaid, bool status)
	: boarder(b), room(r), paymentDate(paymentDate), amountDue(amountDue), amountPaid(amountPaid), status(status) {}

// getters
// getStatus -> returns active/inactive depending on value
std::string Payment::getStatus() {
	return (status) ? "active" : "inactive";
}

// static functions
// viewAll -> displays all assignments in the assignment record
void Payment::viewAll(std::vector<Payment>& record) {
	printf("%-15s%-15s%-20s%15s%15s%10s\n", "Boarder Code", "Room Number", "Assignment Date", "Amount Due", "Amount Paid", "Status");
	printf("%-15s%-15s%-20s%15s%15s%10s\n", "-----", "-----", "-----", "-----", "-----", "-----");
		
	for (std::vector<Payment>::iterator itr = record.begin(); itr != record.end(); itr++)
		itr->display();
}

void Payment::add(std::vector<Payment>& payments, std::vector<Assignment>& assignments) {
	std::string bCode, pPayDate;
	float amountDue, amountPaid;

	system("cls");

	std::cout << "Add New Payment\n---\n";

	std::cout << "Boarder Code: ";
	std::cin >> bCode;

	std::cout << "Payment Date: \n";
	Date bBirthDate;

	std::cout << "Amount Due: ";
	std::cin >> amountDue;

	std::cout << "Amount Paid: ";
	std::cin >> amountPaid;
	/*
	Boarder* = 

	Payment p(bCode, bName, bBirthDate, bPhoneNumber, bReferrer, 0);

	boarders.push_back(b);
	*/
}

void Payment::view(std::vector<Payment>& record, Boarder & b)
{
}

void Payment::view(std::vector<Payment>& record, int year, int month)
{
}

// display -> display payment information
void Payment::display() {
	printf("%-15s%-15s%-20s%15.2f%15.2f%10s\n", boarder.getCode().c_str(), room.getNumber().c_str(), paymentDate.toString().c_str(), amountDue, amountPaid, getStatus().c_str());
}
