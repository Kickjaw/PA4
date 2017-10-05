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

	virtual void cycleState(void);
	virtual int getArrivalTime(void);
	virtual int getIdleTime(void);
	virtual int getTellerNumber(void);

	virtual int check(void); //check what the status of the event is
	event();
	virtual ~event();
	virtual void printEvent(void);

	inline event(int time) : time(time), next(NULL) {}; //????
private:
	
};




class eventQueue {
public:
	void insertEvent(event *e); //method to add item to event queue in order
	void printEventQueue(void);
	event* pop(void);

	eventQueue(); //constructor	
	virtual ~eventQueue(); //deconstructor
//private:
	event *head; 

	void printLastEvents(event *e);


};




class customerEvent: public event { //type of event

public:
	customerEvent();

	virtual void cycleState(void);

	virtual int getArrivalTime(void);

	int cusNum; //helps tell customers aprat
	int arrivalTime; //time of arrival
	bool arriving; //did he just come int
	bool inLine; //customer in line for teller
	bool finished; //customer was served and is leaving

	virtual int check(void);

	virtual void printEvent(void);

};



class tellerEvent: public event { //type of event
public:
	int idleTime; //time that the teller will idle for
	int tellerNumber;

	virtual int check(void);
	virtual int getIdleTime(void);
	virtual int getTellerNumber(void);

	virtual void printEvent(void);





};


class tellerQueue: public eventQueue {
public:
	int length;
	int getLength(void);


	void insertEventEnd(event *e);

};


#endif


