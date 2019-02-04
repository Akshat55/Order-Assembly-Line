#include <iomanip>
#include "Item.h"
#include "Utilities.h"


size_t Item::field_width = 1;

//Constructor
Item::Item(const std::string& record) :description("no detailed description"), code(1) {

	//Initialization
	size_t next_pos = 0;
	bool more = true;

	Utilities extraction;
	extraction.setFieldWidth(field_width);	//Pass the static variable
	try {
		//First token as the name of the item --> Reporting an exception if no name has been specified
		this->name = extraction.nextToken(record, next_pos, more);
		//Second token as the naem of the filler task taht inserts the item into a product
		//Reports exception if no task has been specified
		if (more) { this->filler = extraction.nextToken(record, next_pos, more); }

		//Retrieve the field_width
		field_width = extraction.getFieldWidth();

		//Third token as the name of the remover task that extracts the item from a product
		//Reports exception if no task has been specified
		if (more) { this->remover = extraction.nextToken(record, next_pos, more); }
		//Fourth token is the integer holding the code to be printed on teh item's first insertion into a product
		if (more) { this->code = std::stoi(extraction.nextToken(record, next_pos, more)); }
		//Fifth token is the detailed description of the item
		if (more) { this->description = extraction.nextToken(record, next_pos, more); }

		//Ensures if description is empty a message is still visible
		if (description.empty()) {
			description = "no detailed description";
		}

		//Checks the values, throws exception if anyone of them are missing
		if (name.empty() == true || filler.empty() == true || remover.empty() == true) {
			throw record + "<-- *** no token found before the delimiter ***";
		}

	}
	catch (std::string error) {		//Utilities throws error if malformed
		throw error;				//Passes error on 
	}
}



//Checks if the current object is in safe empty state
bool Item::empty() const {
	return name.empty();
}



//Increments the code to be printed on the next insertion and returns the value before incrementation.
Item& Item::operator++(int num) {
	Item temp = *this;
	code++;
	return temp;
}



//Returns an unmodifiable reference to the string that contains the name of the item
const std::string& Item::getName() const {
	return this->name;
}



//Returns an unmodifiable reference to the string that contains the name of the task that inserts the item into a product
const std::string& Item::getFiller() const {
	return this->filler;
}



//Returns an unmodifiable reference to the string that contains the name of the task that extracts the item from a product
const std::string& Item::getRemover() const {
	return this->remover;
}



//Returns a copy of the code to be printed on the next insertion into a product
unsigned int Item::getCode() const {
	return this->code;
}



//Prints out the Item Information (Name, code, filler, remover, and description) in a specific format
void Item::display(std::ostream& os, bool full) const {

	os << std::setw(field_width) << std::left << std::setfill(' ') << name << " [" <<
		std::right << std::setfill('0') << std::setw(CODE_WIDTH) << code << "]";

	//if Full == true, displays additional information
	if (full) {
		os << " From " << std::left << std::setfill(' ') << std::setw(field_width) << filler <<
			" To " << std::left << std::setw(field_width) << remover << std::endl <<
			std::setw(field_width + CODE_WIDTH + 4) << std::right << ": " << description;
	}

	os << std::left << std::endl;
}


