#include "wall.hpp"

wall::wall(window & w, const vector & location, const vector & end, const int & interval_update):
	rectangle(w, location, end),
	filled(true),
	update_interval(interval_update),
	update_count(0)
	{}

void wall::update(){
	update_count++;
	if(filled){
		filled = false;
	}
	else{
		filled = true;
	}
}

void wall::draw(){

}