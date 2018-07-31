import math
import numpy
coordinates = []
fileName = input("enter in the file name: ")
newFileName = input("enter new file name: ")
numCities = int(input("enter cities number: "))
matrix = numpy.zeros(shape=(numCities,numCities))
distance= numpy.zeros(shape=(numCities,numCities))
with open(fileName) as file:
    for x in range(0,6):
        file.readline()
    for x in range(0,int(numCities)):
        line = file.readline()
        line = " ".join(line.split())
        nums = line.split(" ")
        coordinates.insert(int(nums[0]),[float(nums[1]),float(nums[2])])
for x in range(numCities):
    x1 = coordinates[x][0]
    y1 = coordinates[x][1]
    for y in range(numCities):
        x2 = coordinates[y][0]
        y2 = coordinates[y][1]
        xd = x1 - x2
        yd = y1 - y2
        matrix[x][y] = math.sqrt(xd*xd + yd*yd)

with open(newFileName, "w") as file:
    for i in range(numCities):
        j = 0
        foundZero = False
        while not foundZero:
            if matrix[i][j] == 0:
                break
            j += 1
        for x in range(j+1, numCities):
            file.write(str(matrix[i][x])+" ")
        file.write("\n")
