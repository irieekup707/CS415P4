//
//  hash.cpp
//  CS415P4
//
//  Created by Will Lucic on 5/7/19.
//  Copyright © 2019 supersaiyansubtlety. All rights reserved.
//

#include "hash.hpp"

hash::hash(int k, int n, int cap) : k(k), n(n), cap(cap)
{
    table.resize(k);
}

void hash::insert(int i, int j, int val)
{
    assert(contains(i, j) == -1);
    auto index = h_func(i, j);
    table[index].insert(std::make_pair((std::make_pair(i, j)), val));
}

int hash::contains(int i, int j)
{
    auto index = h_func(i, j);
    auto found = table[index].find(std::make_pair(i, j));
    if (found == table[index].end()) { return -1; }
    else { return found->second; }
}

int hash::getK() { return k; }

void hash::printTable()
{
    for (auto MAP : table)
    {
        for(auto e : MAP)
        {
            std::cout << "i:" << e.first.first << " j:" << e.first.second << " val:" << e.second << "|";
        }
    }
    std::cout << std::endl;
}

//private

int hash::h_func(int i, int j)
{
    unsigned long long Bn   = getNumBits(n + 1);
    unsigned long long Bcap = getNumBits(cap + 1);
    
    unsigned long long Ri   = getNumBits(i);
    unsigned long long Rj = getNumBits(j);
    
    unsigned long long Rij = 1;
    Rij <<= Bn;
    Rij += Ri;
    Rij <<= Bcap;
    Rij += Rj;
    
    return Rij % k;
}

//int hash::h_funcOLD(int i, int j)
//{//ORIGINAL
//    auto Bn   = getNumBits(n + 1);
//    auto Bcap = getNumBits(cap + 1);
//
//    std::deque<bool> Ri = getBitRep(i);
//    std::deque<bool> Rj = getBitRep(j);
//
//    while(Ri.size() < Bn) { Ri.push_front(0); }
//    while(Rj.size() < Bcap) { Rj.push_front(0); }
//
//    auto Rij = Ri;
//    Rij.insert(Rij.end(), Rj.begin(), Rj.end());
//    Rij.push_front(1);
//
//    int iRij = 0;
//
//    for(auto bit : Rij)
//    {
//        iRij <<= 1;
//        iRij |= bit;
//    }
//
//    return iRij % k;
//}

int getNumBits(int num)
{
    return ceil(log2(num+1));
}

//std::deque<bool> getBitRep(int num)
//{
//    std::deque<bool> bits;
//    while(num)
//    {
//        bits.push_front(num & 1);
//        num >>= 1;
//    }
//    return bits;
//}

template<typename T>
void printDeque(std::deque<T> InDeque, std::string leadString)
{
    std::cout << leadString;
    for(auto e : InDeque)
    {
        std::cout << e;
    }
    std::cout << std::endl;
}
