//
//  hash.hpp
//  CS415P4
//
//  Created by Will Lucic on 5/7/19.
//  Copyright © 2019 supersaiyansubtlety. All rights reserved.
//

#ifndef hash_hpp
#define hash_hpp

#include <iostream>
//#include <list>
#include <map>
//#include <tuple>
#include <vector>
#include <deque>
#include <math.h>
#include <algorithm>
#include <assert.h>



class hash
{
public:
    hash(int k, int n, int cap);
    
    void insert(int i, int j, int val);
    
    int contains(int i, int j);
    
    int getK();
    
    void printTable();
    
private:
    std::vector< std::map<std::pair<int,int>, int> > table;
    
    int k;
    int n;
    int cap;
    
    int h_func(int i, int j);
};

int getNumBits(int num);

template<typename T>
void printDeque(std::deque<T> InDeque, std::string leadString);

#endif /* hash_hpp */
