#ifndef led_light_h
#define led_light_h
#include <iostream>
#include <csignal>
#include <string.h>
#include <stdio.h>
extern "C" {
#include <wiringPi.h>
}

// instructions for installing wiringPi http://wiringpi.com/download-and-install/
//https://pinout.xyz/
class led_light{

    public:
        led_light(int pin, std::string theColour);
        ~led_light();
        
        bool get_Status();
        int getPin();
        std::string getColour();
        void setColour(std::string theColour);
        void blink_led(int time);

        
    private:
        //status tells if light is on or off
        bool status = false;
        std::string colour = "";
        int pinNum;
};

#endif
