#include "bottle.h" 
using namespace std;


/*
 * bottle.cpp
 * This class remembers the weight and volume of a bottle
 * For the time being, it is not used
 */
 
bottle::bottle() {} 
bottle::~bottle() {}

// sets the bottle's volume
void bottle::setBottle(int bottleVol){
	this->bottleVolume = bottleVol;
}

//this function is setting the weight of the bottle after a hypothetical taring function
//has been done, then it stores the weight into memory
void bottle::setWeightBottle(int bottleWeight){
	this->weight = bottleWeight;

}

// gets the bottle's volume
int bottle::getBottleVolume(){
	return this->bottleVolume;
}
 
// this function returns the bottle's weight, so 
// the it can be used to substract from the weight measured from
// scale without the person having to re-tare what is in memory.
// This allows us to carry on with required water intake calculations
int bottle::getBottleWeight(){
	return this->weight;
}
