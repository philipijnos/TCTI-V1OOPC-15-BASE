#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "hwlib.hpp"
namespace image{

class image{
private:
	int width;
	int height;
	int pixels;
	hwlib::location body[];
public:
	image(const int width, const int height, const int pixels, const hwlib::location imagebody[]):
		width(width),
		height(height),
		pixels(pixels){
			for(int i = 0; i<pixels; i++){
				body[i].x = imagebody[i].x;
				body[i].y = imagebody[i].y;
			}
		}
	void draw(const hwlib::location & offset = hwlib::location{0, 0}){
		auto scl = hwlib::target::pin_oc{ hwlib::target::pins::scl };
		auto sda = hwlib::target::pin_oc{ hwlib::target::pins::sda };
		auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda{ scl, sda };
		auto display = hwlib::glcd_oled{i2c_bus, 0x3c };
		display.clear();
		for(int i = 0; i<pixels; i++){
			hwlib::location temp(0, 0);
			temp.x = body[i].x + offset.x;
			temp.y = body[i].y + offset.y;
			display.write(temp);
		}
	}
	void enlarge(const int s);
	void widen(const int s);
	void heighten(const int s);
	int getWidth(){
		return width;
	}
	int getHeight(){
		return height;
	}
	int getPixels(){
		return pixels;
	}
	void setPixel(const hwlib::location & pixel, const int value);
	void invert();
};
}
#endif 