//Header
//Defines a house

#ifndef HOUSE_HPP
#define HOUSE_HPP

#include "rectangle.hpp"
#include "filledrectangle.hpp"
#include "circle.hpp"
#include "window.hpp"
#include "line.hpp"

class house{
private:
	rectangle body, openDoor;
	filledrectangle closedDoor;
	circle window1;
	line roofLeft, roofRight;
	bool closed;
public:
	house(window & w, int start_x, int start_y, int end_x, int end_y, bool closed);
	void print();
};

#endif