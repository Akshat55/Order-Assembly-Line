#include <vector>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"
#include "CustomerItem.h"
#include "Item.h"

size_t CustomerOrder::field_width = 1;


//Constructor
CustomerOrder::CustomerOrder(const std::string& record) {
	this->order = nullptr;		//Initializes array to a safe address
	this->nOrders = 0;			//Initializes the number of customer items to 0

								//Uses Utilities object to extract information from the referenced string							
	size_t next_pos = 0;
	bool more = true;

	Utilities extraction;
	extraction.setFieldWidth(field_width);	//Pass the static variable

	this->name = extraction.nextToken(record, next_pos, more);

	if (more) { product = extraction.nextToken(record, next_pos, more); }

	//Store the products into the vector -- Saves time isntead of counting num of products, then assigning
	std::vector<std::string> holder;
	std::string receiver;
	while (more) {
		receiver = extraction.nextToken(record, next_pos, more);
		if (!receiver.empty()) {
			holder.push_back(receiver);
		}
	}

	nOrders = holder.size();			//Update the size
	order = new CustomerItem[holder.size()];
	for (size_t i = 0; i < holder.size(); i++) {
		order[i] = holder.at(i);				//Assigning to the array
	}

	field_width = extraction.getFieldWidth();
}



//Customer orders are not to be duplicated, the copy constructor should never be called
CustomerOrder::CustomerOrder(const CustomerOrder& other) {
	//NO COPY CONSTRUCTOR SHOULD EVER BE CALLED
	throw std::string("Customers orders should not be duplicated");
}



//Move constructor
CustomerOrder::CustomerOrder(CustomerOrder&& another) NOEXCEPT {
	//Call move assignment operator
	*this = std::move(another);
}



//Move assignment operator
CustomerOrder&& CustomerOrder::operator=(CustomerOrder&& another) NOEXCEPT {
	//Check for self assignment
	if (this != &another) {
		this->name = another.name;
		this->product = another.product;
		this->order = another.order;
		this->nOrders = another.nOrders;
		another.order = nullptr;
		another.nOrders = 0;
	}
	return std::move(*this);
}



//Returns true if the current object is in a safe empty state
bool CustomerOrder::empty() const {
	return (name.empty() || order == nullptr);
}



//Returns the number of customer items in the current object
unsigned int CustomerOrder::noOrders() const {
	return this->nOrders;
}



//Returns a reference to the name of customer item i; reports an exception if the index is out of bounds
const std::string& CustomerOrder::operator[](unsigned int index) const {
	if (index >= this->nOrders) {
		throw "Index out of bounds!";
	}
	return order[index].getName();
}



//Searches through the customer items and fills those order for the customer items identified by item if any have not been filled.
//This function increments item's code for each customer item filled.
//This keeps the item code unique for each order.
void CustomerOrder::fill(Item& item) {
	for (size_t i = 0; i < this->nOrders; i++) {
		if (order[i].asksFor(item)) {		//Compare current object at i to paramter item
			order[i].fill(item.getCode());
			item++;		//Increment the code
		}
	}

}



//Searches through the customer items and removes those items identified by the name of item if the corresponding part of the order has been filled.This function does not alter the item's code
void CustomerOrder::remove(Item &item) {
	for (size_t i = 0; i < this->nOrders; i++) {
		if (order[i].asksFor(item)) {
			if (!order[i].isFilled()) {
				std::vector <CustomerItem> another;
				//Save information other than the values to be removed
				for (size_t counter = 0; counter < nOrders; i++) {
					if (counter != i) {
						another.push_back(order[i]);
					}
				}
				//Reassignment/Reallocation
				delete[] order;
				order = nullptr;
				nOrders--;
				order = new CustomerItem[nOrders];
				for (size_t counter = 0; counter < nOrders; i++) {
					order[counter] = another.at(counter);
				}
				another.clear();
			}
		}
	}
}



//Deconstructor
CustomerOrder::~CustomerOrder() {
	delete[] this->order;
	order = nullptr;
}



//Prints name, product and item(s) in a specific format
void CustomerOrder::display(std::ostream& os) const {

	os << std::left << std::setfill(' ') << std::setw(field_width) << name << " : " <<
		std::left << std::setfill(' ') << std::setw(field_width) << product << std::endl;

	//Iterate through the array and call the display function
	for (size_t i = 0; i < nOrders; i++) {
		order[i].display(os);
	}
}



