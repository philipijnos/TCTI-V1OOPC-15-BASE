//Defines a house and the function to draw it

#include "house.hpp"

house::house(window & w, int start_x, int start_y, int end_x, int end_y, bool closed):
	body(w, start_x, start_y, end_x, end_y),
	openDoor(w, start_x, start_y, (3*start_x+end_x)/4, (start_y+3*end_y)/4),
	closedDoor(w, start_x, start_y, (3*start_x+end_x)/4, (start_y+3*end_y)/4),
	window1(w, (start_x+3*end_x)/4, (start_y+end_y)/2, (end_y-start_y)/3),
	roofLeft(w, start_x, end_y, (start_x+end_x)/2, end_y+(end_x-start_x)/2),
	roofRight(w, end_x, end_y, (start_x+end_x)/2, end_y+(end_x-start_x)/2),
	closed(closed)
{}

void house::print(){
	body.print();
	if(closed){
		closedDoor.draw();
	}
	else{
		openDoor.print();
	}
	window1.print();
	roofLeft.print();
	roofRight.print();
}