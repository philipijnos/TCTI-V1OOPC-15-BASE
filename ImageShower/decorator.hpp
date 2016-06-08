#ifndef INVERTIMAGE_HPP
#define INVERTIMAGE_HPP

#include "hwlib.hpp"
#include "image.hpp"
#include "superImage.hpp"

class decorator : public superimage{
private:
	superimage * dec;
public:
	decorator(superimage * d){
		dec = d;
	}
	void draw(const hwlib::location & offset = hwlib::location{0, 0}){
		dec-> draw();
	}
};
#endif //INVERTIMAGE_HPP