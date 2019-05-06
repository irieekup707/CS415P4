//
//  main.cpp
//  CS415P4
//
//  Created by Ryan  Martino on 5/1/19.
//  Copyright © 2019 Ryan  Martino. All rights reserved.
//

#include <iostream>


int knapsack(int weight[], int val[],int cap, int n);
int main(int argc, const char * argv[]) {
    int n = 4;
    
    int weight[] = {2,1,3,2};
    
    int val[] = {12, 10, 20, 15};
    
    int capacity = 5;
    
    int res = knapsack(weight, val, capacity, n);
    
    std::cout << "result is : " << res << std::endl;
    
    return 0;
}
int knapsack(int weight[], int val[],int cap, int n)
{
     int i, j;
    int k[n+1][cap+1];
    
    
    for(i = 0; i <= n; i++)
    {
        k[i][0] = 0;
    }
    for(j = 0; j <= n; j++)
    {
        k[0][j] = 0;
    }
     
    for(i=0; i<= n;i++)
    {
        for(j = 0; j <= cap; j++)
        {
            if(i == 0 || j == 0)
            {
                k[i][j]= 0;
            }else if(weight[i] <= j)
        {
            k[i][j] = std::max(k[i-1][j],val[i-1] + k[i-1][j-weight[i-1]]);
        } else
            k[i][j] = k[i-1][j];
        }
    }
    return k[n][cap ];
}
