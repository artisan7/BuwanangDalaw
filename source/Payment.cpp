#include "Payment.h"

#include <cstdio>

// CONSTRUCTOR
Payment::Payment(std::string bCode, std::string rmNumber, Date paymentDate, float amountDue, float amountPaid, bool status)
	: boarderCode(bCode), roomNumber(rmNumber), paymentDate(paymentDate), amountDue(amountDue), amountPaid(amountPaid), status(status) {}

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

// display -> display payment information
void Payment::display() {
	printf("%-15s%-15s%-20s%15.2f%15.2f%10s\n", boarderCode.c_str(), roomNumber.c_str(), paymentDate.toString().c_str(), amountDue, amountPaid, getStatus().c_str());
}
