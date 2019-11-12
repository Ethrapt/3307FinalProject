default: orchestration.cpp 
	g++ orchestration.cpp bottle.cpp Goaltracker.cpp led_light.cpp -lwiringPi -o orchestration

clean:
	rm orchestration
