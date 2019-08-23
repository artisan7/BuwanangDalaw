#pragma once

#include <string>
#include <vector>

#include "Date.h"

class Assignment
{
private:
	std::string boarderCode;
	std::string roomNumber;
	Date assignDate;
	bool status;

public:
	// constructor
	Assignment(std::string bCode, std::string rmNumber, Date assignDate, bool status);
	
	// getters
	std::string getStatus();
	
	// static functions
	static void viewAll(std::vector<Assignment>& assignList);
	
	// other functions
	void display();
	
};

