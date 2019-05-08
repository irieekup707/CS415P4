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
//    std::cout << "insert=i:" << i << " j:" << j << " val:" << val << " ind:" << index << std::endl;
}

int hash::contains(int i, int j)
{
    auto index = h_func(i, j);
    auto found = table[index].find(std::make_pair(i, j));
//    std::cout << "contains=i:" << i << " j:" << j << " ind:" << index << std::endl;
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
    auto Bn   = getNumBits(n + 1);
    auto Bcap = getNumBits(cap + 1);
    
    std::deque<bool> Ri = getBitRep(i);
    std::deque<bool> Rj = getBitRep(j);
    
    while(Ri.size() < Bn) { Ri.push_front(0); }
    while(Rj.size() < Bcap) { Rj.push_front(0); }
    
    auto Rij = Ri;
    Rij.insert(Rij.end(), Rj.begin(), Rj.end());
    Rij.push_front(1);
    
    int iRij = 0;
    
    for(auto bit : Rij)
    {
        iRij <<= 1;
        iRij |= bit;
    }
    
    return iRij % k;
}

int getNumBits(int num)
{
    return ceil(log2(num+1));
}

std::deque<bool> getBitRep(int num)
{
    std::deque<bool> bits;
    while(num)
    {
        bits.push_front(num & 1);
        num >>= 1;
        std::cout << "";
        
    }
    return bits;
}

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
