#ifndef _Cycle_Breaking_H
#define _Cycle_Breaking_H
#define LIMIT -100
#define BOUNDRY LIMIT-1
#define NIL -1000
#define NOQ -105


#include<vector>
using namespace std;

class CycleBreaking {
    public:
                    CycleBreaking();
                    int undirectedGraph(int, int, int **, int **);
                    int directedGraph(int, int, int **, int **);
};

#endif
#include "CycleBreaking.h"
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <vector>

// Constructor
CycleBreaking::CycleBreaking() {}

int CycleBreaking::undirectedGraph(int num_V, int num_E, int **G, int **PI)
{
    int i = 0;
    while (i < num_V)
    {
        int u = 0;
        int j = 1;
        while (j <= num_V - 1)
        {
            if (PI[j][1] > PI[u][1])
            {
                if (PI[j][1] >= LIMIT)
                {
                    u = j;
                }
            }
            j++;
        }

        PI[u][1] = BOUNDRY - 1;
        if (u != 0)
        {
            if (G[u][PI[u][0]] > G[PI[u][0]][u])
            {
                G[u][PI[u][0]] = NOQ;
            }
            else
            {
                G[PI[u][0]][u] = NOQ;
            }
        }
        j = 0;
        while (j < num_V)
        {
            if (G[u][j] >= LIMIT)
            {
                if ((PI[j][1] != BOUNDRY - 1) && (G[u][j] > PI[j][1]))
                {
                    int temp = u;
                    PI[j][0] = temp;
                    temp = G[u][j];
                    PI[j][1] = temp;
                }
            }
            if (G[j][u] >= LIMIT)
            {
                if ((PI[j][1] != BOUNDRY - 1) && (G[j][u] > PI[j][1]))
                {
                    int temp = u;
                    PI[j][0] = temp;
                    temp = G[j][u];
                    PI[j][1] = temp;
                }
            }
            j++;
        }
        i++;
    }
    int sum = 0;
    i = 0;
    while (i < num_V)
    {
        int j = 0;
        while (j < num_V)
        {
            if (G[i][j] >= LIMIT)
            {
                sum += G[i][j];
            }
            if (G[i][j] <= NIL)
            {
                G[i][j] += 1100;
                sum += G[i][j];
            }
            j++;
        }
        i++;
    }
    // cout << "==========================" << endl;
    // for (int i = 0; i < num_V; i++)
    // {
    //     for (int j = 0; j < num_V; j++)
    //     {
    //         cout << G[i][j] << " ";
    //     }
    //     cout << PI[i][0] << " " << PI[i][1];
    //     cout << endl;
    // }
    return sum;
}
int CycleBreaking::directedGraph(int num_V, int num_E, int **G, int **PI)
{
    int i = 0;
    while (i < num_V)
    {
        int u = 0;
        int j = 1;
        while (j <= num_V - 1)
        {
            if (PI[j][1] > PI[u][1])
            {
                if (PI[j][1] >= LIMIT)
                {
                    u = j;
                }
            }
            j++;
        }

        PI[u][1] = BOUNDRY - 1;
        if (u != 0)
        {
            if (G[u][PI[u][0]] > G[PI[u][0]][u])
            {
                G[u][PI[u][0]] = NOQ;
            }
            else
            {
                G[PI[u][0]][u] = NOQ;
            }
        }
        j = 0;
        while (j < num_V)
        {
            if (G[u][j] >= LIMIT)
            {
                if ((PI[j][1] != BOUNDRY - 1) && (G[u][j] > PI[j][1]))
                {
                    int temp = u;
                    PI[j][0] = temp;
                    temp = G[u][j];
                    PI[j][1] = temp;
                }
            }
            if (G[j][u] >= LIMIT)
            {
                if ((PI[j][1] != BOUNDRY - 1) && (G[j][u] > PI[j][1]))
                {
                    int temp = u;
                    PI[j][0] = temp;
                    temp = G[j][u];
                    PI[j][1] = temp;
                }
            }
            j++;
        }
        i++;
    }

    while (true)
    {
        int s, t;
        s = 0;
        t = 0;
        int i = 0;
        while (i < num_V)
        {
            int j = 0;
            while (j < num_V)
            {
                if (G[i][j] >= 0)
                {
                    if (!(G[i][j] <= G[s][t]))
                    {
                        t = j;
                        s = i;
                    }
                }
                j++;
            }
            i++;
        }

        if ((s == 0) && (t == 0))
        {
            break;
        }

        vector<int> queue;
        queue.push_back(t);
        bool end;
        bool *judge;
        end = false;
        judge = new bool[num_V];
        i = 0;
        while (i < num_V)
        {
            judge[i] = false;
            i++;
        }
        judge[t] = true;

        int v;
        while (queue.empty() != true && end != true)
        {
            v = queue.front();
            queue.erase(queue.begin());
            int i = 0;
            while (i < num_V)
            {
                if (G[v][i] == NOQ)
                {
                    if (i == s)
                    {
                        end = true;
                        G[s][t] -= 1100;
                        queue.clear();
                        break;
                    }
                    if (judge[i] == false)
                    {
                        queue.push_back(i);
                        judge[i] = true;
                    }
                }
                i++;
            }
        }
        if (end == false)
        {
            G[s][t] = NOQ;
        }
    }

    int sum = 0;
    i = 0;
    while (i < num_V)
    {
        int j = 0;
        while (j < num_V)
        {
            if (G[i][j] >= LIMIT)
            {
                sum += G[i][j];
            }
            if (G[i][j] <= NIL)
            {
                G[i][j] += 1100;
                sum += G[i][j];
            }
            j++;
        }
        i++;
    }
    return sum;
}
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string.h>
#include "../lib/tm_usage.h"
#include "CycleBreaking.h"
// #define NLM -100

using namespace std;

void help_message()
{
    cout << "usage: cb <input_file> <output_file>" << endl;
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
        for (int j = 0; j < num_V; j++)
        {
            vertices[i][j] = BOUNDRY;
        }
        i++;
    }
    i = 0;
    while (i < num_V)
    {
        pi[i][0] = -1;
        pi[i][1] = BOUNDRY;
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
