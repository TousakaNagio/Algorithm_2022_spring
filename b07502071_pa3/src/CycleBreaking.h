#ifndef _Cycle_Breaking_H
#define _Cycle_Breaking_H
#define LIMIT -100
#define BOUNDARY LIMIT-1
#define OUB BOUNDARY-2
#define INFINITY -2147483547



#include<vector>
using namespace std;

class CycleBreaking {
    public:
                    CycleBreaking();
                    int undirectedGraph(int, int, int **, int **);
                    int directedGraph(int, int, int **, int **);
};

#endif
