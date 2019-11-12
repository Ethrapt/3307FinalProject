/*
 * bottle.h
 *
 */

#ifndef bottle_h
#define bottle_h
#include <time.h>
#include <stdio.h>
#include <cstdlib>


class bottle {
	
    public:
	bottle(); 
	~bottle(); 
	
	void setBottle(int bottleVol);
	void setWeightBottle(int bottleWeight);
	int getBottleVolume();
	int getBottleWeight();

    private:
	int bottleVolume; 	
	int weight;		


};
#endif /* BOTTLE_H_ */
