import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches
def serial():
    file = open('openmp.txt','r')
    data = file.readlines()
    file.close()
    count = 1.0
    X = []
    y =[]
    #for x in range(10):
    for x in data:
            y.append(float(x.strip()))
            X.append(count)
            count += 1.0
    plt.plot(X,y)
    minP = min(y)
    file = open('serial.txt','r')
    data = file.readlines()
    file.close()
    temp = count
    count = 1.0
    X = []
    y =[]
    for x in data:
            y.append(float(x.strip()))
            X.append(count)
            count += 1.0
    minS = min(y)
    plt.plot(X,y, label ='serial')
    orange_patch = mpatches.Patch(color='orange', label='Serial min, ' + str(minS) + ' Last Generation number ' + str(count))
    blue_patch = mpatches.Patch(color='skyblue', label='Parallel min, ' + str(minP) + ' Last Generation number ' + str(temp))
    plt.legend(handles=[blue_patch,orange_patch])
    plt.title("Average fitness over 30 seconds for 29 cities")
    plt.xlabel("Generation number")
    plt.ylabel("Average fitness")
    plt.savefig('fitness.svg',format='svg', dpi=1000)
serial()
