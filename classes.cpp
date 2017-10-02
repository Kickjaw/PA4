/*
Classes.cpp
file to hold all of the class structures for PA4
made by Jared Perkins 9/25/2017
*/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "classes.h"


event::event() {
	time = 0;
	next = NULL;
}

eventQueue::eventQueue() {
	head = NULL;
}

customerEvent::customerEvent() {
	cusNum = 0;
	arrivalTime = 0;
	arriving = false;
	inLine = false;
	finished = false;
}


eventQueue::~eventQueue() {
	event *e = head;
	while(!e) {
		event *temp = e -> next;
		delete e;
		e = temp;
	}
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

void event::printEvent(void) {
	std::cout << time << " ";
}

void tellerEvent::printEvent(void) {
	std::cout << time << " ";
	printf("Teller\n");

}

void customerEvent::printEvent(void) {
	std::cout << time << " ";
	std::cout << cusNum << " ";
	printf("Customer\n");

}

void eventQueue::printEventQueue(void) {
	printLastEvents(head);
	std::cout << std ::endl;
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

void check(void) {
	printf("default check\n");
}

void check(tellerEvent *e) {
	//check teller queue for customer
	//if yse serve them, changed finished to true and send back into event queue anding serve time
	printf("checked tellerEvent\n");
}


void check(customerEvent *e) {
	if (e -> arriving) {
		//send to a line
	}
	if (e -> inLine) {
		//customer got to front of teller queue, send to teller, not time based
	}
	if (e -> finished) {
		//gather statistics and delete event
	}
}



