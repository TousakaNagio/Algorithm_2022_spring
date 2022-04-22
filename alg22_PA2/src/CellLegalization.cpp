#include "CellLegalization.h"
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>

// Constructor
CellLegalization::CellLegalization() {}

void CellLegalization::test(vector< vector<long long> > &data)
{
    // for (int i=0;i<data.size();i++){
    //     for (int j=0;j<data[i].size();j++){
    //         cout << data[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    long long W, num;
    vector <long long> & widths = data[2];
    vector <long long> & pos = data[3];;
    vector <long long> & weights = data[4];;

    
    W = data[0][0];
    num = data[1][0];

    // cout << row_width << endl;
    // cout << number << endl;
    // for (int i=0;i<cell_width.size()-1;i++){
    //     cout << cell_width[i] << " ";
    // }
    // cout << endl;
    // for (int i=0;i<cell_pos.size()-1;i++){
    //     cout << cell_pos[i] << " ";
    // }
    // cout << endl;
    // for (int i=0;i<cell_weight.size()-1;i++){
    //     cout << cell_weight[i] << " ";
    // }
    // cout << endl;

    // Start from here
    vector <long long> S1;
    vector <long long> S2;

    for (int i = 0;i < W;i++){
        S1.push_back(0);
        S2.push_back(0);
    }

    int sum = 0;
    for (int i = 0;i < num;i++){
        sum += widths[i];
        for (int j = 0;j < W;j++){
            if (i == 0){
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
            else{
                if (i%2 == 1){
                    if (j < sum - 1){
                        S2[j] = 0;
                    }
                    else if (j == sum - 1){
                        S2[j] = S1[j - widths[i]] + weights[i] * abs(j - widths[i] + 1 - pos[i]);
                    }
                    else{
                        long long p = j - widths[i] + 1;
                        long long temp = weights[i] * abs(p - pos[i]);
                        S2[j] = min(S2[j-1], S1[j - widths[i]] + temp);
                    }
                }
                else{
                    if (j < sum - 1){
                        S1[j] = 0;
                    }
                    else if (j == sum - 1){
                        S1[j] = S2[j - widths[i]] + weights[i] * abs(j - widths[i] + 1 - pos[i]);
                    }
                    else{
                        long long p = j - widths[i] + 1;
                        long long temp = weights[i] * abs(p - pos[i]);
                        S1[j] = min(S1[j-1], S2[j - widths[i]] + temp);
                    }
                }
            }
        }
    }
    if (num%2 == 0){
        cout << S2[W-1] << endl;
    }
    else{
        cout << S1[W-1] << endl;
    }

    // Find path
    vector <long long> path;
    int idx = W-1;
    
    for (int i = num-1;i >= 0;i--){
        if (i % 2 == 1){
            for (int j = idx;j >= 0;j--){
                if (S2[j] == S2[j-1]){
                    continue;
                }
                else{
                    path.push_back(j - widths[i] + 1);
                    idx = j - widths[i];
                    break;
                }
            }
            int k = idx;
            while (S1[k] != 0){
                long long h = k - widths[i-1];
                long long p = h + 1;
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
                    path.push_back(j - widths[i] + 1);
                    idx = j - widths[i];
                    break;
                }
            }
            int k = idx;
            while (S2[k] != 0){
                long long h = k - widths[i-1];
                long long p = h + 1;
                S1[h] = S2[k] - weights[i-1] * abs(p - pos[i-1]);
                h--;
                k--;
            }
        }
    }
    for (int i = 0;i <= path.size()-1;i++){
        cout << path[i] << " ";
    }
    cout << endl << "Debug2" << endl;

    // path.push_back(E[num-1][W-1]);
    // for (int k = num-2;k>=0;k--){
    //     path.push_back(E[k][path.back() - 1]);
    // }
    // for (int k = 0;k < path.size();k++){
    //     cout << path[k] << " ";
    // }
    // cout << endl;

    // for (int i = 0;i < W;i++){
    //     cout << S1[i] << " ";
    // }
    // cout << endl;
    // for (int i = 0;i < W;i++){
    //     cout << S2[i] << " ";
    // }
    // cout << endl;
}