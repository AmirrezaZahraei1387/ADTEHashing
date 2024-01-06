//
// Created by KAVOSH on 1/6/2024.
//
#ifndef ADTEHASHING_EXTENDIBLEHASHER_HPP
#define ADTEHASHING_EXTENDIBLEHASHER_HPP
#include <vector>
#include <set>
#include <iostream>
#include <cstddef>
#include <functional>



template<typename Comparable, int MAX_TABL>
class ExtendibleHasher{
public:
    using HashFunctionT = std::function<size_t(const Comparable&, size_t)>;

    void printTable(){
        for(auto& x: ExHTable){
            std::cout<<"new table : "<<x.hashId<<std::endl;
            for(auto& y: x.tabl){
                std::cout<<y<<std::endl;
            }
        }
    }

private:

    struct Entry{
        size_t hashId{};
        std::set<Comparable> tabl;
    };


    HashFunctionT hashFunc;
    size_t currentSize{0};
    std::vector<Entry> ExHTable;

    size_t hash(const Comparable& element){
        return hashFunc(element, ExHTable.size());
    }

    bool splitEntry(size_t index,const Comparable& prior){


        for(const auto& x: ExHTable[index].tabl){
            if(prior <= x){

                Entry entry1{};
                Entry entry2{};
                size_t split_origin;
                split_origin = hash(x);

                // setting the new hashIds
                entry1.hashId = split_origin;
                entry2.hashId = ExHTable[index].hashId;

                // inserting the items
                for(auto& m: ExHTable[index].tabl){
                    if(prior < m){
                        entry1.tabl.insert(m);
                    }else{
                        entry2.tabl.insert(m);
                    }
                }

                removeEntry(index);
                // inserting new entries
                ExHTable.insert(std::next(std::begin(ExHTable), index), entry2);
                ExHTable.insert(std::next(std::begin(ExHTable), index + 1), entry1);
                return true;
            }
        }

        return false;
    }

    void removeEntry(size_t index){
        ExHTable.erase(std::next(ExHTable.begin(), index), std::next(ExHTable.begin(), index + 1));
    }

    //int findPos(const Comparable& element);
};



#endif //ADTEHASHING_EXTENDIBLEHASHER_HPP
