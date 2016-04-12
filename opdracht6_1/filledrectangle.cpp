// example:
// definition of the functions of a filled rectangle object

#include "filledrectangle.hpp"

filledrectangle::filledrectangle( window & w, int start_x, int start_y, int end_x, int end_y ):
   left( w, start_x, start_y, start_x, end_y ),
   right( w, end_x, start_y, end_x, end_y ),
   top( w, start_x, start_y, end_x, start_y ),
   bottom( w, start_x, end_y, end_x, end_y )
{}

void filledrectangle::print(){
   left.print();
   right.print();
   top.print();
   bottom.print();
}

