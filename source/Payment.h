#pragma once

#include <string>
#include <vector>

#include "Assignment.h"
#include "Boarder.h"
#include "Room.h"
#include "Date.h"

class Payment
{
private:
	Boarder boarder;
	Room room;
	Date paymentDate;
	float amountDue;
	float amountPaid;
	bool status;
public:
	// constructor
	Payment(Boarder& b, Room& r, Date paymentDate, float amountDue, float amountPaid, bool status);
	
	// getters
	std::string getStatus();
	
	// static functions
	static void viewAll(std::vector<Payment>& record);
	static void add(std::vector<Payment>& payments, std::vector<Assignment>& assignments);
	static void view(std::vector<Payment>& record, Boarder& b);
	static void view(std::vector<Payment>& record, int year, int month=0);
	
	// other functions
	void display();
};

