#include "wall.hpp"

wall::wall(window & w, const vector & location, const vector & end):
	rectangle(w, location, end),
	start(location),
	end(end),
	filled(true),
	update_count(0)
	{}

void wall::update(){
	update_count++;
	filled = !filled;
}

void wall::draw(){
	rectangle::draw();
	
	if(filled){
		vector v = start;
		for(; v.x < end.x; v.x++){
			v.y = start.y;
			for(; v.y < end.y; v.y++){
				w.draw(v);
			}
		}
	}
}