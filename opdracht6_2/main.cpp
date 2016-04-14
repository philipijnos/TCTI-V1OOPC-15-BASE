// template

#include <iostream>

#include "window.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "filledrectangle.hpp"
#include "house.hpp"

int main(int argc, char **argv){
   window w( 128, 64, 2 );
   
   house openHouse( w, 0, 0, 30, 20, true );
   openHouse.print();
   
   return 0;
}
