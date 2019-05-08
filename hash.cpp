//
//  hash.cpp
//  CS415P4
//
//  Created by Will Lucic on 5/7/19.
//  Copyright © 2019 supersaiyansubtlety. All rights reserved.
//

#include "hash.hpp"

hash::hash(int n, int cap) : n(n), cap(cap) { }

void hash::insert(int i, int j, int val)
{
    
}

bool hash::contains(int i, int j)
{
    
    return true;
}

int hash::h_func(int i, int j)
{
    int iBn = ceil(log2(n+1));
    std::vector<bool> Bn;
    while(iBn)
    {
        Bn.push_back(iBn & 1);
        iBn >>= 1;
        std::cout << "";
    }
    std::reverse(Bn.begin(), Bn.end());
    
    for (auto bit : Bn)
    {
        std::cout << bit;
    }
    std::cout << std::endl;
    int iBcap = ceil(log2(cap+1));
    
    int iRi = ceil(log2(i));
    int iRj = ceil(log2(j));
    
    
    
    
    
    return 0;
}
