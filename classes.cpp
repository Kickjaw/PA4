/*
Classes.cpp
file to hold all of the class structures for PA4
made by Jared Perkins 9/25/2017
*/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "classes.h"

/**
 * Event constuctor
 */
event::event() {
	time = 0;
	next = NULL;
}
/**
 * eventQueue contructor
 */
eventQueue::eventQueue() {
	head = NULL;
}

/**
 * customerEvent constructor
 */
customerEvent::customerEvent() {
	cusNum = 0;
	arrivalTime = 0;
	arriving = false;
	inLine = false;
	finished = false;
}

/**
 *event Queue decontructor
 */
eventQueue::~eventQueue() {
	event *e = head;
	while(!e) {
		event *temp = e -> next;
		delete e;
		e = temp;
	}
}

/**
 * event deconstructor
 */
event::~event() {
	delete next;
}

/**
 * insert customer event into event queue
 * @param takes in the event time and adds the event to the list
 */
void eventQueue::insertEvent(event *e) {

	if (!head) { //if the eventqueue is null then add item as head of the linked list
		head = e;
		return;
	}

	else if (e -> time < head -> time) { //if the item to be added is smaller then stick in front
		e -> next = head;
		head = e;
	}

	else {
		event *temp = head;
		while ((temp -> next)&&(temp -> next -> time < e -> time)) {
			temp = temp -> next;
		}
		e -> next = temp -> next;
		temp -> next = e;
	}

}

/**
 * prints out the time of the event
 */
void event::printEvent(void) {
	std::cout << time << " ";
}

/**
 * prints out the time of the event
 */
void tellerEvent::printEvent(void) {
	std::cout << time << " ";
	std::cout << tellerNumber << " ";
	printf("Teller\n");

}
/**
 * prints out the time of the evnet, what customer it is, and what state it is in
 */
void customerEvent::printEvent(void) {
	std::cout << time << " ";
	std::cout << cusNum << " ";
	std::cout << arriving << " ";
	std::cout << inLine << " ";
	std::cout << finished << " ";
	printf("Customer\n");

}
/**
 * prints out the whole event quque
 */
void eventQueue::printEventQueue(void) {
	if (head != NULL) {
		printLastEvents(head);
		std::cout << std ::endl;
	}
}

/** cycles through the point next in event if next is not null, if null prints event
* prints out in revesre order of how the queue is made
*/
void eventQueue::printLastEvents(event *e) {
	if (e -> next) {
		printLastEvents(e -> next);
	}
	e->printEvent();
}

/**
 * checks the state fo the event, if basic event sends out 0
 */
int event::check(void) {
	printf("default check\n");
	return 0;
}
/**
 * checks to see what kind of event this is
 */
int tellerEvent::check(void) {
	//check teller queue for customer
	//if yse serve them, changed finished to true and send back into event queue anding serve time
	return 6;
}

/**
 * checks what the customer needs to do
 */
int customerEvent::check(void) {
	if (arriving) {
		//send to a line
		return 1;
	}
	if (inLine) {
		//customer got to front of teller queue, send to teller, not time based
		return 2;
	}
	if (finished) {
		//gather statistics and delete event
		return 3;
	}
	return 1;
}
/**
 * inserts event based on the time, smallest time at the front and longest at the end
 * @param e event to insert into the event queue
 */
void tellerQueue::insertEventEnd(event *e) {

	event *temp = new event();
	e -> next = NULL;

	if (!head) {
		head = e;
	}

	else {
		temp = head;
		while (temp -> next) {
			temp = temp -> next;
		}
		temp -> next = e;
	}
}

/**
 * @return event* returns the event at the head of the queue
 */

event* eventQueue::pop(void) {
	event *temp = new event();
	temp = head;
	head = head -> next;
	return temp;
}

/**
 * head method for event class
 */
void event::cycleState(void) {
	printf("defualt event cycle, shouldnt be here\n");
}
/**
 * cycles through the states of the customerEvent
 */
void customerEvent::cycleState(void) {
	if (arriving){
		arriving = false;
		inLine = true;
	}
	else if (inLine) {
		inLine = false;
		finished = true;
	}
	else if (finished) {
		printf("delete event here\n");
	}
}
/**
 * head method to get arrival time
 */
int event::getArrivalTime(void) {
	return 0;
}
/**
 * getter for arrival time for customer event
 */
int customerEvent::getArrivalTime(void) {
	return arrivalTime;
}
/**
 * head method to get idle timem
 */
int event::getIdleTime(void) {
	return 0;
}
/**
 * getter for idle time of teller event
 */
int tellerEvent::getIdleTime(void) {
	return idleTime;
}

int tellerQueue::getLength(void) {
	return length;
}

int event::getTellerNumber(void) {
	return 0;
}
int tellerEvent::getTellerNumber(void) {
	return tellerNumber;
}