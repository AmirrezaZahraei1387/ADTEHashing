//
// Created by KAVOSH on 1/5/2024.
//
#ifndef ADTEHASHING_HOPSCOTCHHASHERCORE_INL
#define ADTEHASHING_HOPSCOTCHHASHERCORE_INL
#include "HopScotchHasher.hpp"

// finds the hash id of the element and try to find it in the
// bound of MAX_DIST
template<typename HashObj>
int HopScotchHasher<HashObj>::findPos(const HashObj &element) {

    size_t pos{hash(element)};

    for(int i{0}; i< MAX_DIST; ++i){
        if(pos >= HopScTable.size())
            pos -= HopScTable.size();

        if(isActive(pos) && HopScTable[pos].element == element)
            return pos;
        ++pos;
    }

    return -1;
}

template<typename HashObj>
bool HopScotchHasher<HashObj>::isActive(int pos) {

    if(pos == -1){
        return false;
    }
    return HopScTable.at(pos).isActive;
}

template<typename HashObj>
size_t HopScotchHasher<HashObj>::hash(const HashObj &element) {
    return hashFunc(element, HopScTable.size());
}

template<typename HashObj>
void HopScotchHasher<HashObj>::rehash(size_t newSize) {
    std::vector<Node> oldHopScTable = HopScTable;

    HopScTable.resize(newSize);

    currentSize = 0;
    // resetting the table
    for(auto& node: HopScTable)
        node.isActive = false;

    for(auto& oldNode: oldHopScTable)
        if(oldNode.isActive)
            insert(oldNode.element);
}

template<typename HashObj>
bool HopScotchHasher<HashObj>::insert(const HashObj &element) {

    size_t pos{hash(element)};

    if(pos >= HopScTable.size()){
        rehash(pos+MAX_DIST);
    }

    // attempt to drag the element into the list
    // without moving anything
    for(int i{0}; i<MAX_DIST; ++i){
        if(HopScTable[pos].Hop[i] == 0 && !isActive(pos+i)){
            pos = pos + i;

            if(pos >= HopScTable.size()){
                rehash(pos);
                break;
            }

            HopScTable[pos - i].Hop[i] = true;
            HopScTable[pos].isActive = true;
            HopScTable[pos].element = element;
            ++currentSize;
            return true;
        }
    }

    //try to use moving the elements to make a spot
    for(int i{0}; i<MAX_DIST; ++i){
        if(HopScTable[pos].Hop[i] == false){
            int parentHash = hash(HopScTable[pos+i].element);
            int distance = (pos + i) - parentHash;

            for(int j{0}; j<MAX_DIST; ++j){
                if(!isActive(parentHash + j)){
                    HopScTable[parentHash + j].isActive = true;
                    HopScTable[parentHash + j].element = HopScTable[pos + i].element;

                    HopScTable[parentHash].Hop[j] = true;
                    HopScTable[parentHash].Hop[distance] = false;

                    clearPos(pos + i);
                    insert(element);
                    ++currentSize;
                    return true;
                }
            }
        }
    }

    return false;
}


template<typename HashObj>
bool HopScotchHasher<HashObj>::insert(HashObj &&element) {
    size_t pos{hash(element)};

    if(pos >= HopScTable.size()){
        rehash(pos+MAX_DIST);
    }

    // attempt to drag the element into the list
    // without moving anything
    for(int i{0}; i<MAX_DIST; ++i){
        if(HopScTable[pos].Hop[i] == false && !isActive(pos+i)){
            pos = pos + i;

            if(pos >= HopScTable.size()){
                rehash(pos);
                break;
            }

            HopScTable[pos - i].Hop[i] = true;
            HopScTable[pos].isActive = true;
            HopScTable[pos].element = std::move(element);

            ++currentSize;
            return true;
        }
    }

    //try to use moving the elements to make a spot
    for(int i{0}; i<MAX_DIST; ++i){
        if(HopScTable[pos].Hop[i] == false){
            int parentHash = hash(HopScTable[pos+i].element);
            int distance = (pos + i) - parentHash;

            for(int j{0}; j<MAX_DIST; ++j){
                if(!isActive(parentHash + j)){
                    HopScTable[parentHash + j].isActive = true;
                    HopScTable[parentHash + j].element = HopScTable[pos + i].element;

                    HopScTable[parentHash].Hop[j] = true;
                    HopScTable[parentHash].Hop[distance] = false;

                    clearPos(pos + i);
                    insert(std::move(element));

                    ++currentSize;
                    return true;
                }
            }
        }
    }


    return false;
}


template<typename HashObj>
void HopScotchHasher<HashObj>::clearPos(size_t pos) {
    HopScTable[pos].isActive = false;
    HopScTable[pos].Hop[0] = 0;
}


#endif //ADTEHASHING_HOPSCOTCHHASHERCORE_INL
