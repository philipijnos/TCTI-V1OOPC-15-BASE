//Prints a filled rectangle

#include <iostream>

#include "window.hpp"
#include "filledrectangle.hpp"

int main(int argc, char **argv){
   window w( 128, 64, 2 );
   
   filledrectangle box( w, 20, 10, 30, 20 );
   box.print();
   
   return 0;
}
