#pragma once

#include <string>

using namespace std;

class Item
{
public:

	Item() : price(0)
	{

	}

	Item(string in_article, string in_vendor, string in_name, uint32_t in_price) : article(in_article), vendor(in_vendor),
		name(in_name), price(in_price)
	{

	}

	/** Article of item */
	string article;

	/** Vendor of item */
	string vendor;

	/** Name of item */
	string name;

	/** Price of item */
	uint32_t price;
};
