//============================================================================
//
//	Created by Philippe Zwietering
//
//============================================================================

#include "hwlib.hpp"
#include "image.hpp"
int main(void)
{
	
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;


    auto scl = hwlib::target::pin_oc{ hwlib::target::pins::scl };
    auto sda = hwlib::target::pin_oc{ hwlib::target::pins::sda };

    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda{ scl, sda };

    auto display = hwlib::glcd_oled{ i2c_bus, 0x3c };

    display.clear();
    display.write(hwlib::location{ 0, 0 });
}