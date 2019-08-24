#pragma once

#include <string>
#include <vector>

#include "Date.h"

class Boarder {
private:
	std::string code;
	std::string name;
	std::string phoneNumber;
	std::string referrer;
	Date birthDate;
	bool status;

public:
	Boarder(std::string code, std::string name, Date bDate, std::string pNumber, std::string referrer, bool status);

	// getters
	std::string getStatus();

	// static functions
	static void viewAll(std::vector<Boarder>& boarders);
	static Boarder* search(std::vector<Boarder>& boarders, std::string& boarderCode);

	// other functions
	void display();
};
