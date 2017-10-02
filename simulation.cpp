


#include <cstdio>
#include <cstdlib>
#include "classes.h"
#include <iostream>

/**
 * Generate Customers
 * @param customers number of customers to generate
 * @param length length of time to run  the simulation in seconds
 * @param queue event queue to add the customers to
 * @return returns the event queue with the customers added
 * takes in needed parameters for random generation. the number of customers to generate, and an event queue
 * and generates random arrival times for the customers and puts them into the event queue
 */

eventQueue generateCustomers(int customers, long length, eventQueue queue) {
	float time;
	for (int i = 0; i < customers; i++) {
		time = length*rand()/float(RAND_MAX);
		customerEvent *e = new customerEvent();
		e -> time = time;
		e -> arrivalTime = true;
		e -> cusNum = i; //incriments
		queue.insertEvent(e);
	}
	return queue;

}

eventQueue generateTellers(int tellers, eventQueue queue) {
	int time = 0;
	for (int i = 0; i < tellers; i ++) {
		tellerEvent *t = new tellerEvent();
		t -> idleTime = rand() % 150 + 1;
		t -> time = time;
		queue.insertEvent(t);
	}
	return queue;
}

int main(void){
	int tellers = 5;
	long clock = 0;
	int customers = 100;
	long length = 1000;
	eventQueue E;
	E = generateCustomers(customers, length, E);

	E.printEventQueue();

	E = generateTellers(tellers, E);

	E.printEventQueue();
	


	while(clock != length) {
		E.head->check();


		//check what event is at the front of the queue
		//do the corrisponding action of that event
			//if event is customer check boolean to see what to do
			//if event is teller check teller queue for a customer
				//if customer server customer and throw back into event queue with finish time
				//if no customer send teller back into event queue with idle time

	}
}
