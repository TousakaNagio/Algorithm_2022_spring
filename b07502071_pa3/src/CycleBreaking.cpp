#include "CycleBreaking.h"
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <vector>

// Constructor
CycleBreaking::CycleBreaking() {}

int CycleBreaking::undirectedGraph(int num_V, int num_E, int **weights, int **PI)
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

        PI[u][1] = BOUNDARY - 1;
        if (u != 0)
        {
            if (weights[u][PI[u][0]] <= weights[PI[u][0]][u])
            {
                weights[PI[u][0]][u] = OUB;
            }
            else
            {
                weights[u][PI[u][0]] = OUB;
            }
        }
        j = 0;
        while (j < num_V)
        {
            if (weights[u][j] >= LIMIT)
            {
                if ((PI[j][1] != BOUNDARY - 1) && (weights[u][j] > PI[j][1]))
                {
                    int temp = u;
                    PI[j][0] = temp;
                    temp = weights[u][j];
                    PI[j][1] = temp;
                }
            }
            if (weights[j][u] >= LIMIT)
            {
                if ((PI[j][1] != BOUNDARY - 1) && (weights[j][u] > PI[j][1]))
                {
                    int temp = u;
                    PI[j][0] = temp;
                    temp = weights[j][u];
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
            if (weights[i][j] >= LIMIT)
            {
                sum += weights[i][j];
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
    //         cout << weights[i][j] << " ";
    //     }
    //     cout << PI[i][0] << " " << PI[i][1];
    //     cout << endl;
    // }
    return sum;
}
int CycleBreaking::directedGraph(int num_V, int num_E, int **weights, int **PI)
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

        PI[u][1] = BOUNDARY - 1;
        if (u != 0)
        {
            if (weights[u][PI[u][0]] <= weights[PI[u][0]][u])
            {
                weights[PI[u][0]][u] = OUB;
            }
            else
            {
                weights[u][PI[u][0]] = OUB;
            }
        }
        j = 0;
        while (j < num_V)
        {
            if (weights[u][j] >= LIMIT)
            {
                if ((PI[j][1] != BOUNDARY - 1) && (weights[u][j] > PI[j][1]))
                {
                    int temp = u;
                    PI[j][0] = temp;
                    temp = weights[u][j];
                    PI[j][1] = temp;
                }
            }
            if (weights[j][u] >= LIMIT)
            {
                if ((PI[j][1] != BOUNDARY - 1) && (weights[j][u] > PI[j][1]))
                {
                    int temp = u;
                    PI[j][0] = temp;
                    temp = weights[j][u];
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
        while (i < num_V) // To find out the maximum weight for each vertex
        {
            int j = 0;
            while (j < num_V)
            {
                if (weights[i][j] >= 0)
                {
                    if (!(weights[i][j] <= weights[s][t]))
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
        int finish;
        int *check;
        finish = 0;
        check = new int[num_V];
        for (int i = 0; i < num_V; i++)
        {
            check[i] = 0;
        }
        check[t] = 1;

        int v;
        while (queue.empty() != true && finish != 1)
        {
            v = queue.front();
            queue.erase(queue.begin());
            int i = 0;
            while (i < num_V)
            {
                if (weights[v][i] == OUB)
                {
                    if (i == s)
                    {
                        finish = 1;
                        weights[s][t] += INFINITY + LIMIT;
                        queue.clear();
                    }
                    if (check[i] == 0)
                    {
                        queue.push_back(i);
                        check[i] = 1;
                    }
                }
                i++;
            }
            if (finish){
                break;
            }
        }
        if (!finish)
        {
            weights[s][t] = OUB;
        }
    }

    int sum = 0;
    i = 0;
    while (i < num_V)
    {
        int j = 0;
        while (j < num_V)
        {
            if (weights[i][j] >= LIMIT)
            {
                sum += weights[i][j];
            }
            if (weights[i][j] <= INFINITY)
            {
                weights[i][j] -= INFINITY + LIMIT;
                sum += weights[i][j];
            }
            j++;
        }
        i++;
    }
    return sum;
}
