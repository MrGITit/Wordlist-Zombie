#pragma once
#include "HashItem.h"

#define MAX_HT_SIZE 1073741824

class HashTable {
	unsigned int tableSize;
	HashItem **table;

	HashItem *firstItem;
	HashItem *lastItem;

	unsigned int itemCount;

	void rehash();

	//Merge Sort Stuff
	HashItem* GetEndHI(HashItem *start, unsigned int len);
	void mergeSort();
	HashItem* merge(HashItem* start1, HashItem* end1, HashItem* start2, HashItem* end2);
public:
	HashTable(unsigned int size);
	~HashTable();

	HashItem* createHashItem(unsigned char* itemStr) { return new HashItem(itemStr); }

	HashItem* getFirstItem() { return firstItem;  }
	void setFirstItem(HashItem* hi) { firstItem = hi; }
	HashItem* getLastItem() { return lastItem;  }
	void setLastItem(HashItem* hi) { lastItem = hi; }
	unsigned int getTableSize() { return tableSize; }
	unsigned int getItemCount() { return itemCount;  }
	void insertItem(unsigned char* itemString);
	void insertItem(HashItem* item);
	HashItem* findItem(unsigned char* itemString);
	void deleteItem(HashItem* item);
	void drawTable();
	void doMergeSort();
};
