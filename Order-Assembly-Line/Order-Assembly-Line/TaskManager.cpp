#include <algorithm>
#include "TaskManager.h"
#include "Task.h"
#include "ItemManager.h"
#include "Item.h"



//Validates each task against all of the other tasks in the base class container.
void TaskManager::validate(std::ostream& os) {
	//Inserts a message into os if not all tasks have been validated.
	for (size_t x = 0; x < std::vector<Task>::size(); x++) {
		for (size_t y = 0; y < std::vector<Task>::size(); y++) {
			//Ignores the same task
			if (x != y) {
				std::vector<Task>::at(x).validate(std::vector<Task>::at(y));
			}
		}
	}
}



//Checks that the tasks assigned to handle each item managed by itemManager are tasks in the base class container.
void TaskManager::validate(const ItemManager& itemManager, std::ostream& os) {

	//If a task is not in the container, then this function inserts a message into os that that task is not available.
	//Check the item Names
	for (size_t x = 0; x < itemManager.size(); x++) {
		bool exists = false;

		int counter = 0;
		//Iterates through the Task Vector
		std::find_if(std::vector<Task>::cbegin(), std::vector<Task>::cend(), [&](const Task& val) {
			exists = (std::vector<Task>::at(counter).getName() == itemManager.at(x).getName());
			counter++;
			return exists;
		});

		//Inserts a message in os if item is not available
		if (exists == false) {
			os << itemManager.at(x).getName() << " is unavailable" << std::endl;
		}
	}

	//Check the remover
	for (size_t x = 0; x < itemManager.size(); x++) {
		bool exists = false;

		int counter = 0;
		//Iterates through the Task Vector
		std::find_if(std::vector<Task>::cbegin(), std::vector<Task>::cend(), [&](const Task& val) {
			exists = (std::vector<Task>::at(counter).getName() == itemManager.at(x).getRemover());
			counter++;
			return exists;
		});

		//Inserts a message in os if item is not available
		if (exists == false) {
			os << itemManager.at(x).getName() << " is unavailable" << std::endl;
		}
	}
}



//Inserts into the referenced ostream object descriptions of the tasks stored in tasks
void TaskManager::display(std::ostream& os) const {
	//Iterate through all of the vectors
	std::for_each(std::vector<Task>::cbegin(), std::vector<Task>::cend(), [&](const Task &another) {
		another.display(os);
	});
}







