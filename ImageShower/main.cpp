//==============================================================================//
//																				//
//						Created by Philippe Zwietering							//
//																				//
//==============================================================================//

#include "hwlib.hpp"
#include "image.hpp"
int main(void)
{
	hwlib::location pixelverzameling[] = {hwlib::location{31, 0}, hwlib::location{30, 1}, hwlib::location{31, 1}, hwlib::location{2, 2}, hwlib::location{3, 2}, hwlib::location{4, 2}, hwlib::location{15, 2}, hwlib::location{16, 2}, hwlib::location{17, 2}, hwlib::location{18, 2}, hwlib::location{19, 2}, hwlib::location{23, 2}, hwlib::location{24, 2}, hwlib::location{25, 2}, hwlib::location{30, 2}, hwlib::location{0, 3}, hwlib::location{1, 3}, hwlib::location{2, 3}, hwlib::location{4, 3}, hwlib::location{5, 3}, hwlib::location{7, 3}, hwlib::location{8, 3}, hwlib::location{9, 3}, hwlib::location{10, 3}, hwlib::location{11, 3}, hwlib::location{12, 3}, hwlib::location{14, 3}, hwlib::location{15, 3}, hwlib::location{19, 3}, hwlib::location{20, 3}, hwlib::location{21, 3}, hwlib::location{22, 3}, hwlib::location{23, 3}, hwlib::location{25, 3}, hwlib::location{26, 3}, hwlib::location{29, 3}, hwlib::location{30, 3}, hwlib::location{0, 4}, hwlib::location{5, 4}, hwlib::location{6, 4}, hwlib::location{7, 4}, hwlib::location{12, 4}, hwlib::location{13, 4}, hwlib::location{14, 4}, hwlib::location{20, 4}, hwlib::location{21, 4}, hwlib::location{26, 4}, hwlib::location{27, 4}, hwlib::location{28, 4}, hwlib::location{0, 5}, hwlib::location{6, 5}, hwlib::location{7, 5}, hwlib::location{12, 5}, hwlib::location{13, 5}, hwlib::location{20, 5}, hwlib::location{26, 5}, hwlib::location{27, 5}, hwlib::location{0, 6}, hwlib::location{6, 6}, hwlib::location{12, 6}, hwlib::location{20, 6}, hwlib::location{26, 6}, hwlib::location{0, 7}};
	image::image plaatje(32, 8, 63, pixelverzameling); 
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;


    auto scl = hwlib::target::pin_oc{ hwlib::target::pins::scl };
    auto sda = hwlib::target::pin_oc{ hwlib::target::pins::sda };

    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda{ scl, sda };

    auto display = hwlib::glcd_oled{ i2c_bus, 0x3c };

    display.clear();
    display.write(hwlib::location{ 0, 0 });
	
	plaatje.draw();

}