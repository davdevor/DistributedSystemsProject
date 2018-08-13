import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches


def serial():
    threads = [2,4,8]
    popSize = [10000,15000,20000]
    cities = [29,52,280]
    for threadNum in threads:
        for popNum in popSize:
            for city in cities:
                file = open("openmp-"+str(threadNum)+"-"+str(popNum)+"-"+str(city)+"-30.txt")
                data = file.readlines()
                file.close()
                count = 1.0
                X = []
                y =[]
                for x in data:
                        y.append(float(x.strip()))
                        X.append(count)
                        count += 1.0
                plt.plot(X,y)
                minP = min(y)
                file = open("serial-"+str(popNum)+"-"+str(city)+"-30.txt")
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
                plt.title("Average fitness over 30 seconds for"+ str(city)+ "cities")
                plt.xlabel("Generation number")
                plt.ylabel("Average fitness")
                plt.savefig("population"+str(popNum)+"threads"+str(threadNum)+"city"+str(city)+".svg", format='svg', dpi=1000)
                plt.clf()
serial()

