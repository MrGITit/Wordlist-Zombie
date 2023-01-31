#include "HashTable.h"
#include "fnv.h"
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

HashTable::HashTable(unsigned int size) {
	tableSize = size;
	itemCount = 0;
	table = (HashItem**)calloc(size, sizeof(HashItem*));
	firstItem = nullptr;
	lastItem = nullptr;
}

HashTable::~HashTable() {
	HashItem* itm = firstItem;
	while (itm->getNextItemHT() != nullptr) {
		HashItem* nextItm = itm->getNextItemHT();
		delete itm;
		itm = nextItm;
	}
	free(table);
}

void HashTable::insertItem(unsigned char* itemString) {
	HashItem* hs = new HashItem(itemString);
	insertItem(hs);
}

void HashTable::insertItem(HashItem* item) {
	//First Try finding, then insert.
	HashItem* hi = findItem(item->getItemStr());
	if (hi != nullptr) {
		//Found it!
		hi->incCount();
		delete item;
		return;
	}

	unsigned int indX = fnv_32a_str((char*)item->getItemStr(), 0) % tableSize;

	//Insert into hashtable
	hi = table[indX];
	if (hi == 0) {
		//No Collision!  EZ PZ
		table[indX] = item;
	}
	else {
		//COLLISION! Follow the linked list!
		while (hi->getNextItemCollision() != nullptr) {
			hi = hi->getNextItemCollision();
		}

		//hi should now be the last item in the linked list
		hi->setNextItemCollision(item);
		item->setPrevItemCollision(hi);
	}

	//Next insert into the big hashtable linked list
	if (firstItem == nullptr) {
		//This is the only item in the linked list so set firstItem and lastItem to item
		firstItem = item;
		lastItem = item;
	}
	else {
		lastItem->setNextItemHT(item);
		item->setPrevItemHT(lastItem);
		lastItem = item;
	}
	itemCount++;

	//check if we should rehash or not.
	if ((tableSize <= itemCount) && (tableSize < MAX_HT_SIZE)) rehash();
}


HashItem* HashTable::findItem(unsigned char* itemString) {
	unsigned int indX = fnv_32a_str((char*)itemString, 0) % tableSize;

	HashItem* hi = table[indX];
	if (hi == 0) {
		//Not found!
		return nullptr;
	}
	else {
		//Found Something!  Lets look a little closer.
		if (strcmp((const char*)hi->getItemStr(), (const char*)itemString) == 0) return hi;

		while (hi->getNextItemCollision() != nullptr) {
			hi = hi->getNextItemCollision();
			if (strcmp((const char*)hi->getItemStr(), (const char*)itemString) == 0) return hi;
		}

		//If we made it this far then we didn't find it
		return nullptr;
	}
}

void HashTable::deleteItem(HashItem* item) {
	//First we have to do is find the item in the hash table.  The quickest way to do this is through the hash function.
	unsigned int indX = fnv_32a_str((char*)item->getItemStr(), 0) % tableSize;

	HashItem* hi = table[indX];
	if (hi == 0) {
		//Not found! (This shouldn't happen but we will handle it anyway)
	}
	else {
		//Found Something!  Lets look a little closer.
		if (hi == item) {
			if (item->getNextItemCollision() == nullptr) {
				//This is the only item. (No Collision) Lets just remove it from the hashTable, and move on.
				table[indX] = 0;
			}
			else {
				//This is the first item of a collision, lets patch this baby up and move on.
				table[indX] = item->getNextItemCollision();
				item->getNextItemCollision()->setPrevItemCollision(nullptr);
			}
		}
		else {
			while (hi->getNextItemCollision() != nullptr) {
				hi = hi->getNextItemCollision();
				if (hi == item) {
					//This is in the middle of or at the end of a collision linked list.  Patch it back together!
					item->getPrevItemCollision()->setNextItemCollision(item->getNextItemCollision());
					if (item->getNextItemCollision() != nullptr) {
						item->getNextItemCollision()->setPrevItemCollision(item->getPrevItemCollision());
					}
				}
			}
		}
	}
	//Now just remove it from the big linked list
	if (firstItem == item) firstItem = item->getNextItemHT();
	if (lastItem == item) lastItem = item->getPrevItemHT();
	if (item->getPrevItemHT() != nullptr) item->getPrevItemHT()->setNextItemHT(item->getNextItemHT());
	if (item->getNextItemHT() != nullptr) item->getNextItemHT()->setPrevItemHT(item->getPrevItemHT());

	itemCount--;
}

void HashTable::rehash() {
	std::cout << "Table Getting Full.  Rehashing....\n";
	free(table);

	tableSize = tableSize * 2;
	if (tableSize > MAX_HT_SIZE) tableSize = MAX_HT_SIZE;
	table = (HashItem**)calloc(tableSize, sizeof(HashItem*));

	HashItem* htItem = firstItem;

	while (htItem != nullptr) {
		unsigned int indX = fnv_32a_str((char*)htItem->getItemStr(), 0) % tableSize;

		//First insert into hashtable
		HashItem* hi = table[indX];
		if (hi == 0) {
			//No Collision!  EZ PZ
			table[indX] = htItem;
			htItem->setPrevItemCollision(nullptr);
			htItem->setNextItemCollision(nullptr);
		}
		else {
			//COLLISION! Follow the linked list!
			while (hi->getNextItemCollision() != nullptr) {
				hi = hi->getNextItemCollision();
			}

			//hi should now be the last item in the linked list
			hi->setNextItemCollision(htItem);
			htItem->setPrevItemCollision(hi);
			htItem->setNextItemCollision(nullptr);
		}
		htItem = htItem->getNextItemHT();
	}
}

void HashTable::drawTable() {
	for (int i = 0; i < tableSize; i++) {
		char* draw;
		if (table[i]) draw = (char*)"#";
		else draw = (char*)"0";
		std::cout << draw;
	}
	std::cout << "\n";
}

HashItem* HashTable::GetEndHI(HashItem* start, unsigned int len) {
	HashItem* result = start;

	for (int i = 0; i < len; i++) {
		if (result != nullptr) result = result->getNextItemHT();
	}

	return result;
}

void HashTable::mergeSort() {
	HashItem* head = firstItem;
	HashItem* currentSpot = nullptr;
	unsigned int len = 1;
	bool firstGo = true;

	while (len <= itemCount) {
		firstGo = true;
		HashItem* hi = head;
		while (hi != nullptr) {
			HashItem* start1 = hi;
			HashItem* end1 = GetEndHI(start1, len);
			HashItem* start2 = nullptr;
			HashItem* end2 = nullptr;

			if (end1 != nullptr) {
				start2 = end1;
				end2 = GetEndHI(start2, len);
			}

			HashItem* tmphi = merge(start1, end1, start2, end2);

			if (firstGo) {
				head = tmphi;
				firstGo = false;
				currentSpot = tmphi;
				while (currentSpot->getNextItemSort() != nullptr) currentSpot = currentSpot->getNextItemSort();
			}
			else {
				currentSpot->setNextItemSort(tmphi);
				while (currentSpot->getNextItemSort() != nullptr) currentSpot = currentSpot->getNextItemSort();
			}

			hi = GetEndHI(hi, len * 2);

		}

		//Do some copying of linked lists
		HashItem* fixor = head;
		while (fixor->getNextItemSort() != nullptr) {
			fixor->setNextItemHT(fixor->getNextItemSort());
			fixor = fixor->getNextItemSort();
		}
		fixor->setNextItemHT(nullptr);

		fixor = head;
		while (fixor->getNextItemHT() != nullptr) {
			fixor->setNextItemSort(nullptr);
			fixor = fixor->getNextItemHT();
		}
		fixor->setNextItemSort(nullptr);

		if (len == itemCount) break;
		len = len * 2;
		if (len > itemCount) len = itemCount;
	}
	firstItem = head;
}


HashItem* HashTable::merge(HashItem* start1, HashItem* end1, HashItem* start2, HashItem* end2)
{
	HashItem* tmplist = nullptr;
	HashItem* tmplistIterator = nullptr;

	if (start2 != nullptr) {
		while ((start1 != end1) && (start2 != end2)) {
			if (start1->getCount() >= start2->getCount()) {
				if (tmplist == nullptr) {
					tmplist = tmplistIterator = start1;
					start1 = start1->getNextItemHT();
					continue;
				}
				else {
					tmplistIterator->setNextItemSort(start1);
					tmplistIterator = start1;
					start1 = start1->getNextItemHT();
					continue;
				}
			}
			else {
				if (tmplist == nullptr) {
					tmplist = tmplistIterator = start2;
					start2 = start2->getNextItemHT();
					continue;
				}
				else {
					tmplistIterator->setNextItemSort(start2);
					tmplistIterator = start2;
					start2 = start2->getNextItemHT();
					continue;
				}
			}
		}
	}
	//cleanup
	while (start1 != end1) {
		if (tmplist == nullptr) {
			tmplist = tmplistIterator = start1;
			start1 = start1->getNextItemHT();
			continue;
		}
		else {
			tmplistIterator->setNextItemSort(start1);
			tmplistIterator = start1;
			start1 = start1->getNextItemHT();
			continue;
		}
	}
	//more cleanup

	if (start2 != nullptr) {
		while (start2 != end2) {
			if (tmplist == nullptr) {
				tmplist = tmplistIterator = start2;
				start2 = start2->getNextItemHT();
				continue;
			}
			else {
				tmplistIterator->setNextItemSort(start2);
				tmplistIterator = start2;
				start2 = start2->getNextItemHT();
				continue;
			}
		}
	}

	return tmplist;
}

void HashTable::doMergeSort()
{
	mergeSort();
	HashItem* hi = firstItem;
	hi->setPrevItemHT(nullptr);

	//Fix the Prev linking of Linked List
	while (hi != nullptr) {
		HashItem* hiya = hi->getNextItemHT();
		if (hiya != nullptr) hiya->setPrevItemHT(hi);
		else lastItem = hi;
		hi = hi->getNextItemHT();
	}
}
