#ifndef INVERTIMAGE_HPP
#define INVERTIMAGE_HPP

#include "hwlib.hpp"
#include "image.hpp"
namespace image{

class invertImage : public image{
private:
	image img;
public:
	invertImage(const image & img):
		img(img){}
	void draw(const hwlib::location & offset = hwlib::location{0, 0}) override;
};
	void image::draw(const hwlib::location & offset){
		auto scl = hwlib::target::pin_oc{ hwlib::target::pins::scl };
		auto sda = hwlib::target::pin_oc{ hwlib::target::pins::sda };
		auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda{ scl, sda };
		auto display = hwlib::glcd_oled{i2c_bus, 0x3c };
		display.clear();
		for(int i = 0; i<(img.width*img.height); i++){
			hwlib::location temp(0, 0);
			if(!img.body[i][2]){
				temp.x = img.body[i][0] + offset.x;
				temp.y = img.body[i][1]+ offset.y;
				display.write(temp);
			}
		}
	}
}
#endif //INVERTIMAGE_HPP