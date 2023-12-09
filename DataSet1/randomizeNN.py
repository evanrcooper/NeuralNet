from random import random

file = open(input('File Name To Save Neural Net To: '), 'w')

inputNodes = int(input('Input Nodes: '))
hiddenNodes = int(input('Hidden Layer Nodes: '))
outputNodes = int(input('Output Nodes: '))

file.write(str(inputNodes)+" "+str(hiddenNodes)+" "+str(outputNodes)+"\n")

# random number from -1 to 1

for h in range(hiddenNodes):
    for i in range(inputNodes):
        file.write(str(round(random(), 3))+" ")
    file.write(str(round(random(), 3))+"\n")

for o in range(outputNodes):
    for h in range(hiddenNodes):
        file.write(str(round(random(), 3))+" ")
    file.write(str(round((random()), 3)))

file.close()