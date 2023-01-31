#include "HashItem.h"
#include <stdlib.h>
#include <malloc.h>

HashItem::HashItem(unsigned char* itemString) : itemStr{ itemString }, nextItemSort{ nullptr }, count{ 1 }, prevItemHT{ nullptr },
nextItemHT{ nullptr }, prevItemCollision{ nullptr }, nextItemCollision{ nullptr }, isroot{ false }, pos{ 0 }, chr1{ 0 }, chr1map{ 0 },
chr2{ 0 }, chr2map{ 0 } { }

HashItem::~HashItem() {
    free(itemStr);
}