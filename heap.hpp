//
//  heap.hpp
//  CS415P4
//
//  Created by Will Lucic on 5/9/19.
//  Copyright © 2019 supersaiyansubtlety. All rights reserved.
//

#ifndef heap_hpp
#define heap_hpp

#include <stdio.h>
#include <iostream>
#include <limits>

#include <deque>
#include <queue>

class node
{
    node(float ratio, int weight, int val, int item);
private:
    friend class heap;
    
    float ratio;
    int weight;
    int val;
    int item;
    
    void print();
    
};

class heap
{
public:
    heap();
    heap(int n, int weight[], int val[], int capacity);
    
    void heapify(std::deque<node> in_data);
    bool insert();
    
    int size();
    bool isEmpty();
    
    node getMax();
    node popMax();
    
    void print();
    
private:
    std::deque<node> data;
    
//    void swap(int i, int j);
    void promote(const int& parent, const int& candidate);
    
    void setLR(const int& parent, int& L, int& R) const;
};



#endif /* heap_hpp */
