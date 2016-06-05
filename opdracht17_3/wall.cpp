#include "wall.hpp"

wall::wall(window & w, const vector & location, const vector & end, vector bounce):
	rectangle(w, location, end, bounce),
	start(location),
	end(end),
	filled(true)
	{}

void wall::update(){
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