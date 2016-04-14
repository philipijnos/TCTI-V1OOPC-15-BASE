// example:
// declaration of a filled rectangle object

#ifndef FILLEDRECTANGLE_HPP
#define FILLEDRECTANGLE_HPP

#include "window.hpp"

class filledrectangle {
private:
   int p_start_x;
   int p_start_y;
   int p_end_x;
   int p_end_y;
   window & w;
public:
   filledrectangle( window & w, int p_start_x, int p_start_y, int p_end_x, int p_end_y ):
		p_start_x(p_start_x);
		p_start_y(p_start_y);
		p_end_x(p_end_x);
		p_end_y(p_end_y);
		w(w);
	{}
   void print();
};


#endif // FILLEDRECTANGLE_HPP
