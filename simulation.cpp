


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
		e -> time = time; //sets the event time to the time it is set to arrive
		e -> arrivalTime = time;// sets the arival time to the time in which it was set to arrive
		e -> arriving = true; //sets boolean that it is arriving to true
		e -> cusNum = i; //incriments to help keep track of different customers
		queue.insertEvent(e);
	}
	return queue;

}

eventQueue generateTellers(int tellers, eventQueue queue) {
	int time = 0;
	for (int i = 0; i < tellers; i ++) {
		tellerEvent *t = new tellerEvent();
		t -> idleTime = rand() % 150 + 1;
		t -> time = time; //set all the tellers to be at the front of the event queue
		queue.insertEvent(t);
	}
	return queue;
}

int main(void){
	int tellers = 5;
	long clock = 0;
	int customers = 10;
	long length = 1000;
	eventQueue E;
	tellerQueue T;

	E = generateCustomers(customers, length, E);

	E.printEventQueue();

	T.insertEventEnd(E.head);
	T.insertEventEnd(E.head);
	T.insertEventEnd(E.head);
	printf("hi\n");
	E.removeHeadEvent();
	printf("hi2\n");

	T.printEventQueue();
	printf("hi3\n");

	E.printEventQueue();

	//E = generateTellers(tellers, E);

	//E.printEventQueue();
	
	
	// switch(E.head->check()){
	// 	/*
	// 	0 = event: should not arise, all events should be either customer or teller
	// 	1 = customerEvent: arriving
	// 	2 = customerEvent: inline(shouldnt come up)
	// 	3 = customerEvent: customer finished in the bank
	// 	6 = tellerEvent: teller has either finished servering customer, or is back from break, check for customer in teller line
	// 	default = catch all, should not come up 
	// 	*/
	// 	case 0:
	// 		printf("generic event in queue, something went wrong\n");
	// 	case 1:
	// 		//place customer in teller queue
	// 		T.insertEventEnd(E.head);
	// 	case 2:
	// 		printf("customer inline while in event queue, something went wrong\n");
	// 	case 3:
	// 		//customer finished, gather statistics about and remove from queue
	// 	case 6:
	// 		//have teller serach his respective queue or the general queue for a customer to searve
	// 		printf("teller check\n");
	// 	// default:
	// 	// 	printf("Something other \n");
	// 	}





		//check what event is at the front of the queue
		//do the corrisponding action of that event
			//if event is customer check boolean to see what to do
				//if set to arriving send to teller queu
				//if set to inline somthing is wrong
				//if set to finished 
					//gather stats and remove event from queue and delete it
			//if event is teller check teller queue for a customer
				//if customer server customer and throw back into event queue with finish time
				//if no customer send teller back into event queue with idle time

}
