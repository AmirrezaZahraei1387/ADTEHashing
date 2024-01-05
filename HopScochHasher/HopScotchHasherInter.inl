//
// Created by KAVOSH on 1/5/2024.
//

#ifndef ADTEHASHING_HOPSCOTCHHASHERINTER_INL
#define ADTEHASHING_HOPSCOTCHHASHERINTER_INL
#include "HopScotchHasher.hpp"

template<typename HashObj>
bool HopScotchHasher<HashObj>::contain(const HashObj &element) {
    size_t pos{findPos(element)};
    return isActive(pos);
}

template<typename HashObj>
void HopScotchHasher<HashObj>::makeEmpty() {
    for(auto& x: HopScTable){
        x.isActive = false;
        for(auto& t: x.Hop)
            t = false;
    }
}

template<typename HashObj>
size_t HopScotchHasher<HashObj>::getSize() {
    return currentSize;
}

template<typename HashObj>
bool HopScotchHasher<HashObj>::remove(const HashObj &element) {
    size_t pos{hash(element)};

    for(int i{0}; i< MAX_DIST; ++i){
        if(HopScTable[pos].Hop[i] == true && HopScTable[pos + i].element == element) {
            HopScTable[pos + i].isActive = false;
            HopScTable[pos+i].Hop[i] = false;
            --currentSize;
            return true;
        }
    }

    return false;
}

template<typename HashObj>
HopScotchHasher<HashObj>::HopScotchHasher(int capacity, HopScotchHasher::HashFunctionT hf)
: HopScTable(capacity),
hashFunc(hf)
{}

#endif //ADTEHASHING_HOPSCOTCHHASHERINTER_INL
