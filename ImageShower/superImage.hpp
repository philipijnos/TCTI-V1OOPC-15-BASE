#ifndef SUPERIMAGE_HPP
#define SUPERIMAGE_HPP

class superimage{
public:
	virtual void draw() = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual void setPixel() = 0;
	virtual int getPixel() = 0;
	virtual void setBody() = 0;
	virtual int getBodyX() = 0;
	virtual int getBodyY() = 0;
	virtual int getBodyV() = 0;
};
#endif //SUPERIMAGE_HPP