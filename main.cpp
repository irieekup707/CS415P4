//
//  main.cpp
//  CS415P4
//
//  Created by Ryan  Martino on 5/1/19.
//  Copyright © 2019 Ryan  Martino. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "time.h"
#include "hash.hpp"

int knapsack(int weight[], int val[],int cap, int n);
int knapsackMem(const int weight[], const int val[], const int& cap, const int& n);
int knapsackMemHelper(const int weight[], const int val[], const int& cap, const int& n, hash& table);

int main(int argc, const char * argv[]) {
    
//    int k = 23;
//    int N = 10;
//    int cap = 16;
//
//    int i = 3;
//    int j = 9;
    
//    hash test(k, N, cap);
//    std::cout << "index: " << test.h_func(i, j) << std::endl;
    
    int n = 5;
    
    int weight[] = {0,2,1,3,2};
    
    int val[] = {0, 12, 10, 20, 15};
    
    int capacity = 5;
    
//    int res = knapsack(weight, val, capacity, n);
    
    int memRes = knapsackMem(weight, val, capacity, n);
    
//    std::cout << "result is : " << res << std::endl;
    
    std::cout << "mem result is : " << memRes << std::endl;
    
    return 0;
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
//                std::cout << "W[i] = " << weight[i] << std::endl;
                auto first = k[i-1][j];
                int second = val[i] + k[i-1][j-weight[i]];
                k[i][j] = std::max(first,second);
            }
            else
                k[i][j] = k[i-1][j];
            
        }
//        std::cout << "===========================\n";
    }
    
    for (int a = 0; a <= n; a++)
    {
        for(int b = 0; b <= cap; b++)
        {
            std::cout << k[a][b] << ",";
        }
        std::cout << "\n";
    }
    std::cout << "---------------------\n";
    
    j = cap;
    i = n;
    
    int current = k[i][j];
//    std::cout << current;
    std::vector<std::pair<int, int> > optimalValues;
    std::vector<int> optimalSet;

    while(j > 0)
    {
        while(current == k[i-1][j])
        {
            i--;
        }
        optimalValues.push_back(std::make_pair(weight[i], val[i]));
        optimalSet.push_back(i);
        j -= weight[i];
        i--;
        current = k[i][j];
        
    }
    
//    optimalSet.push_back(std::make_pair(weight[i], val[i]));
    
    std::reverse(optimalValues.begin(), optimalValues.end());
    std::reverse(optimalSet.begin(), optimalSet.end());
    
//    for (auto item : optimalValues)
//    {
//        std::cout << item.first << "," << item.second << ";";
//    }
    for (auto item : optimalSet)
    {
        std::cout << item << ",";
    }
    std::cout << std::endl;
    std::cout << "Time: " << (clock() - startTime)/CLOCKS_PER_SEC << std::endl;
    
    return k[n][cap ];
}

int knapsackMem(const int weight[], const int val[], const int& cap, const int& n)
{
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
    
    return knapsackMemHelper(weight, val, cap, n, table);
}

int knapsackMemHelper(const int weight[], const int val[], const int& cap, const int& n, hash& table)
{
    int i, j;
    int value;
    for(j = 1; j <= cap; j++)
    {
        for(i=1; i<= n; i++)
        {
            if(table.contains(i, j) < 0)
            {
                if(j < weight[i])
                {
                    value = table.contains(i - 1, j);
                    assert(value >= 0);
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
                table.printTable();
            }
        }
    }
//    std::cout << "i: " << i << ", j: " << j << std::endl;
    
    return table.contains(n, cap);
}
