#include "hwlib.hpp"

int main( void ){	
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   auto led0 = hwlib::target::pin_out( hwlib::target::pins::d7 );
   auto led1 = hwlib::target::pin_out( hwlib::target::pins::d6 );
   auto led2 = hwlib::target::pin_out( hwlib::target::pins::d5 );
   auto led3 = hwlib::target::pin_out( hwlib::target::pins::d4 );
   
   while(true){
	   led3.set(0); led1.set(1); hwlib::wait_ms(300);
	   led0.set(0); led2.set(1); hwlib::wait_ms(300);
	   led1.set(0); led3.set(1); hwlib::wait_ms(300);
	   led2.set(0); led0.set(1); hwlib::wait_ms(300);
   }
}