#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "hwlib.hpp"
#include "superImage.hpp"

class image : public superimage{
private:
	int width;
	int height;
	int body[][3];
public:
	image(const int w, const int h){
		width = w;
		height = h;
	}
	image(const image & img){
		width = img.width;
		height = img.height;
		for(int i = 0; i<(width*height); i++){
			body[i][0] = img.body[i][0];
			body[i][1] = img.body[i][1];
			body[i][2] = img.body[i][2];
		}
	}
	void draw(const hwlib::location & offset = hwlib::location{0, 0}){
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
	int getWidth(){
		return width;
	}
	int getHeight(){
		return height;
	}
	int getBodyX(const int i){
		return body[i][0];
	}
	int getBodyY(const int i){
		return body[i][1];
	}
	int getBodyV(const int i){
		return body[i][2];
	}
	void setPixel(const int x, const int y, const int value = 0){
		if(x >= width || y >= height){
			return;
		}
		for(int i = 0; i<width*height; i++){
			if(body[i][0] == x && body[i][1]){
				body[i][2] = value;
				return;
			}
		}
	}
	void setBody(const int imagebody[][3]){
			for(int i = 0; i<(width*height); i++){
			body[i][0] = imagebody[i][0];
			body[i][1] = imagebody[i][1];
			body[i][2] = imagebody[i][2];
		}
	}
};

#endif //IMAGE_HPP