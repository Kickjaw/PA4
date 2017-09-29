


#include <cstdio>
#include <cstdlib>
#include "classes.h"
#include "classes.cpp"
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
		event *e = new customerEvent(time);
		e -> customerNumber = i; //incriments
		queue.insertEvent(e);
	}

}

int main(void){
	int customers = 100;
	long length = 1000;
	eventQueue E;

	generateCustomers(customers, length, E);

	E.printEventQueue();
	
}