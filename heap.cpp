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
    //dummy-sentinel root node so index math works
    std::deque<node> not_heap = { node(FLT_MAX, 0, 0, 0) };
    
    for (int i = 0; i < n; i++)
    {
        float ratio = (weight[i])? val[i]/float(weight[i]) : 0;
        not_heap.push_back(node(ratio, weight[i], val[i], i));
    }
//    for (auto e : not_heap)
//    {
//        e.print(",");
//    }
    data = not_heap;
    
    heapify();
}

//void heap::heapify()
//{
//    heapify(data);
//}

void heap::heapify()
{
    //dummy-sentinel root node so index math works
    data.push_back(node(INT_MAX, 0, 0, 0));
    
//    int i = int(data.size())/2;
    
//    int L, R, greater;
//    //this does the first iteration outside the loop, with checks for r == -1,
//    //because in the loop we don't need to check
//    setLR(i, L, R);
//    if(R == -1) { greater = L; }
//    else
//    {
//        greater = (data[L].ratio > data[R].ratio)? L : R;
//    }
//    //single promotion rather than full propogation because we're at bottom level
//    if(data[greater].ratio > data[i].ratio)
//    {
//        std::swap(data[greater], data[i]);
//    }
//
    //i-- before loop so we don't re-do the first iteration
    for(int i = int(data.size())/2; i >= 1 ; i--)
    {
        //NOT using setLR because we don't need the check, R always < data.size()
        propogate(i);
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
    
    propogate(1);
    
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
                
                data[parent].print(",","|");
                
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

void heap::propogate(int parent)
{
    int L, R;
    setLR(parent, L, R);
    if(midLeafHandle(parent, L, R)) { return; };
    
    while ( (data[L].ratio > data[parent].ratio) || (data[R].ratio > data[parent].ratio) )
    {
        int greater = (data[L].ratio > data[R].ratio)? L : R;
        
        std::swap(data[parent], data[greater]);
        
        parent = greater;
        setLR(parent, L, R);
        if(midLeafHandle(parent, L, R)) { return; };
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

bool heap::midLeafHandle(const int& parent, const int& L, const int& R)
{
    if (L < 0) { return true; }
    if (R < 0)
    {
        if(data[L].ratio > data[parent].ratio) { std::swap(data[parent], data[L]); }
        return true;
    }
    return false;
}

//node

node::node(float ratio, int weight, int val, int item) :
ratio(ratio),
weight(weight),
val(val),
item(item)
{
    
}

void node::print(std::string delim, int endl)
{
    std::cout << ratio << delim << weight << delim << val << delim << item;
    for(int i = 0; i < endl; i++)
    {
        std::cout << std::endl;
    }
}

void node::print(std::string delim, std::string end)
{
    std::cout << ratio << delim << weight << delim << val << delim << item << end;
}


