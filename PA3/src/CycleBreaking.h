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
