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
	image(const int & width, const int & height, const int & pixels, const hwlib::location imagebody[]):
		width(width),
		height(height),
		pixels(pixels){
			for(int i = 0; i<pixels; i++){
				body[i] = imagebody[i];
			}
		}
	void draw();
	image scale(const image & input, const int s);
	
};
}
#endif 