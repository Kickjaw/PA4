/*
Classes.cpp
file to hold all of the class structures for PA4
made by Jared Perkins 9/25/2017
*/



#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "classes.h"


//construtor
eventQueue::eventQueue() {
	head = NULL;
}
 
//deconstructor
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


void eventQueue::printEventQueue(void) {
	printLastEvents(head);
	std::cout << std ::endl;
}

void eventQueue::printLastEvents(event *e) {
	if (e -> next) {
		printLastEvents(e -> next);
	}
	std::cout << e -> time << " ";
}



