#pragma once

#include <string>
#include <vector>

#include "Assignment.h"
#include "Date.h"

class Payment
{
private:
	Assignment& assignment;
	Date paymentDate;
	float amountDue;
	float amountPaid;
	bool status;
public:
	// constructor
	Payment(Assignment& a, Date paymentDate, float amountDue, float amountPaid, bool status);
	
	// getters
	std::string getStatus();
	
	// static functions
	static void viewAll(std::vector<Payment>& record);
	static void add(std::vector<Payment>& payments, std::vector<Assignment>& assignments, std::vector<Boarder>& boarders, std::vector<Room>& rooms);
	static void view(std::vector<Payment>& record, Boarder& b);
	static void view(std::vector<Payment>& record, Date& d);

	static void readFile(std::vector<Payment>& payments, std::string filepath, std::vector<Boarder>& boarders, std::vector<Room>& rooms, std::vector<Assignment>& assignments);
	static void writeFile(std::vector<Payment>& payments, std::string filepath);
	
	// other functions
	void display();
};

