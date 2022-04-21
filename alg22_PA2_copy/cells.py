import numpy as np
import math

def Solve(W, num, widths, pos, weight):
    
    def Min(S, i, j, width):
        p = j - widths[i] + 1
        temp = weight[i] * abs(p - pos[i])
        S[j] = min(S[j-1], last[j-widths[i]] + temp)
        pass
        
    ans = pos
    
    S = np.zeros((W))
    sum_ = 0
    i, j = 0, 0 
    for i in range(num):
        sum_ += widths[i]
        last = S.copy()
        for j in range(W):
            if i == 0:
                if j < widths[i] - 1:
                    S[j] = 0
                elif j == widths[i] - 1:
                    S[j] = weight[i] * abs(j - widths[i] + 1 - pos[i])
                else:
                    p = j - widths[i] + 1
                    temp = weight[i] * abs(p - pos[i])
                    S[j] = min(S[j-1], temp)
            elif j < sum_ - 1:
                S[j] = last[j]
            elif j == sum_ - 1:
                S[j] = last[j-widths[i]] + weight[i] * abs(j - widths[i] + 1 - pos[i])
            else:
                Min(S, i, j, widths)
                # p = j - widths[i] + 1
                # temp = weight[i] * abs(p - pos[i])
                # S[j] = min(S[j-1], last[j-widths[i]] + temp)
        print(S)
            
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