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
int main(int argc, const char * argv[]) {
    
    int three = 9;
    int zero = 0;
    
    hash test(three, zero);
    test.h_func(9, 0);
    
    int n = 4;
    
    int weight[] = {0,2,1,3,2};
    
    int val[] = {0,12, 10, 20, 15};
    
    int capacity = 5;
    
    int res = knapsack(weight, val, capacity, n);
    
    std::cout << "result is : " << res << std::endl;
    
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
        for(i=0; i<= n;i++)
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
