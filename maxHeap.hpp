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
#include <cfloat>

#include <deque>
#include <queue>

class node
{
public:
    node(float ratio, int weight, int val, int item);
    
    float getRatio() const;
    int getWeight() const;
    int getVal() const;
    int getItem() const;
    
private:
    friend class maxHeap;
    
    float ratio;
    int weight;
    int val;
    int item;
        
    void print(std::string delim, int endl = 1);
    void print(std::string delim, std::string end);
    
};

class maxHeap
{
public:
    maxHeap();
    maxHeap(std::deque<int>& weight, std::deque<int>& val,int cap, int n);
    
    void heapify();
//    void heapify(std::deque<node>& in_data);
    bool insert();
    
    int size();
    bool isEmpty();
    
    node getMax();
    node popMax();
    
    void print();
    
private:
    std::deque<node> data;
    
//    void swap(int i, int j);
    void propogate(int parent);
    
    void setLR(const int& parent, int& L, int& R) const;
    
    bool midLeafHandle(const int& parent, const int& L, const int& R);
};



#endif /* heap_hpp */
