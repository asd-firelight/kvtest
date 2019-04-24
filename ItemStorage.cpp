#include "pch.h"
#include "ItemStorage.h"

/** Removes item by article */
void ItemStorage::remove_item_by_article(string article)
{
	auto found = items_by_article.find(article);

	if (found != items_by_article.end())
	{
		auto item = found->second;
		items_by_article.erase(found);

		auto iterator = items_by_vendor.find(item->vendor);
		for (auto it = iterator; it != items_by_vendor.end(); it++)
		{
			if (it->second == item)
			{
				items_by_vendor.erase(it);
				break;
			}
		}
	}
}

/** Returns item with specified article or nullptr if none found */
shared_ptr<const Item> ItemStorage::get_item_by_article(string article)
{
	shared_lock<shared_mutex> lock(mutex_items_by_article);

	auto found = items_by_article.find(article);

	if (found != items_by_article.end())
	{
		return found->second;
	}

	return nullptr;
}

/** Returns items of specified vendor */
std::vector<shared_ptr<const Item>> ItemStorage::get_items_by_vendor(string vendor)
{
	shared_lock<shared_mutex> lock(mutex_items_by_vendor);

	std::vector<shared_ptr<const Item>> items;

	auto iterator = items_by_vendor.find(vendor);
	for (auto it = iterator; it != items_by_vendor.end(); it++)
	{
		items.push_back(it->second);
	}

	return items;
}

/** Adds specified item to storage */
void ItemStorage::add_item(shared_ptr<Item> item)
{
	// Invalid item
	if (item == nullptr)
	{
		return;
	}

	// Already added
	if (get_item_by_article(item->article) == item)
	{
		return;
	}

	unique_lock<shared_mutex> lock(mutex_items_by_article);
	{
		unique_lock<shared_mutex> lock2(mutex_items_by_vendor);

		items_by_article.insert(std::make_pair(item->article, item));
		items_by_vendor.insert(std::make_pair(item->vendor, item));
	}
}

void ItemStorage::debug_print()
{
	{
		shared_lock<shared_mutex> lock(mutex_items_by_article);

		for (auto it = items_by_article.begin(); it != items_by_article.end(); it++)
		{
			printf("ART. %s, item %s [vendor %s]\n", it->first.c_str(), it->second->name.c_str(), it->second->vendor.c_str());
		}
	}

	{
		shared_lock<shared_mutex> lock(mutex_items_by_vendor);

		for (auto it = items_by_vendor.begin(); it != items_by_vendor.end(); it++)
		{
			printf("VEN. %s, item %s [art %s]\n", it->first.c_str(), it->second->name.c_str(), it->second->article.c_str());
		}
	}
}
