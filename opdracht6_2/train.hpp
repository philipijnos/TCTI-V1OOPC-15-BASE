//Header
//Defines a train

#IFNDEF TRAIN_HPP
#DEFINE TRAIN_HPP

#include "window.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "line.hpp"

class train{
private:
	rectangle body;
	circle frontwheel, rearwheel;
	line connection;
	int length;
public:
	train(window & w, int length, int start_x, int start_y);
	void print();
};
#ENDIF