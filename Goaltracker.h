/*
 * Goaltracker.h
 * the header file containing protypes and attribute declarations for the Goaltracker class.
 */

#ifndef Goaltracker_h
#define Goaltracker_h
#include "bottle.h"

class Goaltracker {


public:

    Goaltracker();
    ~Goaltracker();

    float getProgression();
    int getStatus();
    int getHoursAwake();
    int getInitialVolume();
    void setStatus(int time, int weight, int numAwakeHours);
    void setHoursAwake(int);
    void setGoal(int theGoal);
    void setInterval();
    void setInitialVolume(int initialVolumeUser);
    void reset(int time, int awakeNumHours);

private:

    int goal; 				
    int initialVolume; 			// will be adjusted throughout, gets value from Scale (input file)
    int amountDrank; 			// amount drunk from initial goal
    int status; 			// sets the user's status wrt to their goal, 1 = ahead, -1 = behind
    int interval;			// amount to drink per hour depending on their goal and time spent awake in hours [goal / time]
    int numHoursAwake;  		// this keeps track of how long the person is planning on staying awake, used in calculating the interval
    bottle * bot = new bottle();	// creating bottle class for the future implementation of the different water bottles user story


};

#endif /* GOALTRACKER_H_ */
