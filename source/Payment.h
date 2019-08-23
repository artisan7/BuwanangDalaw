#pragma once

#include <string>
#include <vector>

#include "Date.h"

class Payment
{
private:
	std::string boarderCode;
	std::string roomNumber;
	Date paymentDate;
	float amountDue;
	float amountPaid;
	bool status;
public:
	// constructor
	Payment(std::string bCode, std::string rmNumber, Date paymentDate, float amountDue, float amountPaid, bool status);
	
	// getters
	std::string getStatus();
	
	// static functions
	static void viewAll(std::vector<Payment>& record);
	
	// other functions
	void display();
};

