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
	void action();

	void check(); //check what the status of the event is
	event();
	void printEvent(event *e);

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
	customerEvent();

	int cusNum; //helps tell customers aprat
	int arrivalTime; //time of arrival
	bool arriving; //did he just come int
	bool inLine; //customer in line for teller
	bool finished; //customer was served and is leaving

	void check(customerEvent *c);

	void printEvent(customerEvent *c);

};



class tellerEvent: public event { //type of event
public:
	int idleTime; //time that the teller will idle for

	void printEvent(tellerEvent *t);

	void check(tellerEvent *t);



};


class tellerQueue: public eventQueue {
public:
	int length;

};


#endif


