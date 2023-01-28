#pragma once

#include "HashItem.h"
#include <stdlib.h>
#include <malloc.h>

HashItem::HashItem(unsigned char* itemString) : itemStr{ itemString }, nextItemSort{ nullptr }, count{ 1 }, prevItemHT{ nullptr },
nextItemHT{ nullptr }, prevItemCollision{ nullptr }, nextItemCollision{ nullptr } { }

HashItem::~HashItem() {
    free(itemStr);
}