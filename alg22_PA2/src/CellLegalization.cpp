#include "CellLegalization.h"
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>

// Constructor
CellLegalization::CellLegalization() {}

void CellLegalization::test(long long W, long long num, long long *data0, long long *data1, long long *data2,long long &cost, long long *path)
{
    // for (int i=0;i<3;i++){
    //     for (int j=0;j<num;j++){
    //         cout << data[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    long long *widths = data0;
    long long *pos = data1;
    long long *weights = data2;

    // cout << W << endl;
    // cout << num << endl;
    // for(int i=0;i<num;i++){
    //     cout << widths[i] << " ";
    // }
    // cout << endl;
    // for(int i=0;i<num;i++){
    //     cout << pos[i] << " ";
    // }
    // cout << endl;
    // for(int i=0;i<num;i++){
    //     cout << weights[i] << " ";
    // }
    // cout << endl;


    // Start from here
    long long S1[W];
    long long S2[W];

    // DP Version1
    int i = 0 ,sum = 0;
    for (int j = 0;j < W; j++){
        if (j < widths[i] - 1){
            S1[j] = 0;
        }
        else if (j == widths[i] - 1){
            S1[j] = weights[i] * abs(j - widths[i] + 1 - pos[i]);
        }
        else{
            long long p = j - widths[i] + 1;
            long long temp = weights[i] * abs(p - pos[i]);
            S1[j] = min(S1[j-1], temp);
        }
    }
    sum += widths[i];

    for (i = 1;i < num;i++){
        sum += widths[i];
        if (i%2 == 1){
            int j = sum - 1;
            S2[j] = S1[j - widths[i]] + weights[i] * abs(j - widths[i] + 1 - pos[i]);
            for (j = sum;j < W; j++){
                long long p = j - widths[i] + 1;
                long long temp = weights[i] * abs(p - pos[i]);
                S2[j] = min(S2[j-1], S1[j - widths[i]] + temp);
            }
        }
        else{
            int j = sum - 1;
            S1[j] = S2[j - widths[i]] + weights[i] * abs(j - widths[i] + 1 - pos[i]);
            for (j = sum;j < W; j++){
                long long p = j - widths[i] + 1;
                long long temp = weights[i] * abs(p - pos[i]);
                S1[j] = min(S1[j-1], S2[j - widths[i]] + temp);
            }
        }
    }
    if (num%2 == 0){
        cost = S2[W-1];
        // cout << S2[W-1] << endl;
    }
    else{
        cost = S1[W-1];
        // cout << S1[W-1] << endl;
    }
    
    

    // Find path
    // long long path[num];
    long long idx = W-1;
    long long total_width = 0;

    for (int i=0;i<num;i++){
        // cout << i << ": " << widths[i] << endl;
        total_width += widths[i];
    }
    // cout << "debug" << endl;
    // cout << total_width << endl;

    // for (int i = 0;i < num;i++){
    //     cout << path[i] << " ";
    // }
    // cout << endl << "Debug2" << endl;

    // Version 2
    for (int i = num-1;i >= 0;i--){
        total_width -= widths[i];
        if (i % 2 == 1){
            for (int j = idx;j >= 0;j--){
                if (S2[j] == S2[j-1]){
                    continue;
                }
                else{
                    long long temp = j - widths[i] + 1;
                    path[i] = j - widths[i] + 1;
                    idx = j - widths[i];
                    break;
                }
            }
            if (i <= 1){
                continue;
            }
            int k = idx;
            while (k >= total_width - 1){
                int h = k - widths[i-1];
                int p = h + 1;
                S2[h] = S1[k] - weights[i-1] * abs(p - pos[i-1]);
                h--;
                k--;
            }
        }
        else{
            for (int j = idx;j >= 0;j--){

                if (S1[j] == S1[j-1]){
                    continue;
                }
                else{
                    long long temp;
                    temp = j - widths[i] + 1;
                    path[i] = j - widths[i] + 1;
                    idx = j - widths[i];
                    break;
                }
            }
            if (i <= 1){
                continue;
            }
            int k = idx;
            while (k >= total_width - 1){
                int h = k - widths[i-1];
                int p = h + 1;
                S1[h] = S2[k] - weights[i-1] * abs(p - pos[i-1]);
                h--;
                k--;
            }
        }
        // cout << i << ": " << total_width << endl;
    }

    // // Check path
    // for (int l = 0;l < num;l++){
    //     // count += weights[l] * abs(path[l] - pos[l]);
    //     cout << path[l] << " ";
    // }
    // cout <<  endl;
    
    // // Check answer
    // long long count = 0;
    // for (int l = 0;l < num;l++){
    //     count += weights[l] * abs(path[l] - pos[l]);
    // }
    // cout << count << endl;
}