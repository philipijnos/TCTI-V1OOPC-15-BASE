#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "hwlib.hpp"
namespace image{

class image{
private:
	int width;
	int height;
	int pixelAmount;
	hwlib::location body[];
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
	void setPixel(const hwlib::location & pixel, const int value);
	void setBody(const hwlib::location imagebody[]);
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
			temp.x = body[i].x + offset.x;
			temp.y = body[i].y + offset.y;
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
	int image::getPixelAmount(){
		return pixelAmount;
	}
	int image::getWidth(){
		return width;
	}
	void image::setBody(const hwlib::location imagebody[]){
		for(int i = 0; i<pixelAmount; i++){
			body[i] = imagebody[i];
		}
	}
	void image::invert(){
		int invertedPixelAmount = width * height - pixelAmount;
		int dummyIncrement = 0;
		hwlib::location tempbody[pixelAmount] = hwlib::location{0, 0};
		for(int n = 0; n<pixelAmount; n++){
			tempbody[n] = body[n];
		}
		for(int i = 0; i<width; i++){
			for(int j = 0; j<height; j++){
				bool dummyControl = false;
				for(int p = 0; p<pixelAmount; p++){
					if(tempbody[p].x == i && tempbody[p].y == j){
						dummyControl = true;
					}
				}
				if(!dummyControl){
					body[dummyIncrement] = hwlib::location{i, j};
					dummyIncrement++;
				}
			}
		}
		pixelAmount = invertedPixelAmount;
	}
}
#endif 