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

	static std::vector<Payment> masterList;

public:
	// constructor
	Payment(Assignment& a, Date paymentDate, float amountDue, float amountPaid, bool status);
	
	// getters
	std::string getStatus();
	std::vector<Payment>& getMasterList();
	
	// static functions
	static void viewAll();
	static void add(std::vector<Assignment>& assignments, std::vector<Boarder>& boarders, std::vector<Room>& rooms);
	static void view(Boarder& b);
	static void view(Date& d);

	static void readFile(std::string filepath, std::vector<Boarder>& boarders, std::vector<Room>& rooms, std::vector<Assignment>& assignments);
	static void writeFile(std::string filepath);
	
	// other functions
	void display();
};

