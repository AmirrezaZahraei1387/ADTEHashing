//
// Created by KAVOSH on 1/5/2024.
//
#ifndef ADTEHASHING_HOPSCOTCHHASHER_HPP
#define ADTEHASHING_HOPSCOTCHHASHER_HPP
#include <functional>
#include <cstddef>
#include <vector>
#include <array>


template<typename HashObj>
class HopScotchHasher{
public:
    using HashFunctionT = std::function<size_t(const HashObj&, size_t)>;

    explicit HopScotchHasher(int capacity, HashFunctionT hf);

    bool insert(const HashObj& element);
    bool insert(HashObj&& element);

    bool contain(const HashObj& element);
    void makeEmpty();
    size_t getSize();
    bool remove(const HashObj& element);

private:

    static constexpr int MAX_DIST{6};
    HashFunctionT hashFunc;
    int currentSize{0};
    struct Node{
        HashObj element{};
        std::array<bool, MAX_DIST> Hop{false};
        bool isActive{};
    };
    std::vector<Node> HopScTable;

    size_t hash(const HashObj& element);
    void rehash(size_t newSize);
    int findPos(const HashObj& element);
    bool isActive(int pos);
    void clearPos(size_t pos);
};

#include "HopScotchHasherCore.inl"
#include "HopScotchHasherInter.inl"

#endif //ADTEHASHING_HOPSCOTCHHASHER_HPP
