#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "hwlib.hpp"
namespace image{

class image{
private:
	int width;
	int height;
	int pixelAmount;
	int body[][2];
public:
	image(const int width, const int height, const int pixelAmount):
		width(width),
		height(height),
		pixelAmount(pixelAmount){}
	void draw(const hwlib::location & offset = hwlib::location{0, 0});
	void enlarge(const int s);
	void widen(const int s);
	void heighten(const int s);
	int getWidth();
	int getHeight();
	int getPixelAmount();
	void setPixel(const int value);
	void setBody(const int imagebody[][2]);
	void invert();
};

	void image::draw(const hwlib::location & offset){
		auto scl = hwlib::target::pin_oc{ hwlib::target::pins::scl };
		auto sda = hwlib::target::pin_oc{ hwlib::target::pins::sda };
		auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda{ scl, sda };
		auto display = hwlib::glcd_oled{i2c_bus, 0x3c };
		display.clear();
		for(int i = 0; i<pixelAmount; i++){
			hwlib::location temp(0, 0);
			temp.x = body[i][0] + offset.x;
			temp.y = body[i][1]+ offset.y;
			display.write(temp);
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
	int image::getPixelAmount(){
		return pixelAmount;
	}
	void image::setBody(const int imagebody[][2]){
		for(int i = 0; i<pixelAmount; i++){
			body[i][0] = imagebody[i][0];
			body[i][1] = imagebody[i][1];
		}
	}
}
#endif 