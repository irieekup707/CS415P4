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
#include "heap.hpp"

void greedySortSack(std::deque<int>& weight, std::deque<int>& val,int cap, int n);
void greedyHeapSack(std::deque<int>& weight, std::deque<int>& val,int cap, int n);
int knapsack(std::deque<int>& weight, std::deque<int>& val,int cap, int n);
int knapsackMem(std::deque<int>& weight, std::deque<int>& val, const int& cap, const int& n);
int knapsackMemHelper(std::deque<int>& weight, std::deque<int>& val, const int& cap, const int& n, hash& table);

bool isInt(const std::string& str);
int getInt(std::ifstream& stream);
void endl(int n);


/* USER ENTRY */
auto& inStream = std::cin;
bool automatic = false;
void openStream() {}
bool whileCheck() { return true; }

/* AUTOMATIC ENTRY */
//std::ifstream inStream;
//void openStream() { inStream.open("input.txt"); }
//bool automatic = true;
//bool whileCheck() { return inStream.peek() != EOF; }

int main(int argc, const char * argv[])
{
    openStream();
    while (whileCheck())
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
            getline(inStream, input);
            
            if(automatic)
            {
                std::cout << input;
                endl(1);
            }
            
            file->open(input);
            if(!file->is_open())
            {
                if(automatic) { return 0; }
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
                        if(n != vals.size())
                        {
                            weights.clear();
                            vals.clear();
                            i--;
                        }
                        else { i++; }
                        break;
                    default:
                        assert(false);
                        break;
                        
                }
            }
        }
        
        std::cout << std::endl << "Knapsack capacity = " << cap << ". Total number of items = " << n << std::endl << std::endl;
        
        knapsack(weights, vals, cap, n);
        knapsackMem(weights, vals, cap, n);
        greedySortSack(weights, vals, cap, n);
        greedyHeapSack(weights, vals, cap, n);
    }
    
    return 0;
}


void greedySortSack(std::deque<int>& weight, std::deque<int>& val,int cap, int n)
{
    float startTime = clock();
    
    std::deque<node> values;
    for(int i = 0; i < n; i++)
    {
        values.push_back(node(val[i]/float(weight[i]), weight[i], val[i], i + 1));
    }
  
    sort (values.begin(), values.end(), node::ratioGreater);
    
    std::deque<node> optimalSet;
    
    int curCap = 0;
    for(int it = 0; (it < n) && (curCap + values[it].getWeight() <= cap); it++)
    {
        curCap += values[it].getWeight();
        optimalSet.push_back(values[it]);
    }
    
    int optVal = 0;
    for(auto e : optimalSet)
    {
        optVal += e.getVal();
    }
    std::cout << "Greedy Approach Optimal value: " << optVal << std::endl;
    std::cout << "Greedy Approach Optimal subset: {";

    std::sort(optimalSet.begin(), optimalSet.end(), node::itemLess);
    for(auto it = optimalSet.begin(); it < optimalSet.end() - 1; it++)
    {
        std::cout << it->getItem() << ", ";
    }
    std::cout << (optimalSet.end() - 1)->getItem() << "}";
    endl(1);
    std::cout << "Greedy Approach Time Taken: " << (clock() - startTime)/CLOCKS_PER_SEC;
    endl(2);
}

void greedyHeapSack(std::deque<int>& weight, std::deque<int>& val,int cap, int n)
{
    float startTime = clock();
    
    heap h(weight, val, cap, n);
    
    int curCap = 0;
    
    std::deque<node> optimalSet;
    
    node tempNode = h.popMax();
    for(int it = 0; (it < n) && (curCap + tempNode.getWeight() <= cap); it++)
    {
        curCap += tempNode.getWeight();
        optimalSet.push_back(tempNode);
        tempNode = h.popMax();
    }
    
    int optVal = 0;
    for(auto e : optimalSet)
    {
        optVal += e.getVal();
    }
    
    std::cout << "Heap-based Greedy Approach Optimal value: " << optVal << std::endl;
    std::cout << "Heap-based Greedy Approach Optimal subset: {";

    std::sort(optimalSet.begin(), optimalSet.end(), node::itemLess);
    for(auto it = optimalSet.begin(); it < optimalSet.end() - 1; it++)
    {
        std::cout << it->getItem() << ", ";
    }
    std::cout << (optimalSet.end() - 1)->getItem() << "}";
    endl(1);
    std::cout << "Heap-based Greedy Approach Time Taken: " << (clock() - startTime)/CLOCKS_PER_SEC;
    endl(2);
    
}

int knapsack(std::deque<int>& weight, std::deque<int>& val,int cap, int n)
{
    weight.push_front(0);
    val.push_front(0);
    
    float startTime = clock();
    int i, j;

    std::vector<std::vector <int> > k;
    k.resize(n + 1);
    for(int i = 0; i < n + 1; i++)
    {
        std::vector<int> temp;
        temp.resize(cap + 1);
        k[i] = temp;
    }
    
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
                k[i][j] = std::max(first,second);
            }
            else
                k[i][j] = k[i-1][j];
            
        }
    }
    
    j = cap;
    i = n;
    int current = k[i][j];

    std::deque<int> optimalSet;

    while((j > 0) && (i > 1))
    {
        while((i > 1) && (current == k[i-1][j]))
        {
            i--;
        }
        assert(i > 0);
        optimalSet.push_front(i);
        j -= weight[i];
        i--;
        assert(i > -1);
        current = k[i][j];
    }
    
    std::cout << "Traditional Dynamic Programming Optimal value: " << k[n][cap] << std::endl;
    std::cout << "Traditional Dynamic Programming Optimal subset: {";
    for(auto it = optimalSet.begin(); it < optimalSet.end() - 1; it++)
    {
        std::cout << *it << ", ";
    }
    std::cout << *(optimalSet.end() - 1) << "}";
    endl(1);
    std::cout << "Traditional Dynamic Programming Time Taken: " << (clock() - startTime)/CLOCKS_PER_SEC;
    endl(2);
    
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
    
    int i = n;
    int j = cap;
    int current = table.contains(i, j);
    
    std::deque<std::pair<int, int> > optimalValues;
    std::deque<int> optimalSet;
    
    while((j > 0) && (i > 1))
    {
        while((i > 1) && (current == table.contains(i - 1, j)))
        {
            i--;
        }

        optimalSet.push_front(i);
        j -= weight[i];
        i--;
        current = table.contains(i, j);
        
    }
    
    std::cout << "Space-efficient Dynamic Programming Optimal value: " << optimalVal << std::endl;
    std::cout << "Space-efficient Dynamic Programming Optimal subset: {";
    for(auto it = optimalSet.begin(); it < optimalSet.end() - 1; it++)
    {
        std::cout << *it << ", ";
    }
    std::cout << *(optimalSet.end() - 1) << "}";
    endl(1);
    std::cout << "Space-efficient Dynamic Programming Time Taken: " << (clock() - startTime)/CLOCKS_PER_SEC;
    endl(2);
    
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
    
    if (!isInt(token))
    {
        std::cerr << "File provided contains non-integer value. " << std::endl;
        return -1;
    }
    return std::stoi(token);
}

void endl(int n)
{
    for(int i = 0; i < n; i++)
    {
        std::cout << std::endl;
    }
}
