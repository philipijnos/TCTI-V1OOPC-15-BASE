#include "victim.hpp"

victim::victim(window & w, const vector & start, const vector & end, vector bounce):
	start(start),
	end(end),
	rectangle(w, start, end, bounce){}

void victim::draw(){
	rectangle::draw();
}

void interact(drawable & other){		//Ik wist niet hoe ik dit aan moest pakken, eerlijk gezegd had de opdracht vanaf het begin ook een stuk duidelijker gekund.
	if(this != & other){
		if(overlaps(other)){
			start+= vector(1, 1);
			end-= vector(1, 1);
		}
	}
}