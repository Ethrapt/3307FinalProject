#include "Goaltracker.h"
using namespace std;

/*
 * Goaltracker.cpp
 *
 * This class takes in values from a scale and track's the user's progression towards their goal.
 * All operations are in some way linked to tracking a goal.
 */
 
 Goaltracker::Goaltracker() {}; //constructor
 Goaltracker::~Goaltracker() {}; //deconstructor

// returns a percentage representing progression towards the goal
// this will be important if we get an lcd screen
float Goaltracker::getProgression()
{
    float progPerc;
    progPerc = ((float)this->amountDrank / (float)this->goal) * 100;
    return progPerc;
}
// this returns the status of the water intake when asked for
// by the orchestration class
int Goaltracker::getStatus()
{
    return this->status;
}

// this is the getter for how long the user plans on staying awake
int Goaltracker::getHoursAwake()
{
	return this->numHoursAwake;
}

//This returns the initial volume put in for the water bottle by the user
int Goaltracker::getInitialVolume()
{
	return this->initialVolume;
}

/*
 * This function takes in time as an integer, and weight of the current water in the bottle
 * and returns 1 if the amount drank by the person thus far is up to date with the amount
 * of water the person has needed to drink up until that point.
 * -(Interval*time) means the amount of water they must have drank all together based
 * on how many hours have gone by
 */
void Goaltracker::setStatus(int time, int weight, int numAwakeHours)
{
    this->numHoursAwake = numAwakeHours;
    amountDrank = initialVolume - weight;
    if (weight < 0){
        // The user has lifted the bottle from the scale, assign 0
        status = 0;
    }else if (amountDrank < interval*time){
	// The user is behind on their goal, assign -1 
	status = -1;
    }else if (amountDrank >= interval*time){
    	// if amountDrank up until now >= current interval multiplied by time
    	// aka the user is ahead of their goal, assign 1
    	status = 1;
    }
    ////////////////////////////////////////////////////////////////
    // USER STORY - RESET
    // this automatically resets the time when it hits the numAwakeHours
    // the user entered, saying they will be awake
    // this completes the reset user story saying the program will have a way to be reset, and
    // that the program will reset when the person will go to sleep
    // the program will not reset at midnight (this acceptance test is bypassed)
    // because someone can stay awake past midnight, but people are usually
    // awake straight for a defined number of hours
    if (time == numHoursAwake)
    {
		goal = 0;
		initialVolume = 0;
    }
}

// allows us to set and get the numhours the person will be planning on staying awake
void Goaltracker::setHoursAwake(int hoursAwake)
{
	this->numHoursAwake = hoursAwake;
}

// allows us to change the goal
void Goaltracker::setGoal(int theGoal)
{
    this->goal = theGoal;
}

/////////////////////////////////////////////////////////////////////////
// USER STORY - DIFFERENT WATER BOTTLES (incomplete)
// lays out the foundations for a future user story
// This lets the user enter the amount of liquid the user has in their
// water bottle - the next step is creating bottle objects that hold 
// the user's different water bottle information
void Goaltracker::setInitialVolume(int initialVolumeUser)
{
	this->bot->setBottle(initialVolumeUser);	//create bottle for memory of weight
	this->initialVolume = initialVolumeUser;
}

// this sets the interval amount based on the number of hours awake
// and the set goal by the user
void Goaltracker::setInterval() 
{
	this->interval = this->goal/this->numHoursAwake;
}

/////////////////////////////////////////////////////////////////////
// USER STORY - RESET
// this resets the entire program and clears the numbers entered by the user
// to reflect how they wanted to change their goals and number of hours awake
// this completes one of our user stories, this function can be called by the user
void Goaltracker::reset(int time, int awakeNumHours){
	this->goal = 0;
	this->initialVolume = 0;
	this->numHoursAwake = 0;
}



