//Defines a train and how to draw it

#include "train.hpp"

train::train(window & w, int length, int start_x, int start_y):
	body(w, start_x, start_y, start_x+50, start_y+30), 
	frontwheel(w, start_x+15, start_y+30, 10),
	rearwheel(w, start_x+35, start_y+30, 10), 
	