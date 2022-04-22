import numpy as np
import math

def Solve(W, num, widths, pos, weight):
    
    S1 = np.zeros((W))
    S2 = np.zeros((W))
    # C = np.zeros((W))
    sum_ = 0
    i, j = 0, 0 
    for i in range(num):
        sum_ += widths[i]
        for j in range(W):
            if i == 0:
                if j < widths[i] - 1:
                    S1[j] = 0
                    # C[j] = 0
                elif j == widths[i] - 1:
                    p = j - widths[i] + 1
                    S1[j] = weight[i] * abs(p - pos[i])
                    # C[j] = weight[i] * abs(p - pos[i])
                else:
                    p = j - widths[i] + 1
                    temp = weight[i] * abs(p - pos[i])
                    S1[j] = min(S1[j-1], temp)
                    # C[j] = min(S1[j-1], temp)
            else:
                if i%2==1:
                    if j < sum_ - 1:
                        S2[j] = 0
                        # C[j] = 0
                    elif j == sum_ - 1:
                        p = j - widths[i] + 1
                        temp = weight[i] * abs(p - pos[i])
                        S2[j] = S1[j-widths[i]] + temp
                    else:
                        p = j - widths[i] + 1
                        temp = weight[i] * abs(p - pos[i])
                        S2[j] = min(S2[j-1], S1[j-widths[i]] + temp)

                else:
                    if j < sum_ - 1:
                        S1[j] = 0
                        # C[j] = 0
                    elif j == sum_ - 1:
                        p = j - widths[i] + 1
                        temp = weight[i] * abs(p - pos[i])
                        S1[j] = S2[j-widths[i]] + temp
                    else:
                        p = j - widths[i] + 1
                        temp = weight[i] * abs(p - pos[i])
                        S1[j] = min(S1[j-1], S2[j-widths[i]] + temp)
        

    # print("C: ", [int(x) for x in C])
    if i%2 == 1:
        print(S2[-1])
        # print("S: ", [int(x) for x in S2])
    else:
        print(S1[-1])
        # print("S: ", [int(x) for x in S1])
    
    print("=====================================")
        
    path = []
    idx = W-1
    for i in range(num-1, -1, -1):
        # print("S1: ", [int(x) for x in S1])
        # print("S2: ", [int(x) for x in S2])
        
            
        if i%2 == 1:
            for j in range(idx, -1, -1):
                if S2[j] == S2[j-1]:
                    continue
                else:
                    path.append(j-widths[i]+1)
                    idx = j - widths[i]
                    break
            k = idx
            while (S1[k] != 0):
                h = k - widths[i-1]
                p = h + 1
                S2[h] = S1[k] - weight[i-1] * abs(p - pos[i-1])
                h -= 1
                k -= 1
            
        else:
            for j in range(idx, -1, -1):
                if S1[j] == S1[j-1]:
                    continue
                else:
                    path.append(j-widths[i]+1)
                    idx = j - widths[i]
                    break
            k = idx
            while (S2[k] != 0):
                h = k - widths[i-1]
                p = k - widths[i-1] + 1
                S1[h] = S2[k] - weight[i-1] * abs(p - pos[i-1])
                h -= 1
                k -= 1
    print(path)
        
        
            
f = open('./inputs/input_80.txt')
f_in = []
for line in f.readlines():
    f_in.append(list(line.split(" ")))

W = int(f_in[0][0])
num = int(f_in[1][0])
widths = [int(x) for x in f_in[2][:-1]]
pos = [int(x) for x in f_in[3][:-1]]
weight = [int(x) for x in f_in[4][:-1]]

Solve(W, num, widths, pos, weight)