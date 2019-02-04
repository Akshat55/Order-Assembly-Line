#include <iostream>
#include <iomanip>
#include "Task.h"
#include "Utilities.h"


size_t Task::field_width = 1;


//Constructor
Task::Task(const std::string& record) {

	//Initalizes the number of product slots
	this->slots = "1";
	size_t next_pos = 0;
	bool more = true;

	//Sets the pointer to a safe 0 --> Passed, 1 --> Redirect
	for (int i = 0; i < 2; i++) {
		this->pNextTask[i] = nullptr;
	}

	//Instantiating Utilities instance
	Utilities extract;
	extract.setFieldWidth(field_width);		//Passes the static variable as parameter

											//Extracting and Assigning
	name = extract.nextToken(record, next_pos, more);		//Minimum of 1 extraction value - Mandatory

	if (more) {			//Slot value is in the 2nd field - optional
		slots = extract.nextToken(record, next_pos, more);
	}
	if (more) { // Stores Name of next task
		nextTask[0] = extract.nextToken(record, next_pos, more);
	}
	if (more) { // Stores Name of next task
		nextTask[1] = extract.nextToken(record, next_pos, more);
	}

	//Updates the field width
	field_width = extract.getFieldWidth();
}



//Matches each new task to task
bool Task::validate(const Task& task) {

	//Insures that true is returned if BOTH pointers are resolved/empty
	bool isValid = true;

	//Compares 'task' (parameter value) to the stored nextTask array
	if (task.getName() == nextTask[0] && (nextTask[0].empty() == false)) {
		this->pNextTask[0] = &task;
	}
	else if (task.getName() == nextTask[1] && (nextTask[1].empty() == false)) {
		this->pNextTask[1] = &task;
	}

	//checks if the pointer to EACH non-empty next task has been resolved
	for (int i = 0; i < 2; i++) {
		if ((nextTask[i].empty() == false) && pNextTask[0] == nullptr) {
			isValid = false;
		}
	}

	return isValid;
}



//Returns the name (First Field value)
const std::string& Task::getName() const {
	return this->name;
}



//Returns the number of product slots in the task(converted from a string to an unsigned integer)
unsigned int Task::getSlots() const {
	return stoi(slots);
}



//Returns the address of the next task associated with the parameter recieved
const Task* Task::getNextTask(Quality quantity) const {

	//Throws Error if empty(not resolved)
	if (pNextTask[quantity] == nullptr) {
		throw "*** Validate [" + this->nextTask[quantity] + "] @ [" + name + "] ***";
	}

	return pNextTask[quantity];
}



//Display the Task in a specific format
void Task::display(std::ostream& os) const {

	//Print out the task name
	os << "Task Name    : " << std::left << std::setw(field_width + 2) << "[" + name + "]" << " " <<
		"[" << slots << "]" << std::endl;

	//Continue if validated (Value exists in next Task)
	if (nextTask[0].empty() == false) {
		os << " Continue to : " << std::left << std::setw(field_width + 2) <<
			"[" + nextTask[0] + "]";

		//Appends a note that validation is still required
		if (pNextTask[0] == nullptr) {
			os << " *** to be validated ***";
		}
		os << std::endl;
	}

	//Redirect if validated (Value exists in next Task)
	if (nextTask[1].empty() == false) {
		os << " Redirect to : " << std::left << std::setw(field_width + 2) <<
			"[" + nextTask[1] + "]";
		//Appends a note that validation is still required
		if (pNextTask[1] == nullptr) {
			os << " *** to be validated ***";
		}
		os << std::endl;
	}
}



//Returns the field width currently stored for all objects in this class
size_t Task::getFieldWidth() {
	return field_width;
}



//Compares the two Tasks (parameters) for the same name
bool operator==(const Task& task_a, const Task& task_b) {
	return (task_a.getName() == task_b.getName());
}


