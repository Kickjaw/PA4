/*
Classes.cpp
file to hold all of the class structures for PA4
made by Jared Perkins 9/25/2017
*/

eventQueue::eventQueue() {
	head = NULL;
}
eventQueue::~eventQueue() {
	event *e = head;
	while(!e) {
		event *temp = e -> nextl
		delete e;
		p = temp;
	}
}

void eventQueue::insertEvent(int new_time) {
	event *e = new event(new_time);

	if (!head) { //if the eventqueue is null then add item as head of the linked list
		head = e;
		return;
	}

	else if (time < head -> time) { //if the item to be added is smaller then stick in front
		e -> next = head;
		head = e;
	}

	else {
		event *temp = head;
		while ((temp -> next)&&(temp -> next -> time < new_time)) {
			temp = temp -> next;
		}
		e -> next = temp -> next;
		temp -> next = e;
	}

}

void printEventQueue(void) {
	printLastEvents(head);
	std::cout << std ::endl;
}

void printLastEvents(event *e) {
	if (e -> next) {
		printLastEvents(p -> next);
	}
	std::cout << p -> time << " ";
}