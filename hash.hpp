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
#include <list>
#include <tuple>
#include <vector>
#include <math.h>
#include <algorithm>



class hash
{
public:
    hash(int n, int cap);
    
    void insert(int i, int j, int val);
    
    bool contains(int i, int j);
    
//private:
    std::vector< std::list<std::tuple<int,int,int> > > table;
    
    int h_func(int i, int j);
    
    int n;
    int cap;
};

#endif /* hash_hpp */
