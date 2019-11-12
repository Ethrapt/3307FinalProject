/*
 * led_light.cpp
 * Contains operations used to power & blink led lights. 
 * 
 */

#include "led_light.h"
using namespace std;

// creates an led_light object
// pass in the pin which the led is connected to on the raspberry pi,
// and a string representing the light's color.
led_light::led_light(int pin, string theColour){
    wiringPiSetupGpio();
    this->pinNum = pin;
    this->colour = theColour;
    pinMode(pin, OUTPUT);
}

// destructor for led_light objects
led_light::~led_light(){ }

// returns the light's status--true for on, false for off.
bool led_light::get_Status(){
    return this->status;
}

// returns the pin number of this light
int led_light::getPin(){
    return this->pinNum;
}

// returns the light's color
string led_light::getColour(){
    return this->colour;
}

// changes the color stored in this led_light object, used for identification
void led_light::setColour(string theColour){
    this->colour = theColour;
}

// Makes the led_light flash for the time specified (in milliseconds)
void led_light::blink_led(int time){
    digitalWrite(this->pinNum, HIGH);
    this->status = true;
    delay(time);
    digitalWrite(this->pinNum, LOW);
    this->status = false;
    delay(time);
}

