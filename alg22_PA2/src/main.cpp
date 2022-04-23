// **************************************************************************
//  File       [main.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The main program of 2019 fall Algorithm PA1]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string.h>
#include "../lib/tm_usage.h"
#include "CellLegalization.h"

using namespace std;

void help_message() {
    cout << "usage: cl <input_file> <output_file>" << endl;
}

int main(int argc, char* argv[])
{
    if(argc != 3) {
       help_message();
       return 0;
    }
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    //////////// read the input file /////////////
    
    string line;
    vector<string> lines;
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    
    while (getline(fin, line)){
        lines.push_back(line);
    }
    // for (int i = 0;i < 5;i++){
    //     cout << lines[i] << endl;
    // }

    long long W, num;

    string dir1;
    stringstream ss1(lines[0]);
    while(getline(ss1, dir1, ' ')){
        // long long temp;
        W = stoi(dir1);
    }
    string dir2;
    stringstream ss2(lines[1]);
    while(getline(ss2, dir2, ' ')){
        // long long temp;
        num = stoi(dir2);
    }
    // cout << W << " " << num << endl;


    long long data[3][num];
    for (int i = 2;i < 5;i++){
        string dir;
        stringstream ss(lines[i]);
        for (int j = 0;j < num; j++){
            getline(ss, dir, ' ');
            long long temp;
            temp = stoi(dir);
            data[i-2][j] = temp;
        }
    }

    long long path[num];
    long long cost;

    //////////// the solving part ////////////////
    tmusg.periodStart();

    CellLegalization Test;

    Test.test(W, num, data[0], data[1], data[2], cost, path);

    // // Pinrt out result
    // cout << cost << endl;

    // for (int l = 0;l < num;l++){
    //     // count += weights[l] * abs(path[l] - pos[l]);
    //     cout << path[l] << " ";
    // }
    // cout <<  endl;

    tmusg.getPeriodUsage(stat);
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory

    //////////// write the output file ///////////
    fout << cost << endl;
    for (int i = 0;i < num; i++){
        fout << path[i] << endl;
    }
    fin.close();
    fout.close();
    return 0;
}
