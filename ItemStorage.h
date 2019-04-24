#pragma once

#include "Item.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <shared_mutex>


class ItemStorage
{
public:

	/** Removes item by article */
	void remove_item_by_article(string article);

	/** Returns item with specified article or nullptr if none found */
	shared_ptr<const Item> get_item_by_article(string article);

	/** Returns items of specified vendor */
	std::vector<shared_ptr<const Item>> get_items_by_vendor(string vendor);

	/** Adds specified item to storage */
	void add_item(shared_ptr<Item> item);

	/** Prints contents of storage to console. */
	void debug_print();

protected:

	/** Mutex used for items_by_article access */
	shared_mutex mutex_items_by_article;

	/** Mutex used for items_by_vendor access */
	shared_mutex mutex_items_by_vendor;

	/** Items by article */
	unordered_map<string, shared_ptr<Item>> items_by_article;

	/** Items by vendor */
	multimap<string, shared_ptr<Item>> items_by_vendor;
};
