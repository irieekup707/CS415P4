//
//  heap.cpp
//  CS415P4
//
//  Created by Will Lucic on 5/9/19.
//  Copyright © 2019 supersaiyansubtlety. All rights reserved.
//

#include "heap.hpp"

heap::heap() : Size(0)
{
    
}

heap::heap(int n, int weight[], int val[], int capacity)
{
    std::deque<node> not_heap;
    
    for (int i = 0; i < n; i++)
    {
        not_heap.push_back(node(val[i]/float(weight[i]), weight[i], val[i], i));
    }
    
    for (auto e : not_heap)
    {
        std::cout << e.ratio << "," << e.weight << "," << e.val << "," << e.item << std::endl;
    }
    std::cout << std::endl;
}

void heap::heapify(std::deque<node> in_data)
{
    int left, right;
    for(int i = in_data.size()/2; i >= 0 ; i--)
    {
        left = 2 * i;
        right = left + 1;
        node& greater = (in_data[left].ratio > in_data[right].ratio)? in_data[left] : in_data[right];
        if(greater.ratio > in_data[i].ratio)
        {
            greater.swap(in_data[i]);
        }
    }
}

bool heap::insert()
{
    
    return false;
}


int heap::size()
{
    return Size;
}

bool heap::isEmpty()
{
    return Size == 0;
}

node heap::getMax()
{
    return data.front();
}

node heap::popMax()
{
    auto max = getMax();
//    &data.begin() = &(data.end() - 1);
    std::cout << data.front().ratio << "," << data.back().ratio;
    
    data.front().swap(data.back());

    
    data.pop_back();
    
    node* propogater = &data.front();
    while (((propogater->left > 0) && (data[propogater->left].ratio > propogater->ratio)) || ((propogater->right > 0) && (data[propogater->right].ratio > data.front().ratio)))
    {
        node& greater = (data[propogater->left].ratio > data[propogater->right].ratio) ? data[propogater->left] : data[propogater->right];
        
        greater.swap(*propogater);
        
        propogater = &greater;
    }
    
    return max;
}

void heap::printeHeap()
{
    
}

node::node(float ratio, int weight, int val, int item) :
ratio(ratio),
weight(weight),
val(val),
item(item),
parent(-1),
left(-1),
right(-1)
{
    
}

void node::swap(node &R)
{
    std::swap(ratio, R.ratio);
    std::swap(ratio, R.ratio);
    std::swap(ratio, R.ratio);
    std::swap(ratio, R.ratio);
}


