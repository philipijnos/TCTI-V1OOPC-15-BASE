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
};

class image: public superimage{
private:
	int width;
	int height;
	int (*body)[3];
public:
	image(const int w, const int h, int (*b)[3]):
		width(w),
		height(h),
		body(b){}
		
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
				temp.y = body[i][1] + offset.y;
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
};

class invertdecorator : public superimage{
private:
	superimage & slave;
public:
	invertdecorator(superimage & slave):
		slave(slave){}
	int getHeight() override {
		return slave.getHeight();
	}
	int getWidth() override {
		return slave.getWidth();
	}
	int getBodyX(const int i) override {
		return slave.getBodyX(i);
	}
	int getBodyY(const int i) override {
		return slave.getBodyY(i);
	}
	int getBodyV(const int i) override {
		if(slave.getBodyV(i)){
			return 0;
		}
		else{
			return 1;
		}
	}
	void draw(const hwlib::location & offset = hwlib::location{0, 0}) override {
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
	int getHeight() override {
		return height;
	}
	int getWidth() override {
		return width;
	}
	int getBodyX(const int i) override {
		return slave.getBodyX(i);
	}
	int getBodyY(const int i) override {
		return slave.getBodyY(i);
	}
	int getBodyV(const int i) override {
		return slave.getBodyV(i);
	}
	void draw(const hwlib::location & offset = hwlib::location{0, 0}) override {
		slave.draw(offset);
	}
};
#endif //IMAGE_HPP