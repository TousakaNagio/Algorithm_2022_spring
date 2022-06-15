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
