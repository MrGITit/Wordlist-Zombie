#pragma once

class HashItem {
	unsigned char *itemStr;
	unsigned int count;

	HashItem *prevItemHT;
	HashItem *nextItemHT;

	HashItem *prevItemCollision;
	HashItem *nextItemCollision;

	HashItem *nextItemSort;

public:
	HashItem(unsigned char* itemString);
	~HashItem();

	unsigned char* getItemStr() { return itemStr; }

	unsigned int getCount() { return count; }
	void incCount() { count++; }

	HashItem* getNextItemSort() { return nextItemSort; }
	void setNextItemSort(HashItem* nItemSort) { nextItemSort = nItemSort; }

	HashItem* getPrevItemHT() { return prevItemHT; }
	void setPrevItemHT(HashItem* pItemHT) { prevItemHT = pItemHT; }

	HashItem* getNextItemHT() { return nextItemHT; }
	void setNextItemHT(HashItem* nItemHT) { nextItemHT = nItemHT; }

	HashItem* getPrevItemCollision() { return prevItemCollision; }
	void setPrevItemCollision(HashItem* pItemCol) { prevItemCollision = pItemCol; }

	HashItem* getNextItemCollision() { return nextItemCollision; }
	void setNextItemCollision(HashItem* nItemCol) { nextItemCollision = nItemCol; }
};
