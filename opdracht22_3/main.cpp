#include "hwlib.hpp"

void moreless( hwlib::port_out & leds, hwlib::target::pin_in & switchmore, hwlib::target::pin_in & switchless){
	int n = 0;
	while(true){
		if(!switchmore.get() && n<4){
			n++;
			hwlib::wait_ms(200);
			hwlib::cout << n;
		}
		if(!switchless.get() && n>0){
			n--;
			hwlib::wait_ms(200);
			hwlib::cout << n;
		}
		if(n>0){
			for(int i=0; i < n; i++){
				leds.set(0x01 << i);
			}
		}
		else{
			leds.set(0x00);
		}
	}
}

int main( void ){	
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   auto led0 = hwlib::target::pin_out( hwlib::target::pins::d7 );
   auto led1 = hwlib::target::pin_out( hwlib::target::pins::d6 );
   auto led2 = hwlib::target::pin_out( hwlib::target::pins::d5 );
   auto led3 = hwlib::target::pin_out( hwlib::target::pins::d4 );
   auto switch0 = hwlib::target::pin_in( hwlib::target::pins::d8 );
   auto switch1 = hwlib::target::pin_in( hwlib::target::pins::d9 );
   
   auto leds = hwlib::port_out_from_pins( led0, led1, led2, led3 );
//   int i = 0;
//   while(1){
//	   if(!switch0.get()){
//		   i = 1;
//		   break;
//	   }
//	   if(!switch1.get()){
//		   i = 2;
//		   break;
//	   }
//   }
//   leds.set(0x01 << i); hwlib::wait_ms(1000);
   
   ::moreless(leds, switch0, switch1);
}