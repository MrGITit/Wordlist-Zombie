#pragma once

class HashItem {
	unsigned char* itemStr;
	unsigned long long count;

	//Markov Chain Stuff
	bool isroot;
	unsigned long pos;
	unsigned long chr1;
	unsigned char chr1map;
	unsigned long chr2;
	unsigned char chr2map;

	HashItem* prevItemHT;
	HashItem* nextItemHT;

	HashItem* prevItemCollision;
	HashItem* nextItemCollision;

	HashItem* nextItemSort;

public:
	HashItem(unsigned char* itemString);
	~HashItem();

	bool getIsRoot() { return isroot; }
	void setIsRoot(bool ir) { isroot = ir; }

	unsigned long getPos() { return pos; }
	void setPos(unsigned long p) { pos = p; }

	unsigned long getChr1() { return chr1; }
	void setChr1(unsigned long c1) { chr1 = c1; }

	unsigned char getChr1Map() { return chr1map; }
	void setChr1Map(unsigned char c1m) { chr1map = c1m; }

	unsigned long getChr2() { return chr2; }
	void setChr2(unsigned long c2) { chr2 = c2; }

	unsigned char getChr2Map() { return chr2map; }
	void setChr2Map(unsigned char c2m) { chr2map = c2m; }

	unsigned char* getItemStr() { return itemStr; }

	unsigned long long getCount() { return count; }
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