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
	bool status;		// (0) inactive (1) active

	static std::vector<Boarder> masterList;

public:
	Boarder(std::string code, std::string name, Date birthDate, std::string pNumber, std::string referrer, bool status);

	// getters
	std::string getCode();
	std::string getName();
	std::string getPhoneNumber();
	Date& getBirthDate();
	bool getStatus();
	static std::vector<Boarder>& getMasterList();

	// setters
	void setStatus(bool status);

	// static functions
	static void add();
	static Boarder* search();
	static Boarder* search(std::string& boarderCode);
	static void viewAll();

	static void readFile(std::string filepath);
	static void writeFile(std::string filepath);

	// other functions
	void display();

	// overloaded operators
	bool operator==(Boarder& other);
};
