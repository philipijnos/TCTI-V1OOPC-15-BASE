// example:
// definition of the functions of a filled rectangle object

#include "filledrectangle.hpp"

<<<<<<< HEAD
// filledrectangle::filledrectangle( window & w, int p_start_x, int p_start_y, int p_end_x, int p_end_y ):
//{}

void filledrectangle::draw()
{
    int x0 = p_start_x;
    int x1 = p_end_x;
    int y0 = p_start_y;
    int y1 = p_end_y;

    int length = x1 - x0;
    int width = y1 - y0;

    if(length > 0) {
		for(int i = x0; i < x1; i++) {
			if(width > 0) {
				for(int j = y0; j < y1; j++) {
					w.draw(i, j);
				}
			}
			else{
				for(int j = y1; j < y0; j++) {
					w.draw(i, j);
				}
			}
		}
    }
	else{
		for(int i = x1; i < x0; i++) {
			if(width > 0) {
				for(int j = y0; j < y1; j++) {
					w.draw(i, j);
				}
			}
			else{
				for(int j = y1; j < y0; j++) {
					w.draw(i, j);
				}
			}
		}
	}
=======
filledrectangle::filledrectangle( window & w, int p_start_x, int p_start_y, int p_end_x, int p_end_y ):
{}

void filledrectangle::draw(){
	
>>>>>>> 513fa1437ce4d27f8aa01ce9002c36e4f0ae628c
}