/*
 * classes.h
 *
 *  jared perkins
 */
//this class and the associated methods are based off of the code given in lab 4 created by Hugh Lauer


#include <cstdio>
#include <cstdlib>

class eventQueue {
public:
	void insertEvent(int time); //method to add item to event queue in order
	void printEventQueue(void); //method to print out the whole eventQueue in order

	eventQueue(); //constructor	
	~eventQueue(); //deconstructor
private:
	class event; 
	event *head; 


	void printLastEvents(event *e);


	class event { //internal class event, objects that make up eventQueue
	public:

		int time; //time at which the event will happen
		event *next;  //next item in the eventQueue

		inline event(int time) : time(time), next(NULL) {}; //????
	private:
		class customerEvent { //type of event

		}

		class tellerEvent { //type of event

		}
	}
}



class tellerQueue: public eventQueue {
public:
	//teller queue functions

}

