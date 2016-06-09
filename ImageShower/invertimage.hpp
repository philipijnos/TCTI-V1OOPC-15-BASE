#ifndef SUPERIMAGE_HPP
#define SUPERIMAGE_HPP

class decorator : public superimage{
private:
	superimage *super;
public:
	decorator(superimage * s):
		super(s){}
	void draw(const hwlib::location & offset = hwlib::location{0, 0}){
		super -> draw(offset);
	}
	int getWidth(){
		return super -> getWidth();
	}
	int getHeight(){
		return super -> getHeight();
	}
	void setPixel(const int x, const int y, const int value = 0){
		super -> setPixel(x, y, value);
	}
	void setBody(const int imagebody[][3]){
		super -> setBody(imagebody);
	}
	int getBodyX(const int i){
		return super -> getBodyX(i);
	}
	int getBodyY(const int i){
		return super -> getBodyY(i);
	}
	int getBodyV(const int i){
		return super -> getBodyV(i);
	}
};

class invertdec : public decorator{
public:
	invertdec(superimage * sup):
		decorator(sup){}
	int getHeight(){
		return decorator::getHeight();
	}
	int getWidth(){
		return decorator::getWidth();
	}
	int getBodyX(const int i){
		return decorator::getBodyX(i);
	}
	int getBodyY(const int i){
		return decorator::getBodyY(i);
	}
	int getBodyV(const int i){
		if(decorator::getBodyV(i)){
			return 0;
		}
		else{
			return 1;
		}
	}
	void setPixel(const int x, const int y, const int value = 0){
		if(value){
			decorator::setPixel(x, y, 0);
		}
		else{
			decorator::setPixel(x, y, 1);
		}
	}
	void setBody(const int imagebody[][3]){
		int pixelAmount = decorator::getWidth()*decorator::getHeight();
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
		decorator::setBody(tempbody);
	}
//	void draw(const hwlib::location & offset = hwlib::location{0, 0}){
//		
//	}
};
#endif //SUPERIMAGE_HPP