#include "pch.h"
#include "ItemStorageTest.h"

#include "ItemStorage.h"

bool ItemStorageTest::RunTest()
{
	ItemStorage Storage;

	Storage.add_item(make_shared<Item>("art_1", "ven_1", "item1", 0));
	Storage.add_item(make_shared<Item>("art_2", "ven_1", "item2", 0));

	if (Storage.get_items_by_vendor("ven_1").size() != 2)
	{
		printf("get_items_by_vendor (ven_1) expected to be 2\n");
		return false;
	}

	if (Storage.get_item_by_article("art_1") == nullptr)
	{
		printf("get_item_by_article == nullptr\n");
		return false;
	}

	if (Storage.get_item_by_article("art_1")->article != "art_1")
	{
		printf("get_item_by_article invalid result\n");
		return false;
	}

	if (Storage.get_item_by_article("art_3") != nullptr)
	{
		printf("get_item_by_article invalid result for non-existing object\n");
		return false;
	}

	// Removal
	Storage.remove_item_by_article("art_1");

	if (Storage.get_item_by_article("art_1") != nullptr)
	{
		printf("remove_item_by_article failed\n");
		return false;
	}

	if (Storage.get_items_by_vendor("ven_1").size() != 1)
	{
		printf("get_items_by_vendor (ven_1) expected to be 1 after removal\n");
		return false;
	}

	printf("Storage test passed\n");
	return true;
}
