//=================================================================================
//			ImageShower library
//
//          Copyright Philippe Zwietering 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
//=================================================================================
/// @file

#ifndef IMAGE_HPP
#define IMAGE_HPP
/// This library converts array consisting of an x- and y-coordinate and a pixel value to a displayable image on an OLED-display.
/// The array can be automatically generated through the Python script "bmpconverter.py", which only works for bitmap images of 1, 4 or 8 bits.
/// Furthermore, this library wasn't designed to check if everything is put in correctly.
/// If there is any incorrect input, this library will not work and it won't give any sophisticated error messages.
/// There are also two decorators implemented in this library, one which inverts images and the other one crops images.
/// For more functionality, one can add easily add their own decorator.

/// This library needs the hwlib library and is only tested on an Arduino DUE and OLED display.
/// This library thus might not work on other platforms the hwlib library still works on.
#include "hwlib.hpp"

/// superimage interface
//
/// This class implements an interface for all basic functions one would want to use on images.
/// I have decided one only wants to ever read images, and therefore not setters are implemented.
/// Ofcourse this can always still be implemented, if need be.
class superimage{
public:
	/// draw image
	//
	/// This function draws an image at a certain offset, which is automatically in the upper left corner of the screen.
	/// To use this, the SDA and SCL pins of the OLED display have to be connected to the SDA and SCL pins of the Arduino respectively.
	virtual void draw(const hwlib::location & offset = hwlib::location{0, 0}) = 0;
	/// gets width
	//
	/// This function returns the width of an image in pixels.
	virtual int getWidth() = 0;
	/// gets height
	//
	/// This function returns the height on image in pixels.
	virtual int getHeight() = 0;
	/// gets x-coordinate image array
	//
	/// This function returns the x-coordinate of an image array of the ith space in the array.
	virtual int getBodyX(const int i) = 0;
	/// gets y-coordinate image array
	//
	/// This function returns the y-coordinate of an image array of the ith space in the array.
	virtual int getBodyY(const int i) = 0;
	/// gets pixel value image array
	//
	/// This function returns the pixel value of an image array of the ith space in the array.
	virtual int getBodyV(const int i) = 0;
};
/// image class
//
/// This class implements an image class which can be used to define and describe image classes.
/// This class inherits from the superimage superclass.
class image: public superimage{
private:
	int width;
	int height;
	int (*body)[3];
public:
	/// image constructor
	//
	/// This constructor defines an image.
	/// The image constructor needs a width, a height and an array of 1-dimensional arrays which consist of
	/// a x- and y-coordinate and a value of 1 or 0 which is the value of the pixel the coordinates define.
	/// The order in which the pixels are put in the array doesn't matter.
	image(const int w, const int h, int (*b)[3]):
		width(w),
		height(h),
		body(b){}
		
	/// draw function normal image
	//
	/// This function clears the screen and draws an image at a certain offset.
	/// This means that this library doesn't yet support multiple images to be drawn at the same moment.
	/// The reason being that when a hwlib::glcd_oled object is given to the function as a parameter, images are drawn distorted.
	/// This is still to be fixed.
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
	/// get width
	//
	/// Returns the width of an image.
	int getWidth(){
		return width;
	}
	/// get height
	//
	/// Returns the height of an image.
	int getHeight(){
		return height;
	}
	/// get x-coordinate image array
	//
	/// Returns the ith x-coordinate of an image array.
	int getBodyX(const int i){
		return body[i][0];
	}
	/// get y-coordinate image array
	//
	/// Returns the ith y-coordinate of an image array.
	int getBodyY(const int i){
		return body[i][1];
	}
	/// get pixel value image array
	//
	/// Returns the ith pixel value of an image array.
	int getBodyV(const int i){
		return body[i][2];
	}
};
/// invert decorator
//
/// This class implements an image inverting decorator.
class invert : public superimage{
private:
	superimage & slave;
public:
	/// invert constructor
	//
	/// This constructor constructs a invert decorated image from a superimage object.
	invert(superimage & slave):
		slave(slave){}
	/// gets height
	//
	/// Returns the height of an inverted image.
	int getHeight() override {
		return slave.getHeight();
	}
	/// gets width
	//
	/// Returns the width of an inverted image.
	int getWidth() override {
		return slave.getWidth();
	}
	/// gets x-coordinate image array
	//
	/// Returns the ith x-coordinate of an inverted image array.
	int getBodyX(const int i) override {
		return slave.getBodyX(i);
	}
	/// gets y-coordinate image array
	//
	/// Returns the ith y-coordinate of an inverted image array.
	int getBodyY(const int i) override {
		return slave.getBodyY(i);
	}
	/// gets pixel value image array
	//
	/// Returns the ith pixel value of an inverted image array.
	int getBodyV(const int i) override {
		if(slave.getBodyV(i)){
			return 0;
		}
		else{
			return 1;
		}
	}
	/// draws inverted image
	//
	/// This functions clears the display and invertedly draws an image through the SDA and SCL pins.
	/// It begins drawing at a certain offset.
	void draw(const hwlib::location & offset = hwlib::location{0, 0}) override {
		auto scl = hwlib::target::pin_oc{ hwlib::target::pins::scl };
		auto sda = hwlib::target::pin_oc{ hwlib::target::pins::sda };
		auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda{ scl, sda };
		auto display = hwlib::glcd_oled{i2c_bus, 0x3c };
		display.clear();
		for(int i = 0; i<(slave.getWidth()*slave.getHeight()); i++){
			hwlib::location temp(0, 0);
			if(!slave.getBodyV(i)){
				temp.x = slave.getBodyX(i) + offset.x;
				temp.y = slave.getBodyY(i) + offset.y;
				display.write(temp);
			}
		}
	}
};
/// imagepart decorator
//
/// This imagepart class implements an image cropping decorator and inherits from the superimage class.
class imagepart : public superimage{
private:
	superimage & slave;
	int width;
	int height;
	int widthOffset;
	int heightOffset;
public:
	/// imagepart constructor
	//
	/// This imagepart constructor makes a cropped image.
	/// The width and height are the distance to the most bottomright pixel that still needs to be in the image.
	/// The widthOffset and heightOffset are the most upperleft pixel that still need to be in the image, and are automatically 0.
	imagepart(superimage & slave, const int width, const int height, const int widthOffset = 0, const int heightOffset = 0):
		slave(slave), width(width), height(height), widthOffset(widthOffset), heightOffset(heightOffset){}
	/// gets height
	//
	/// Returns the height of a cropped image.
	int getHeight() override {
		return height-heightOffset;
	}
	/// gets width
	//
	/// Returns the width of a cropped image.
	int getWidth() override {
		return width-widthOffset;
	}
	/// gets x-coordinate image array
	//
	/// Returns the ith x-coordinate of a cropped image.
	/// If it doesn't fit in the cropped image, returns 0.
	int getBodyX(const int i) override {
		if(slave.getBodyX(i) < width && slave.getBodyX(i) > widthOffset){
			return slave.getBodyX(i);
		}
		else{
			return 0;
		}
	}
	/// gets y-coordinate image array
	//
	/// Returns the ith y-coordinate of a cropped image.
	/// If it doesn't fit in the cropped image, returns 0.
	int getBodyY(const int i) override {
		if(slave.getBodyY(i) < height && slave.getBodyY(i) > heightOffset){
			return slave.getBodyY(i);
		}
		else{
			return 0;
		}
	}
	/// gets pixel value image array
	//
	/// Returns the ith pixel value of a cropped image.
	/// If it doesn't fit in the cropped image, returns 0.
	int getBodyV(const int i) override {
		if(slave.getBodyX(i) < width && slave.getBodyY(i) < height && slave.getBodyX(i) > widthOffset && slave.getBodyY(i) > heightOffset){
			return slave.getBodyV(i);
		}
		else{
			return 0;
		}
	}
	/// draws cropped image
	//
	/// This functions clears the display and draws a cropped image through the SDA and SCL pins.
	/// It begins drawing at the offset.
	void draw(const hwlib::location & offset = hwlib::location{0, 0}) override {
		auto scl = hwlib::target::pin_oc{ hwlib::target::pins::scl };
		auto sda = hwlib::target::pin_oc{ hwlib::target::pins::sda };
		auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda{ scl, sda };
		auto display = hwlib::glcd_oled{i2c_bus, 0x3c };
		display.clear();
		for(int i = 0; i<(slave.getWidth()*slave.getHeight()); i++){
			hwlib::location temp(0, 0);
			if(slave.getBodyV(i) && slave.getBodyX(i) < width && slave.getBodyY(i) < height && slave.getBodyX(i) > widthOffset && slave.getBodyY(i) > heightOffset){
				temp.x = slave.getBodyX(i) + offset.x;
				temp.y = slave.getBodyY(i) + offset.y;
				display.write(temp);
			}
		}
	}
};
#endif //IMAGE_HPP