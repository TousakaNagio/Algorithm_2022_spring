import numpy as np
import math

def Solve(W, num, widths, pos, weight):
    
    S = np.zeros((num, W))
    E = np.zeros((num, W))
    i, j, count = 0, 0, 0 
    for i in range(num):
        count += widths[i]
        for j in range(W):
            if i == 0:
                
                if j < widths[i] - 1:
                    S[i][j] = 0
                    E[i][j] = 0
                elif j == widths[i] - 1:
                    S[i][j] = weight[i] * abs(j - widths[i] + 1 - pos[i])
                    E[i][j] = j - widths[i] + 1
                else:
                    p = j - widths[i] + 1
                    temp = weight[i] * abs(p - pos[i])
                    S[i][j] = min(S[i][j-1], temp)
                    if S[i][j] == S[i][j-1]:
                        E[i][j] = E[i][j-1]
                    else:
                        E[i][j] = p
            elif j < count - 1:
                S[i][j] = 0
                E[i][j] = 0
            elif j == count - 1:
                S[i][j] = S[i-1][j-widths[i]] + weight[i] * abs(j - widths[i] + 1 - pos[i])
                E[i][j] = j - widths[i] + 1
            else:
                p = j - widths[i] + 1
                temp = weight[i] * abs(p - pos[i])
                S[i][j] = min(S[i][j-1], S[i-1][j-widths[i]] + temp)
                if S[i][j] == S[i][j-1]:
                    E[i][j] = E[i][j-1]
                else:
                    E[i][j] = j-widths[i]+1
    print(S)
    
    print("============================")
    print(E)
    path = []
    path.append(int(E[num-1][W-1]))
    for i in range(num-2, -1, -1):
        path.append(int(E[i][int(path[-1])-1]))
    print(path)
    
            
f = open('./inputs/input_8.txt')
f_in = []
for line in f.readlines():
    f_in.append(list(line.split(" ")))

W = int(f_in[0][0])
num = int(f_in[1][0])
widths = [int(x) for x in f_in[2][:-1]]
pos = [int(x) for x in f_in[3][:-1]]
weight = [int(x) for x in f_in[4][:-1]]

Solve(W, num, widths, pos, weight)