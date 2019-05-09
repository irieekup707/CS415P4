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

void heap::heapify(std::deque<node> in_data)
{
    
}

bool heap::insert()
{

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


