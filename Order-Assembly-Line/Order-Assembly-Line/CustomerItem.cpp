#include <iomanip>
#include "CustomerItem.h"
#include "Item.h"


//Constructor
CustomerItem::CustomerItem(const std::string& record) {
	this->name = record;
	this->filled = false;
	this->code = 0;

	//If Name is empty, set to safe empty state
	if (record.empty()) {
		name = "";
	}
}



//Returns true if the current object asks for item; false otherwise
bool CustomerItem::asksFor(const Item& item) const {
	return (this->name == item.getName());
}



//returns true if the current object's request has been filled
bool CustomerItem::isFilled() const {
	return filled;
}



//sets the item code for the current object to the value received and switches the status of the current object to filled
void CustomerItem::fill(const unsigned int c) {
	this->code = c;
	this->filled = true;
}



//Resets the item code for the current object to 0 and resets the status of the current object to not filled
void CustomerItem::clear() {
	this->code = 0;
	this->filled = false;
}



//Returns the name of the Item
const std::string& CustomerItem::getName() const {
	return this->name;
}



//Prints out the boolValue(Symbol), code and name in a specific format
void CustomerItem::display(std::ostream& os) const {

	//Checks if the item is filled and add the preceeding symbol
	os << " " << (this->isFilled() ? '+' : '-') << " " <<
		"[" << std::setfill('0') << std::right << std::setw(CODE_WIDTH) << code << "] " <<
		name << std::endl;
}
