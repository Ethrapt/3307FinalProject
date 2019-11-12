/*
 * orchestration.cpp 
 * Uses all the available operations in the created classes to run the Droplet system.
 * Currently configured to read from a text file, not a scale.
 * 
 */
#include "Goaltracker.h"
#include "led_light.h"
#include <iostream>
#include <fstream>
#include <csignal>
#include <cerrno>

using namespace std;
 
 // Callback handler if CTRL-C signal is detected
void my_handler(int s) {
    cout << "Detected CTRL-C signal no. " << s << '\n' << endl;
    exit(0);
}

int main() {

	// intitializing the variables to be used throughout this method
	// String used to read lines from the text file (the dummy scale)
	string weight;							
	// initializes hours for the test case, as well as the weight of the water + bottle
    int waterWeight, bottleWeight, hours = 1;     
	ifstream infile;
	
    led_light * red = new led_light(17, "red");
    led_light * green = new led_light(22, "green");
    led_light * blue = new led_light(23, "blue");
    led_light * rgb = new led_light(27, "rgb");
    
    // Register a callback function to be called if the user presses CTRL-C
    signal(SIGINT, my_handler);
    // this file is our "dummy" scale; it has the input from the 'scale' throughout the day, 
    // taken every hour, assuming the person is awake for 15 hours
	infile.open("drinktest.txt");		
		
	if (infile.fail()){
        cout << "Error opening file.\n" << endl;
        exit(0);
    }

    Goaltracker * test = new Goaltracker();				//this creates a Goaltracker object
	test->setGoal(2000);                                //setting water goal as 2000ml, which is 2L
    test->setHoursAwake(15);
    
/////////////////////////////////////////////////////////////////////////
// USER STORY - TARING (incomplete)
// Reads in the weight of the bottle, and uses it to offset all future 
// readings from the scale.
// This will happen in the scale class in the future, with a bottle object
// passes all acceptance tests, but there is no button yet.
    getline(infile, weight);
    bottleWeight = atoi(weight.c_str());
    if (bottleWeight > 2000){
        cout << "That bottle weighs too much. Please reset the scale and use a different bottle.\n" << endl;
        exit(0);
    }
//////////////////////////////////////////////////////////////////////////

    // reading in the initial amount of water in the bottle.
    // this is stored & used to calculate the progression.
    getline(infile, weight);
    waterWeight = atoi(weight.c_str()) - bottleWeight;
    test->setInitialVolume(waterWeight);                       
    

	// within this loop, read in each hourly weight value 
	// and calculate the user's status towards their goal.
	while (!infile.eof()){ 					
		
		getline(infile, weight); 
		// cout << "our weight is: " << weight << endl;

		// converting information to an integer and calculating the status.
		waterWeight = atoi(weight.c_str()) - bottleWeight; 		
		
		test->setStatus(hours, waterWeight, test->getHoursAwake());	
		test->setInterval();	

        // Turn on the correct light depending on the status.
		if (test->getStatus() == -1) {
	
            cout << "You are falling behind on your goal!" << endl;
            red->blink_led(1000);

		} else if (test->getStatus() == 1) {
         
            cout << "You are on track!"<< endl;;
            green->blink_led(1000);
            
        }else if (test->getStatus() == 0){
		
            cout << "You are currently drinking water"<< endl;
            blue->blink_led(1000);
		}

		hours++;
		// checking that if the user has reached the end of the day
		if (hours == 15 && test->getProgression() == 100) {
         
            cout << "Good job! You reached your goal!" << endl;;
         
            rgb->blink_led(1000);
            rgb->blink_led(1000);
            rgb->blink_led(1000);
            break;
         
		}else if(hours == 15 && test->getProgression() != 100){
			cout << "You only completed " << test->getProgression() << "% of your goal :( please try harder tomorrow!" << endl;
			break;
		}
	}
	
	// destroying all objects & closing the infile.
	infile.close();
	delete test;
	delete red;
	delete blue;
	delete green;
	delete rgb;
    return 0;
}

