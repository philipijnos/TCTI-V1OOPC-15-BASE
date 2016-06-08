#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "hwlib.hpp"
namespace image{

class image{
private:
	int width;
	int height;
	int body[][3];
public:
	image(const int width, const int height):
		width(width),
		height(height){}
	void draw(const hwlib::location & offset = hwlib::location{0, 0}) override;
	void enlarge(const int s);
	void widen(const int s);
	void heighten(const int s);
	int getWidth();
	int getHeight();
	void setPixel(const int value);
	void setBody(const int imagebody[][3]);
	void invert();
};

	void image::draw(const hwlib::location & offset){
		auto scl = hwlib::target::pin_oc{ hwlib::target::pins::scl };
		auto sda = hwlib::target::pin_oc{ hwlib::target::pins::sda };
		auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda{ scl, sda };
		auto display = hwlib::glcd_oled{i2c_bus, 0x3c };
		display.clear();
		for(int i = 0; i<(width*height); i++){
			hwlib::location temp(0, 0);
			if(body[i][2]){
				temp.x = body[i][0] + offset.x;
				temp.y = body[i][1]+ offset.y;
				display.write(temp);
			}
		}
	}
//	void image::enlarge(const int s){
//		for(int i = 0; i < pixelAmount; i++){
//			auto tempx = body[i].x;
//			auto tempy = body[i].y;
//			
//		}
//		height *= s;
//		width *= s;
//		pixelAmount *= s*s;
//	}
	int image::getHeight(){
		return height;
	}
	int image::getWidth(){
		return width;
	}
	void image::setBody(const int imagebody[][3]){
		for(int i = 0; i<(width*height); i++){
			body[i][0] = imagebody[i][0];
			body[i][1] = imagebody[i][1];
			body[i][2] = imagebody[i][2];
		}
	}
}
#endif 