//
//  heap.cpp
//  CS415P4
//
//  Created by Will Lucic on 5/9/19.
//  Copyright © 2019 supersaiyansubtlety. All rights reserved.
//

#include "heap.hpp"

heap::heap()
{
    
}

heap::heap(int n, int weight[], int val[], int capacity)
{
    std::deque<node> not_heap;
    //dummy-sentinel root node so index math works
    not_heap.push_back(node(INT_MAX, 0, 0, 0));
    
    for (int i = 0; i < n; i++)
    {
        not_heap.push_back(node(val[i]/float(weight[i]), weight[i], val[i], i));
    }
    
//    for (auto e : not_heap)
//    {
//        e.print();
//        std::cout << std::endl;
//    }
//    std::cout << std::endl;
    
    heapify(not_heap);
}

void heap::heapify(std::deque<node> in_data)
{
    data = in_data;
    //dummy-sentinel root node so index math works
    data.push_back(node(INT_MAX, 0, 0, 0));
    
    int i = int(data.size())/2;
    
    int L, R, greater;
    //this does the first iteration outside the loop, with checks for r == -1,
    //because in the loop we don't need to check
    setLR(i, L, R);
    if(R == -1) { greater = L; }
    else
    {
        greater = (data[L].ratio > data[R].ratio)? L : R;
    }
    
    promote(i, greater);
    
    //i-- before loop so we don't re-do the first iteration
    for(i--; i >= 1 ; i--)
    {
        //NOT using setLR because we don't need the check, R always < data.size()
        L = 2 * i;
        R = L + 1;
        //also no check for -1 is needed
        greater = (data[L].ratio > data[R].ratio)? L : R;

        promote(i, greater);
    }
}

bool heap::insert()
{
    
    return false;
}


int heap::size()
{
    return int(data.size()) - 1;
}

bool heap::isEmpty()
{
    return data.size() <= 1;
}

node heap::getMax()
{
    return data[1];
}

node heap::popMax()
{
    auto max = getMax();
    
    std::swap(data[1], data.back());
    data.pop_back();
    
    int propogater = 1;
    int L, R;
    setLR(propogater, L, R);
    
    while (((L > 0) && (data[L].ratio > data[propogater].ratio)) || ((R > 0) && (data[R].ratio > data[propogater].ratio)))
    {
        int greater = (data[L].ratio > data[R].ratio)? L : R;
        
        std::swap(greater, propogater);
        
        propogater = greater;
        setLR(propogater, L, R);
    }
    
    return max;
}

void heap::print()
{
    if(!isEmpty())
    {
        std::queue<int> Q1, Q2;
        
        int parent, L, R;
        
        auto currQ = &Q1;
        auto nextQ = &Q2;
        
        currQ->push(1);
        while (currQ->size() > 0)
        {
            while (currQ->size() > 0)
            {
                parent = currQ->front();
                currQ->pop();
                
                data[parent].print();
                std::cout << "|";
                
                setLR(parent, L, R);
                
                if(L > 0) { nextQ->push(L); }
                if(R > 0) { nextQ->push(R); }
            }
            
            std::cout << std::endl;
            std::swap(currQ, nextQ);
        }
    }
}

//private

void heap::promote(const int& parent, const int& candidate)
{
    if(data[candidate].ratio > data[parent].ratio)
    {
        std::swap(data[parent], data[candidate]);
    }
}

void heap::setLR(const int& parent, int& L, int& R) const
{
    L = parent * 2;
    if(L >= data.size()) { L = -1; R = -1; }
    else
    {
        R = L + 1;
        if(R >= data.size()) { R = -1; }
    }
}

//node

node::node(float ratio, int weight, int val, int item) :
ratio(ratio),
weight(weight),
val(val),
item(item)
{
    
}

void node::print()
{
    std::cout << ratio << "," << weight << "," << val << "," << item;
}



