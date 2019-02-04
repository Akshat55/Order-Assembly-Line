#include <algorithm>
#include "OrderManager.h"
#include "CustomerOrder.h"
#include "ItemManager.h"
#include "Item.h"



//Moves a customerOrder from the back of the base class container
CustomerOrder&& OrderManager::extract() {
	//Returns a move( reference to the last element in the vector) 
	return(std::move(std::vector<CustomerOrder>::back()));
}



//Checks that the items requested in the customer orders are available
void OrderManager::validate(const ItemManager& itemManager, std::ostream& os) {

	//Inserting a message into os for any item that is not available
	for (size_t x = 0; x < std::vector<CustomerOrder>::size(); x++) {
		bool exists = false;
		//Iterate through the number of orders
		for (size_t y = 0; y < std::vector<CustomerOrder>::at(x).noOrders(); y++) {

			//Find if item exists
			std::find_if(itemManager.cbegin(), itemManager.cend(), [&](const Item &val)->bool {
				exists = (val.getName() == std::vector<CustomerOrder>::at(x)[y]);
				return (val.getName() == std::vector<CustomerOrder>::at(x)[y]);
			});

			//Throws error if doesn't exist
			if (exists == false) {
				os << std::vector<CustomerOrder>::at(x)[y] << " is unavailable" << std::endl;
			}
		}

	}

}



//Inserts into os descriptions of each customer order in the base class container
void OrderManager::display(std::ostream& os) const {

	//Iterates through the vector and inserts os into the descriptions
	std::for_each(std::vector<CustomerOrder>::cbegin(), std::vector<CustomerOrder>::cend(), [&](const CustomerOrder &another) {
		another.display(os);
	});
}