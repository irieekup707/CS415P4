//
//  main.cpp
//  CS415P4
//
//  Created by Ryan  Martino on 5/1/19.
//  Copyright © 2019 Ryan  Martino. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <string>
#include "time.h"
#include "hash.hpp"
#include "maxHeap.hpp"
void greedySortSack(std::deque<int>& weight, std::deque<int>& val,int cap, int n);
void greedyHeapSack(std::deque<int>& weight, std::deque<int>& val,int cap, int n);
int knapsack(std::deque<int>& weight, std::deque<int>& val,int cap, int n);
int knapsackMem(std::deque<int>& weight, std::deque<int>& val, const int& cap, const int& n);
int knapsackMemHelper(std::deque<int>& weight, std::deque<int>& val, const int& cap, const int& n, hash& table);
bool isInt(const std::string& str);
int getInt(std::ifstream& stream);

int main(int argc, const char * argv[])
{
    while (true)
    {
        //Get three files. Keep asking until valid path is specified for each.
        std::string input = "";
        std::ifstream capFile, weightFile, valFile;
        std::ifstream* file;
        
        int cap, n = 0;
        std::deque<int> weights, vals;
        
        std::string specifier;
        int i = 0;
        while(i < 3)
        {
            switch (i) {
                case 0:
                    specifier = "capacity";
                    file = &capFile;
                    break;
                case 1:
                    specifier = "weights";
                    file = &weightFile;
                    break;
                case 2:
                    specifier = "values";
                    file = &valFile;
                    break;
                default:
                    assert(false);
                    break;
            }
            std::cout << "Enter file containing the " << specifier << ": ";
            getline(std::cin, input);
            file->open(input);
            if(!file->is_open())
            {
                std::cout << "Invalid file path specified. ";
            }
            else
            {
                switch (i)
                {
                    case 0:
                        cap = getInt(capFile);
                        if(cap >= 0) { i++; }
                        break;
                    case 1:
                        while(isspace(weightFile.peek())) { weightFile.ignore(1); }
                        while(weightFile.peek() != EOF)
                        {
                            
                            weights.push_back(getInt(weightFile));
                            if(weights.back() < 0)
                            {
                                weights.clear();
                                break;
                            }
                            while(isspace(weightFile.peek())) { weightFile.ignore(1); }
                        }
                        
                        i++;
                        n = int(weights.size());
                        break;
                    case 2:
                        while(isspace(valFile.peek())) { valFile.ignore(1); }
                        while(valFile.peek() != EOF)
                        {
                            vals.push_back(getInt(valFile));
                            if(vals.back() < 0)
                            {
                                vals.clear();
                                break;
                            }
                            while(isspace(valFile.peek())) { valFile.ignore(1); }
                        }
                        if(n != vals.size()) { i--; }
                        else { i++; }
                        break;
                    default:
                        assert(false);
                        break;
                        
                }
            }
        }
        
        std::cout << std::endl << "Knapsack capacity = " << cap << ". Total number of items = " << n << std::endl << std::endl;
        
//        knapsack(weights, vals, cap, n);
        knapsackMem(weights, vals, cap, n);
        greedySortSack(weights, vals, cap, n);
        greedyHeapSack(weights, vals, cap, n);


    }
    
    return 0;
}


void greedySortSack(std::deque<int>& weight, std::deque<int>& val,int cap, int n)
{
    float startTime = clock();
    
    std::deque<std::pair<std::pair<float, int>, std::pair<int, int>> > values;
    std::deque<std::pair<std::pair<float, int>, std::pair<int, int>> > unsorted;
    std::pair<float,int> weightValRatio;
    std::pair<int,int> weightAndVal;
    std::pair<std::pair<float,int>,std::pair<int,int>> weightValPair;
    std::deque<int> optimalSet;
    for(int i = 0; i < n; i++)
    {
        weightValRatio = std::make_pair(( val[i]/float(weight[i])), i + 1);
        weightAndVal = std::make_pair(weight[i], val[i]);
        weightValPair = std::make_pair(weightValRatio,weightAndVal);
        values.push_back(weightValPair);
    }
  
    unsorted = values;

    sort (values.begin(), values.end(), std::greater<>());
//    for(auto i =0; i < values.size(); i++)
//    {
//        std::cout << "val/weight is : " <<  values[i].first.first << "  item is : " << values[i].first.second << " Weight is " << values[i].second.first<< std::endl;
//    }
//
    int curCap = 0;
//    if(values[1].second.first <= cap)
//    {
//        curCap = values[0].second.first;
//        optimalSet.push_front(values[0].first.second);
//    }
//    std::cout << " curCap is : " << curCap << std::endl;
    int it = 0;
    while((curCap + values[it].second.first <= cap) && (it < n))
    {
//        if((curCap + values[it].second.first) <= cap)
//        {
            curCap += values[it].second.first;
            optimalSet.push_back(values[it].first.second);
//            std::cout << " curCap is : " << curCap << " Item is: " << values[it].first.second << " Val is: " << values[it].second.second << std::endl;
//        }
        it++;
    }
    int optVal = 0;
    for (auto e : optimalSet)
    {
        optVal += unsorted[e - 1].second.second;
    }
    std::cout << "Greedy Approach Optimal value: " << optVal << std::endl;
    std::cout << "Greedy Approach Optimal subset: ";

    std::sort(optimalSet.begin(), optimalSet.end());
    for (auto item : optimalSet)
    {
        std::cout << item << ", ";
    }
    
    std::cout << std::endl << "Greedy Approach Time Taken: " << (clock() - startTime)/CLOCKS_PER_SEC << std::endl << std::endl;
}

void greedyHeapSack(std::deque<int>& weight, std::deque<int>& val,int cap, int n)
{//ratio, weight, val, item
    float startTime = clock();
    
    maxHeap h(weight, val, cap, n);
    
    int it = 0, curCap = 0;
    
    std::deque<node> optimalSet;
    
    node tempNode = h.popMax();
    while((curCap + tempNode.getWeight() <= cap) && (it < n))
    {
        //        if((curCap + values[it].second.first) <= cap)
        //        {
        curCap += tempNode.getWeight();
        optimalSet.push_back(tempNode);
        //            std::cout << " curCap is : " << curCap << " Item is: " << values[it].first.second << " Val is: " << values[it].second.second << std::endl;
        //        }
        tempNode = h.popMax();
        it++;
    }
    
    int optVal = 0;
    for(auto e : optimalSet)
    {
        optVal += e.getVal();
    }
    
    std::cout << "Heap-based Greedy Approach Optimal value: " << optVal << std::endl;
    std::cout << "Heap-based Greedy Approach Optimal subset: ";
    std::deque<int> items;
    for (auto e : optimalSet)
    {
        items.push_back(e.getItem());
    }
    
    std::sort(items.begin(), items.end());
    
    for (auto e : items)
    {
        std::cout << e << ", ";
    }
    
    std::cout << std::endl << "Heap-based Greedy Approach Time Taken: " << (clock() - startTime)/CLOCKS_PER_SEC << std::endl << std::endl;
    
}

int knapsack(std::deque<int>& weight, std::deque<int>& val,int cap, int n)
{
    float startTime = clock();
    int i, j;
    int k[n+1][cap+1];
    weight.push_front(0);
    val.push_front(0);
    
//    for (int a = 0; a <= n; a++)
//    {
//        for(int b = 0; b <= cap; b++)
//        {
//            k[a][b] = -1;
//        }
//    }
    
    for(j = 0; j <= cap; j++)
    {
        for(i = 0; i<= n; i++)
        {
            if(i == 0 || j == 0)
            {
                k[i][j] = 0;
            }
            else if((j - weight[i]) >= 0)
            {
                auto first = k[i-1][j];
                auto second = val[i] + k[i-1][j-weight[i]];
//                std::cout << "val[i]" << val[i] << "[" << i << "]" << std::endl;
                k[i][j] = std::max(first,second);
            }
            else
                k[i][j] = k[i-1][j];
            
        }
    }
    
//    for (int a = 0; a <= n; a++)
//    {
//        for(int b = 0; b <= cap; b++)
//        {
//            std::cout << k[a][b] << ",";
//        }
//        std::cout << "\n";
//    }
//    std::cout << "---------------------" << std::endl;
    
    j = cap;
    i = n;
    
    int current = k[i][j];

//    std::deque<std::pair<int, int> > optimalValues;
    std::deque<int> optimalSet;

    while(j > 0)
    {
        while(current == k[i-1][j])
        {
            i--;
        }
//        optimalValues.push_front(std::make_pair(weight[i], val[i]));
        optimalSet.push_front(i);
        j -= weight[i];
        i--;
        current = k[i][j];
        
    }
    
//    std::cout << "optimal vals: ";
//    for (auto item : optimalValues)
//    {
//        std::cout << item.first << "," << item.second << ";";
//    }
    
    std::cout << "Traditional Dynamic Programming Optimal value: " << k[n][cap] << std::endl;
    std::cout << "Traditional Dynamic Programming Optimal subset: ";
    for (auto item : optimalSet)
    {
        std::cout << item << ", ";
    }
    
    std::cout << std::endl << "Traditional Dynamic Programming Time Taken: " << (clock() - startTime)/CLOCKS_PER_SEC << std::endl << std::endl;
    
    weight.pop_front();
    val.pop_front();
    
    return k[n][cap];
}

int knapsackMem(std::deque<int>& weight, std::deque<int>& val, const int& cap, const int& n)
{
    float startTime = clock();
    
    weight.push_front(0);
    val.push_front(0);
    
    int k = 2 * cap;
    hash table(k , n, cap);
    for (int i = 0; i <= n; i++)
    {
        table.insert(i, 0, 0);
    }
    
    for (int j = 1; j <= cap; j++)
    {
        table.insert(0, j, 0);
    }
    
    auto optimalVal = knapsackMemHelper(weight, val, cap, n, table);
//    for (int i = 0; i <= n; i++)
//    {
//        for(int j = 0; j <= cap; j++)
//        {
//            std::cout << table.contains(i, j) << ",";
//        }
//        std::cout << "\n";
//    }
//    std::cout << "---------------------" << std::endl;
    
    int i = n;
    int j = cap;
    int current = table.contains(i, j);
    
    std::deque<std::pair<int, int> > optimalValues;
    std::deque<int> optimalSet;
    
    while(j > 0)
    {
        while(current == table.contains(i - 1, j))
        {
            i--;
        }

        optimalSet.push_front(i);
        j -= weight[i];
        i--;
        current = table.contains(i, j);
        
    }
    
    std::cout << "Space-efficient Dynamic Programming Optimal value: " << optimalVal << std::endl;
    std::cout << "Space-efficient Dynamic Programming Optimal subset: ";
    for (auto item : optimalSet)
    {
        std::cout << item << ", ";
    }
    
    std::cout << std::endl << "Space-efficient Dynamic Programming Time Taken: " << (clock() - startTime)/CLOCKS_PER_SEC << std::endl << std::endl;
    
    weight.pop_front();
    val.pop_front();
    
    return optimalVal;
}

int knapsackMemHelper(std::deque<int>& weight, std::deque<int>& val, const int& cap, const int& n, hash& table)
{
    int value;
    
    int i = n;
    int j = cap;
    
    if(table.contains(i, j) < 0)
    {
        if(j < weight[i])
        {
            value = table.contains(i - 1, j);
            if (value == -1) { value = knapsackMemHelper(weight, val, j, i - 1, table); }
        }
        else
        {
            int first = table.contains(i - 1, j);
            if (first == -1) { first = knapsackMemHelper(weight, val, j, i - 1, table); }
            
            int second = table.contains(i - 1,  j - weight[i]);
            if (second == -1) { second = knapsackMemHelper(weight, val, j - weight[i], i - 1, table); }
            
            value = std::max(first, val[i] + second);
        }
        table.insert(i, j, value);
    }
    
    return table.contains(n, cap);
}

bool isInt(const std::string& str)
{
    for (auto c : str)
    {
        if (!isdigit(c)) { return false; }
    }
    
    return true;
}

int getInt(std::ifstream& stream)
{
    std::string token;
    stream >> token;
//    std::cout << "Token:" << token << std::endl;
    if (!isInt(token))
    {
        std::cerr << "File provided contains non-integer value. " << std::endl;
        return -1;
    }
    return std::stoi(token);
}
