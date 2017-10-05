


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

int main(int argc, char *argv[]){

	int customers = atoi(argv[1]);
	int tellers = atoi(argv[2]);
	long length = atoi(argv[3]);
	int averageServiceTime = atoi(argv[4]);
	int seed;

	if (argc > 5 ) {
		seed = atoi(argv[5]);
	}
	else{
		seed = time(NULL);
	}

	srand(seed);
	
	int customerServed = 0;
	int averageTimeSpent = 0;
	int totalTellerSeviceTime = 0;
	int totalTellerIdleTime = 0;
	int maxWaitTime = 0;
	int waitTimeAverage =0;

	int counter = 0;
	long clock = 0;


	
	//float service = (2*averageServiceTime*rand())/float(RAND_MAX); help with this
	int service = 150;
	
	eventQueue E;
	tellerQueue T;
	T.head = NULL;

	tellerQueue *tQueues[tellers];
	for (int i =0; i < tellers; i++) {
		tQueues[i] = new tellerQueue();
	}

	int shortestQueue = 0;

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
				printf("hi\n");
				clock = E.head->time;
				E.head->cycleState();
				for (int i = 0; i < tellers; i++) {
					if (tQueues[i]->getLength() < shortestQueue) {
						shortestQueue = i;
					}
				}

				tQueues[shortestQueue]->insertEventEnd(E.pop());
				printf("hi2\n");
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
				averageTimeSpent = averageTimeSpent + E.head->getArrivalTime();
				break;
			case 6:
				//have teller serach his respective queue or the general queue for a customer to searve
				clock = E.head->time;
				if (tQueues[E.head->getTellerNumber()] != NULL) {
					event *temp = new event();
					temp = tQueues[E.head->getTellerNumber()]->pop();
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

					totalTellerIdleTime = totalTellerIdleTime + tTemp->getIdleTime();

				}
				break;
			default:
				printf("Something other \n");
				break;
			}
	}
	E.printEventQueue();
	//remove tellers from queue
	for (int i = 0; i < tellers; i++) {
		E.pop();
	}
	averageTimeSpent = averageTimeSpent/customers;

	printf("The number of tellers in the simulaton is %i.\n", tellers );

	printf("The queue type is a individual queue for all the tellers.\n");
	printf("Total number of customer served in the time frame is %i. \n", customerServed);
	printf("Time to serve all customers input into simulation is %ld in seconds. \n", clock);
	printf("Average time customers spent in the bank is %i .\n", averageTimeSpent);
	printf("The maximum wait time for a customer to be seen is %i.\n", maxWaitTime);
	printf("Total amount of teller service time is %i.\n", totalTellerSeviceTime);
	printf("Total amount of teller idle time is %i.\n", totalTellerIdleTime);

	// //reset varabiles --------------------------------------------------
	// customerServed = 0;
	// averageTimeSpent = 0;
	// standarddeviation = 0;
	// totalTellerSeviceTime = 0;
	// totalTellerIdleTime = 0;
	// maxWaitTime = 0;
	// waitTimeAverage =0;

	// counter = 0;
	// clock = 0;

	// eventQueue E2;
	// tellerQueue T2;
	// T2.head = NULL;

	

	// E2 = generateCustomers(customers, length, E);
	// E2 = generateTellers(tellers, E);

	// E2.printEventQueue();

	// //---------------------------------------------------------------------------------------------------------------
	// //second sim with individual queues for each teller

	// while (counter != customers) {
	// 	switch(E.head->check()){
	// 		/*
	// 		0 = event: should not arise, all events should be either customer or teller
	// 		1 = customerEvent: arriving
	// 		2 = customerEvent: inline(shouldnt come up)
	// 		3 = customerEvent: customer finished in the bank
	// 		6 = tellerEvent: teller has either finished servering customer, or is back from break, check for customer in teller line
	// 		default = catch all, should not come up 
	// 		*/
	// 		case 0:
	// 			printf("generic event in queue, something went wrong\n");
	// 			break;
	// 		case 1:
	// 			//place customer in teller queue
	// 			clock = E.head->time;
	// 			E.head->cycleState();
	// 			T.insertEventEnd(E.pop());
	// 			break;
	// 		case 2:
	// 			printf("customer inline while in event queue, something went wrong\n");
	// 			break;
	// 		case 3:
	// 			//customer finished, gather statistics about and remove from queue
	// 			clock = E.head->time;
	// 			printf("customer finished\n");
	// 			if (clock < length) { //if within simulatino time frame increment customer served
	// 				customerServed++; 
	// 			}
	// 			E.pop();
	// 			counter++;
	// 			averageTimeSpent = averageTimeSpent + E.head->getArrivalTime();
	// 			break;
	// 		case 6:
	// 			//have teller serach his respective queue or the general queue for a customer to searve
	// 			clock = E.head->time;
	// 			if (T.head != NULL) {
	// 				event *temp = new event();
	// 				temp = T.pop();
	// 				temp -> cycleState();//changes state
	// 				temp -> time = temp -> time + service; //adds the time to be serviced
	// 				E.insertEvent(temp); //sends it back into the event queue

	// 				event *tTemp = new event();
	// 				tTemp = E.pop();
	// 				tTemp -> time = tTemp -> time + service;
	// 				E.insertEvent(tTemp);

	// 				totalTellerSeviceTime = totalTellerSeviceTime + service;

	// 				waitTimeAverage = waitTimeAverage + (clock - temp -> getArrivalTime());

	// 				if ((clock - temp -> getArrivalTime()) > maxWaitTime) {
	// 					maxWaitTime = (clock - temp -> getArrivalTime());
	// 				}
	// 			}
	// 			else {
	// 				event *tTemp = new event();
	// 				tTemp = E.pop();
	// 				tTemp -> time = tTemp -> time + tTemp->getIdleTime();
	// 				E.insertEvent(tTemp);

	// 				totalTellerIdleTime = totalTellerIdleTime + tTemp->getIdleTime();

	// 			}
	// 			break;
	// 		default:
	// 			printf("Something other \n");
	// 			break;
	// 		}
	// 	//E.printEventQueue();
	// }
	// averageTimeSpent = averageTimeSpent/customers;

	// printf("The number of tellers in the simulaton is %i.\n", tellers );

	// printf("The queue type is a single queue for all the tellers.\n");
	// printf("Total number of customer served in the time frame is %i. \n", customerServed);
	// printf("Time to serve all customers input into simulation is %ld in seconds. \n", clock);
	// printf("Average time customers spent in the bank is %i and the standard deviation is %i.\n", averageTimeSpent, standarddeviation );
	// printf("The maximum wait time for a customer to be seen is %i.\n", maxWaitTime);
	// printf("Total amount of teller service time is %i.\n", totalTellerSeviceTime);
	// printf("Total amount of teller idle time is %i.\n", totalTellerIdleTime);
}
