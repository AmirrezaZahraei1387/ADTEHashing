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
    int pos{findPos(element)};

    if(pos == -1){
        return false;
    }

    HopScTable[static_cast<size_t>(pos)].isActive = false;
    --currentSize;
    return true;
}

template<typename HashObj>
HopScotchHasher<HashObj>::HopScotchHasher(int capacity, HopScotchHasher::HashFunctionT hf)
: HopScTable(capacity),
hashFunc(hf)
{}

template<typename HashObj>
void HopScotchHasher<HashObj>::printTable() {
    for(auto& x: HopScTable){
        std::cout<<x.isActive<<' ';
        std::cout<<x.element<<' ';
            for(auto i: x.Hop)
                std::cout<<i;
            std::cout<<std::endl;

    }
    std::cout<<"table size: "<<currentSize<<std::endl;
}

#endif //ADTEHASHING_HOPSCOTCHHASHERINTER_INL
