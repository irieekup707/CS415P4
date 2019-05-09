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
#include <deque>

class node;

class heap
{
public:
    heap();
    void heapify();
    bool insert();
    
    int size();
    bool isEmpty();
    
    node getMax();
    node popMax();
    
private:
    std::deque<node> data;
    
    int Size;
    
};

class node
{
    node(float ratio, int weight, int val, int item);
private:
    friend class heap;
    
    float ratio;
    int weight;
    int val;
    int item;
    
    int parent;
    int left;
    int right;

};

#endif /* heap_hpp */
