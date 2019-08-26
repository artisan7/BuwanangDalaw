#pragma once

#include <string>
#include <vector>

#include "Boarder.h"
#include "House.h"
#include "Room.h"
#include "Date.h"

class Assignment
{
private:
	Boarder boarder;
	Room room;
	House house;

	Date assignDate;
	bool status;

public:
	// constructor
	Assignment(Boarder& b, Room& r, House& h, Date assignDate, bool status);
	
	// getters
	Room& getRoom();
	House& getHouse();
	Date& getAssignDate();
	Boarder& getBoarder();
	bool getStatus();
	
	// static functions
	static void add(std::vector<Assignment>& assignments, Boarder& boarder, Room& room, House& house);
	static Assignment* search(std::vector<Assignment>& assignments, Boarder& b, Room& r);
	static void viewAll(std::vector<Assignment>& assignments);
	static void viewActive(std::vector<Assignment>& assignments);
	static void viewActive(std::vector<Assignment>& assignments, House& h);

	static void readFile(std::vector<Assignment>& assignments, std::string filepath, std::vector<House>& houses, std::vector<Boarder>& boarders, std::vector<Room>& rooms);
	static void writeFile(std::vector<Assignment>& assignments, std::string filepath);
	
	// other functions
	void display();
	
};

