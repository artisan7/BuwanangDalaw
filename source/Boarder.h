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
	Boarder(std::string code, std::string name, Date birthDate, std::string pNumber, std::string referrer, bool status);

	// getters
	std::string getCode();
	std::string getName();
	std::string getPhoneNumber();
	Date& getBirthDate();
	bool getStatus();

	// static functions
	static void viewAll(std::vector<Boarder>& boarders);
	static Boarder* search(std::vector<Boarder>& boarders);
	static Boarder* search(std::vector<Boarder>& boarders, std::string& boarderCode);
	static void add(std::vector<Boarder>& boarders);

	static void readFile(std::vector<Boarder>& boarders, std::string filepath);
	static void writeFile(std::vector<Boarder>& boarders, std::string filepath);

	// other functions
	void display();

	// overloaded operators
	bool operator==(Boarder& other);
};
