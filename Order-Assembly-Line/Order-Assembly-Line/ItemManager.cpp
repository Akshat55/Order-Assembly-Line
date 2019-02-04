#include <algorithm>
#include "ItemManager.h"
#include "Item.h"



//Inserts into os descriptions of each item stored in the base class container.
//The bool parameter specifies whether a full description of the item should be inserted.
void ItemManager::display(std::ostream& os, bool isTrue) const {

	for_each(std::vector<Item>::cbegin(), std::vector<Item>::cend(), [&](const Item &another) {
		another.display(os, isTrue);
	});
}
