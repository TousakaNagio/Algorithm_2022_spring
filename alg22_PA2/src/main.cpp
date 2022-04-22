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

    vector< vector<long long> > data;

    for (int i = 0;i < 5;i++){
        string dir;
        stringstream ss(lines[i]);
        vector<long long> temps;
        while(getline(ss, dir, ' ')){
            long long temp;
            temp = stoi(dir);
            temps.push_back (temp);
        }
        data.push_back(temps);
    }
    
    // for (int i=0;i<5;i++){
    //     for (int j=0;j<data[i].size();j++){
    //         cout << data[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    //////////// the solving part ////////////////
    tmusg.periodStart();

    CellLegalization Test;

    Test.test(data);

    tmusg.getPeriodUsage(stat);
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory

    //////////// write the output file ///////////
    fout << "# " << data.size() << " data points" <<endl;
    fout << "# index number" << endl;
    for (int i = 0; i < data.size(); i++)
        fout << i << " " <<data[0][i] << endl;
    fin.close();
    fout.close();
    return 0;
}
