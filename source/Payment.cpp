#include "Payment.h"

#include <iostream>
#include <fstream>
#include <cstdio>

// CONSTRUCTOR
Payment::Payment(Assignment& a, Date paymentDate, float amountDue, float amountPaid, bool status)
	: assignment(a), paymentDate(paymentDate), amountDue(amountDue), amountPaid(amountPaid), status(status) {}

// getters
// getStatus -> returns active/inactive depending on value
std::string Payment::getStatus() {
	return (status) ? "active" : "inactive";
}

// static functions
// viewAll -> displays all payments in the payment record
void Payment::viewAll(std::vector<Payment>& record) {
	printf("%-15s%-15s%-20s%15s%15s%10s\n", "Boarder Code", "Room Number", "Assignment Date", "Amount Due", "Amount Paid", "Status");
	printf("%-15s%-15s%-20s%15s%15s%10s\n", "-----", "-----", "-----", "-----", "-----", "-----");
		
	for (std::vector<Payment>::iterator itr = record.begin(); itr != record.end(); itr++)
		itr->display();
}

// add -> prompts the user for information and adds to payment record
void Payment::add(std::vector<Payment>& payments, std::vector<Assignment>& assignments, std::vector<Boarder>& boarders, std::vector<Room>& rooms) {
	std::string bCode, rmNumber;
	float amountDue, amountPaid;

	system("cls");

	std::cout << "Add New Payment\n---\n";

	std::cout << "Boarder Code: ";
	std::cin >> bCode;
	
	std::cout << "Room Number: ";
	std::cin >> rmNumber;

	std::cout << "Payment Date: \n";
	Date paymentDate;

	std::cout << "Amount Due: ";
	std::cin >> amountDue;

	std::cout << "Amount Paid: ";
	std::cin >> amountPaid;

	Assignment* a = Assignment::search(assignments, *Boarder::search(boarders, bCode), *Room::search(rooms, rmNumber));

	if (a != nullptr) {
		Payment p(*a, paymentDate, amountDue, amountPaid, 1);
		payments.push_back(p);
	}
}

void Payment::view(std::vector<Payment>& payments, Boarder& b) {
	printf("Total Received Payments from %s\n-----\n", b.getName().c_str());
	
	int count = 0;
	float totalDue = 0, totalPaid = 0;
	for (std::vector<Payment>::iterator itr = payments.begin(); itr != payments.end(); itr++) {
		Assignment& a = itr->assignment;

		if (a.getBoarder() == b) {
			printf("%d)\tDate Paid: %s\n", ++count, itr->paymentDate.toString().c_str());
			printf("\tRoom Fee:  %9.2f\n", a.getRoom().getFee());
			printf("\tPenalty:   %9.2f\n", itr->amountDue - a.getRoom().getFee());
			printf("\t--------------------\n");
			printf("\tTotal Due: %9.2f\n", itr->amountDue);
			printf("\tPayment:   %9.2f\n\n", itr->amountPaid);

			totalDue += itr->amountDue;
			totalPaid += itr->amountPaid;
		}
	}

	printf("\nOVERALL TOTAL\t\t: %.2f\n", totalDue);
	printf("TOTAL PAYMENT RECEIVED\t: %.2f\n", totalPaid);
	printf("COUNT: %d\n\n", count);

	system("pause");
}

void Payment::view(std::vector<Payment>& payments, Date& d) {
	printf("\nPayments Received for the %s of ", (d.getMonthNum() == 0) ? "Year" : "Month");
	if (d.getMonthNum() != 0) printf("%s ", d.getMonth().c_str());
	printf("%d\n\n", d.getYear());
	printf("(Payment Date / Assign Date) Boarder Name : Room #\n-----\n");

	int count = 0;
	float totalDue = 0, totalPaid = 0;
	for (std::vector<Payment>::iterator itr = payments.begin(); itr != payments.end(); itr++) {
		if (itr->paymentDate.getYear() == d.getYear() && (d.getMonthNum() == 0 || itr->paymentDate.getMonthNum() == d.getMonthNum())) {
			Assignment& a = itr->assignment;

			printf("(%s / %s) %s : %s\n", itr->paymentDate.toString().c_str(), a.getAssignDate().toString().c_str(), a.getBoarder().getName().c_str(), a.getRoom().getNumber().c_str());
			printf("\tRoom Fee:  %9.2f\n", a.getRoom().getFee());
			printf("\tPenalty:   %9.2f\n", itr->amountDue - a.getRoom().getFee());
			printf("\t--------------------\n");
			printf("\tTotal Due: %9.2f\n", itr->amountDue);
			printf("\tPayment:   %9.2f\n\n", itr->amountPaid);

			totalDue += itr->amountDue;
			totalPaid += itr->amountPaid;
			count++;
		}
	}

	printf("\nOVERALL TOTAL\t\t: %.2f\n", totalDue);
	printf("TOTAL PAYMENT RECEIVED\t: %.2f\n", totalPaid);
	printf("COUNT: %d\n\n", count);

	system("pause");
}

// readFile -> reads data for payments
void Payment::readFile(std::vector<Payment>& payments, std::string filepath, std::vector<Boarder>& boarders, std::vector<Room>& rooms, std::vector<Assignment>& assignments) {
	std::ifstream inFile;

	inFile.open(filepath);

	inFile.ignore(1000, '\n');
	while (inFile.good()) {
		std::string boarderCode, roomNumber, payDate;
		float amountDue, amountPaid;
		bool status;

		std::getline(inFile, boarderCode, ',');
		std::getline(inFile, roomNumber, ',');

		std::getline(inFile, payDate, ',');
		Date paymentDate(payDate);

		char delim;
		inFile >> amountDue >> delim >> amountPaid >> delim >> status;

		inFile.ignore(1000, '\n');

		// add to vector
		if (boarderCode != "" || roomNumber != "") {
			Assignment* a = Assignment::search(assignments, *Boarder::search(boarders, boarderCode), *Room::search(rooms, roomNumber));

			if (a != nullptr) {
				Payment p(*a, paymentDate, amountDue, amountPaid, status);
				payments.push_back(p);
			}
		}
	}
	inFile.close();
}

// writeFile -> writes the payments list data to file
void Payment::writeFile(std::vector<Payment>& payments, std::string filepath) {
	std::ofstream outFile;
	outFile.open(filepath);

	outFile << "boarder_code,roomnumber,payment_date,due_amount,amount_paid,status\n";

	for (std::vector<Payment>::iterator itr = payments.begin(); itr != payments.end(); itr++)
		outFile << itr->assignment.getBoarder().getCode() << ',' << itr->assignment.getRoom().getNumber() << ',' << itr->paymentDate.toSlashFormat() << ',' << itr->amountDue << ',' << itr->amountPaid << ',' << itr->status << '\n';
}

// display -> display payment information
void Payment::display() {
	Boarder& b = assignment.getBoarder();
	Room& r = assignment.getRoom();
	printf("%-15s%-15s%-20s%15.2f%15.2f%10s\n", b.getCode().c_str(), r.getNumber().c_str(), paymentDate.toString().c_str(), amountDue, amountPaid, getStatus().c_str());
}
