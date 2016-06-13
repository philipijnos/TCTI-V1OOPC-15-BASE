#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "hwlib.hpp"
class superimage{
public:
	virtual void draw(const hwlib::location & offset = hwlib::location{0, 0}) = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual int getBodyX(const int i) = 0;
	virtual int getBodyY(const int i) = 0;
	virtual int getBodyV(const int i) = 0;
	virtual void setPixel(const int x, const int y, const int value = 0) = 0;
	virtual void setBody(const int imagebody[][3]) = 0;
};

class image: public superimage{
private:
	int width;
	int height;
	int body[][3];
public:
	image(const int w, const int h):
		width(w),
		height(h){}
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
		for(int i = 0; i<width*height; i++){
			body[i][0] = imagebody[i][0];
			body[i][1] = imagebody[i][1];
			body[i][2] = imagebody[i][2];
		}
	}
};

class invertdecorator : public superimage{
private:
	superimage & slave;
public:
	invertdecorator(superimage & slave):
		slave(slave){}
	int getHeight(){
		return slave.getHeight();
	}
	int getWidth(){
		return slave.getWidth();
	}
	int getBodyX(const int i){
		return slave.getBodyX(i);
	}
	int getBodyY(const int i){
		return slave.getBodyY(i);
	}
	int getBodyV(const int i){
		if(slave.getBodyV(i)){
			return 0;
		}
		else{
			return 1;
		}
	}
	void setPixel(const int x, const int y, const int value = 0){
		if(value){
			slave.setPixel(x, y, 0);
		}
		else{
			slave.setPixel(x, y, 1);
		}
	}
	void setBody(const int imagebody[][3]){
		int pixelAmount = slave.getWidth()*slave.getHeight();
		int tempbody[pixelAmount][3] = {};
		for(int i = 0; i<pixelAmount; i++){
			tempbody[i][0] = imagebody[i][0];
			tempbody[i][1] = imagebody[i][1];
			if(imagebody[i][2]){
				tempbody[i][2] = 0;
			}
			else{
				tempbody[i][2] = 1;
			}
		}
		slave.setBody(tempbody);
	}
	void draw(const hwlib::location & offset = hwlib::location{0, 0}){
		slave.draw(offset);
	}
};

class imagepart : public superimage{
private:
	superimage & slave;
	int width;
	int height;
public:
	imagepart(superimage & slave, const int width, const int height):
		slave(slave), width(width), height(height){}
	int getHeight(){
		return height;
	}
	int getWidth(){
		return width;
	}
	int getBodyX(const int i){
		return slave.getBodyX(i);
	}
	int getBodyY(const int i){
		return slave.getBodyY(i);
	}
	int getBodyV(const int i){
		return slave.getBodyV(i);
	}
	void setPixel(const int x, const int y, const int value = 0){
		slave.setPixel(x, y, value);
	}
	void setBody(const int imagebody[][3]){
		int tempbody[height*width][3] = {};
		int counter = 0;
		hwlib::cout << slave.getWidth() << "," << slave.getHeight() << "\n";
		hwlib::cout << width << "," << height << "\n";
		for(int i = 0; i < slave.getHeight()*slave.getWidth(); i++){
			if(imagebody[i][0] < width && imagebody[i][1] < height){
				tempbody[counter][0] = imagebody[i][0];
				tempbody[counter][1] = imagebody[i][1];
				tempbody[counter][2] = imagebody[i][2];
				counter++;
			}
		}
		slave.setBody(tempbody);
	}
	void draw(const hwlib::location & offset = hwlib::location{0, 0}){
		slave.draw(offset);
	}
};
#endif //IMAGE_HPP