


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
		t -> tellerNumber = i;
		queue.insertEvent(t);
	}
	return queue;
}



// tellerQueue generateTellerQueues(int tellers) {
// 	tQueues [tellers];
// 	for (int i = 0; i < tellers; i++) {
// 		tellerQueue *queue = new tellerQueue();
// 		tQueues[i] = queue;
// 	}
// 	return tQueues;make
// }

int main(void){

	int tellers = 5;
	int customerServed = 0;
	int totalTimeToServe = 0;
	int averageTimeSpent = 0;
	int standarddeviation = 0;
	int totalTellerSeviceTime = 0;
	int totalTellerIdleTime = 0;
	int maxWaitTime = 0;
	int waitTimeAverage =0;
	int counter = 0;
	long clock = 0;
	int customers = 10;
	long length = 1000;
	int service  = 200; // change this later
	eventQueue E;
	tellerQueue T;
	T.head = NULL;

	tellerQueue *tQueues[tellers];
	for (int i =0; i < tellers; i++) {
		tQueues[i] = new tellerQueue();
	}

	E = generateCustomers(customers, length, E);
	E = generateTellers(tellers, E);

	E.printEventQueue();
	while (counter != customers) {
	switch(E.head->check()){
		/*
		0 = event: should not arise, all events should be either customer or teller
		1 = customerEvent: arriving
		2 = customerEvent: inline(shouldnt come up)
		3 = customerEvent: customer finished in the bank
		6 = tellerEvent: teller has either finished servering customer, or is back from break, check for customer in teller line
		default = catch all, should not come up 
		*/
		case 0:
			printf("generic event in queue, something went wrong\n");
			break;
		case 1:
			//place customer in teller queue
			printf("place customer in telller queue\n");
			clock = E.head->time;
			E.head->cycleState();
			T.insertEventEnd(E.pop());
			break;
		case 2:
			printf("customer inline while in event queue, something went wrong\n");
			break;
		case 3:
			//customer finished, gather statistics about and remove from queue
			clock = E.head->time;
			printf("customer finished\n");
			if (clock < length) { //if within simulatino time frame increment customer served
				customerServed++; 
			}
			E.pop();
			counter++;
			break;
		case 6:
			//have teller serach his respective queue or the general queue for a customer to searve
			clock = E.head->time;
			if (T.head != NULL) {
				event *temp = new event();
				temp = T.pop();
				temp -> cycleState();//changes state
				temp -> time = temp -> time + service; //adds the time to be serviced
				E.insertEvent(temp); //sends it back into the event queue

				event *tTemp = new event();
				tTemp = E.pop();
				tTemp -> time = tTemp -> time + service;
				E.insertEvent(tTemp);

				totalTellerSeviceTime = totalTellerSeviceTime + service;

				waitTimeAverage = waitTimeAverage + (clock - temp -> getArrivalTime());

				if ((clock - temp -> getArrivalTime()) > maxWaitTime) {
					maxWaitTime = (clock - temp -> getArrivalTime());
				}
			}
			else {
				event *tTemp = new event();
				tTemp = E.pop();
				tTemp -> time = tTemp -> time + tTemp->getIdleTime();
				E.insertEvent(tTemp);
				printf("no customer in queue\n");

				totalTellerIdleTime = totalTellerIdleTime + tTemp->getIdleTime();

			}
			printf("teller check\n");
			break;
		default:
			printf("Something other \n");
			break;
		}
		E.printEventQueue();
	}


	printf("The number of tellers in the simulaton is %i.\n", tellers );

	printf("The queue type is a single queue for all the tellers.\n");
	printf("Total number of customer served in the time frame is %i. \n", customerServed);
	printf("Time to serve all customers input into simulation is %d in seconds. \n", clock);
	printf("Average time customers spent in the bank is %ld and the standard deviation is %i.\n", averageTimeSpent, standarddeviation );
	printf("The maximum wait time for a customer to be seen is %i.\n", maxWaitTime);
	printf("Total amount of teller service time is %i.\n", totalTellerSeviceTime);
	printf("Total amount of teller idle time is %i.\n", totalTellerIdleTime);





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
