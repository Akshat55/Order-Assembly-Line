#pragma once

#include <iostream>
#include <vector>

class Item;

class ItemManager : public std::vector<Item> {
public:
	void display(std::ostream&, bool = false) const;
};