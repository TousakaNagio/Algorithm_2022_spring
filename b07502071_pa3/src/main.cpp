#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string.h>
#include "../lib/tm_usage.h"
#include "CycleBreaking.h"

using namespace std;

void help_message()
{
    cout << "usage: ./bin/cb <input_file> <output_file>" << endl;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        help_message();
        return 0;
    }
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    //////////// read the input file /////////////
    int **vertices, **pi;
    char type;
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);

    int num_V;
    int num_E;
    int v1, v2, w, zero;
    fin >> type >> num_V >> num_E;

    vertices = new int *[num_V];
    pi = new int *[num_V];
    int i = 0;
    while (i < num_V)
    {
        vertices[i] = new int[num_V];
        pi[i] = new int[2];
        pi[i][0] = -1;
        pi[i][1] = BOUNDARY;
        for (int j = 0; j < num_V; j++)
        {
            vertices[i][j] = BOUNDARY;
        }
        i++;
    }
    i = 0;
    while (i < num_E)
    {
        fin >> v1 >> v2 >> w;
        vertices[v1][v2] = w;
        i++;
    }
    // cout << num_V << endl;
    // cout << num_E << endl;
    // for (int i = 0;i < num_V; i++){
    //     for (int j = 0; j < num_V + 3; j++){
    //         cout << vertices[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "============================" << endl;
    fin >> zero;

    //////////// the solving part ////////////////
    tmusg.periodStart();

    CycleBreaking Solver;
    int sum;
    if (type == 'u')
    {
        sum = Solver.undirectedGraph(num_V, num_E, vertices, pi);
    }
    else if (type == 'd')
    {
        sum = Solver.directedGraph(num_V, num_E, vertices, pi);
    }
    else
    {
        cout << "Wrong type !" << endl;
    }

    tmusg.getPeriodUsage(stat);
    cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout << "memory: " << stat.vmPeak << "KB" << endl; // print peak memory

    //////////// write the output file ///////////
    fout << sum << endl;
    // cout << sum << endl;
    for (int i = 0; i < num_V; i++)
    {
        for (int j = 0; j < num_V; j++)
        {
            if (vertices[i][j] >= LIMIT)
            {
                // cout << i << " " << j << " " << vertices[i][j] << endl;
                fout << i << " " << j << " " << vertices[i][j] << endl;
            }
        }
    }
    cout << "End" << endl;
    fout.close();
    fin.close();
}
