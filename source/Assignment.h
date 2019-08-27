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

	static std::vector<Assignment> masterList;

public:
	// constructor
	Assignment(Boarder& b, Room& r, House& h, Date assignDate, bool status);
	
	// getters
	Room& getRoom();
	House& getHouse();
	Date& getAssignDate();
	Boarder& getBoarder();
	bool getStatus();
	static std::vector<Assignment>& getMasterList();
	
	// static functions
	static void add(Boarder& boarder, Room& room, House& house);
	static Assignment* search(Boarder& b, Room& r);
	static void viewAll();
	static void viewActive();
	static void viewActive(House& h);

	static void readFile(std::string filepath, std::vector<House>& houses, std::vector<Boarder>& boarders, std::vector<Room>& rooms);
	static void writeFile(std::string filepath);
	
	// other functions
	void display();
	
};

