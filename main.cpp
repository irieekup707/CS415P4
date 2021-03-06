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
#include "time.h"
#include "hash.hpp"
#include "heap.hpp"
void greedySortSack(int weight[], int val[], int cap, int n);
int knapsack(int weight[], int val[],int cap, int n);
int knapsackMem(const int weight[], const int val[], const int& cap, const int& n);
int knapsackMemHelper(const int weight[], const int val[], const int& cap, const int& n, hash& table);
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
        std::vector<int> weights, vals;
        
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
            if(!(*file))
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
                        while(weightFile)
                        {
                            weights.push_back(getInt(weightFile));
                            if(weights.back() < 0)
                            {
                                weights.clear();
                                break;
                            }
                        }
                        i++;
                        n = int(weights.size());
                        break;
                    case 2:
                        while(weightFile)
                        {
                            vals.push_back(getInt(valFile));
                            if(vals.back() < 0)
                            {
                                vals.clear();
                                break;
                            }
                        }
                        if(n != vals.size())
                        {
                            i--;
                        }
                    default:
                        assert(false);
                        break;
                }
                
            }
        }
    }
    
    return 0;
}


int mainOLD(int argc, const char * argv[])
{
    int n = 8;
    
    int weight[] = {0,2,1,3,2,2,3,4};
    
    int val[] = {0, 12, 10, 20, 15, 20, 25, 30};
    
    int capacity = 10;
    
    heap test(n, weight, val, capacity);
    test.print();
    
//    greedySortSack(weight, val, capacity, n);
    //int res = knapsack(weight, val, capacity, n);
    
    //std::cout << "result is : " << res << std::endl << std::endl;
    
    //int memRes = knapsackMem(weight, val, capacity, n);
    
    //std::cout << "mem result is : " << memRes << std::endl << std::endl;
    
    return 0;
}

void greedySortSack(int weight[], int val[], int cap, int n)
{
    std::deque<std::pair<std::pair<float, int>, std::pair<int, int>> > values;
    std::pair<float,int> weightValRatio;
    std::pair<int,int> weightAndVal;
    std::pair<std::pair<float,int>,std::pair<int,int>> weightValPair;
    std::deque<int> optimalSet;
    for(int i =1; i < n; i++)
    {
        weightValRatio = std::make_pair(( val[i]/float(weight[i])),i);
        weightAndVal = std::make_pair(weight[i], val[i]);
        weightValPair = std::make_pair(weightValRatio,weightAndVal);
        values.push_back(weightValPair);
    }
  

    sort (values.begin(), values.end(), std::greater<>());
    for(auto i =0; i < values.size(); i++)
    {
        std::cout << "val/weight is : " <<  values[i].first.first << "  item is : " << values[i].first.second << " Weight is " << values[i].second.first<< std::endl;
    }
    
    int curCap = 0;
//    if(values[1].second.first <= cap)
//    {
//        curCap = values[0].second.first;
//        optimalSet.push_front(values[0].first.second);
//    }
//    std::cout << " curCap is : " << curCap << std::endl;
    int k = 0;
    while((curCap < cap) && (k <= n))
    {
        if((curCap + values[k].second.first) <= cap)
           {
               curCap = curCap + values[k].second.first;
               optimalSet.push_front(values[k].first.second);
               std::cout << " curCap is : " << curCap << " Item is" <<  std::endl;
           }
        k++;
    }
}

int knapsack(int weight[], int val[],int cap, int n)
{
    float startTime = clock();
    int i, j;
    int k[n+1][cap+1];
    
    for (int a = 0; a <= n; a++)
    {
        for(int b = 0; b <= cap; b++)
        {
            k[a][b] = -1;
        }
    }
    
    for(j = 0; j <= cap; j++)
    {
        for(i=0; i<= n; i++)
        {
            if(i == 0 || j == 0)
            {
                k[i][j]= 0;
            }
            else if((j - weight[i]) >= 0)
            {
                auto first = k[i-1][j];
                int second = val[i] + k[i-1][j-weight[i]];
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

    std::deque<std::pair<int, int> > optimalValues;
    std::deque<int> optimalSet;

    while(j > 0)
    {
        while(current == k[i-1][j])
        {
            i--;
        }
        optimalSet.push_front(i);
        j -= weight[i];
        i--;
        current = k[i][j];
        
    }
    
    std::cout << "optimal set: ";
    for (auto item : optimalSet)
    {
        std::cout << item << ",";
    }
    std::cout << std::endl << "Time: " << (clock() - startTime)/CLOCKS_PER_SEC << std::endl;
    
    return k[n][cap];
}

int knapsackMem(const int weight[], const int val[], const int& cap, const int& n)
{
    float startTime = clock();
    
    int k = 23;
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
    
    std::cout << "optimal set: ";
    for (auto item : optimalSet)
    {
        std::cout << item << ",";
    }
    std::cout << std::endl << "Time: " << (clock() - startTime)/CLOCKS_PER_SEC << std::endl;
    return optimalVal;
}

int knapsackMemHelper(const int weight[], const int val[], const int& cap, const int& n, hash& table)
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
            auto first = table.contains(i - 1, j);
            if (first == -1) { first = knapsackMemHelper(weight, val, j, i - 1, table); }
            
            auto second = table.contains(i - 1,  j - weight[i]);
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
    return stoi(token);
}
