/*
 * classes.h
 *
 *  jared perkins
 */
//this class and the associated methods are based off of the code given in lab 4 created by Hugh Lauer
#ifndef CLASSES_H 
#define CLASSES_H

#include <cstdio>
#include <cstdlib>

class event { //internal class event, objects that make up eventQueue
public:

	int time; //time at which the event will happen
	event *next;  //next item in the eventQueue

	//virtual action()

	inline event(int time) : time(time), next(NULL) {}; //????
private:
	
};

class eventQueue {
public:
	void insertEvent(event *e); //method to add item to event queue in order
	void printEventQueue(void);

	eventQueue(); //constructor	
	~eventQueue(); //deconstructor
//private:
	event *head; 


	void printLastEvents(event *e);


	
};

class customerEvent: public event { //type of event
public:
	int customerNumber; //helps tell customers aprat

};

class tellerEvent: public event { //type of event
public:
	int idleTime; //time that the teller will idle for

};


#endif


