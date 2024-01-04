from random import shuffle

data = open(input('CSV: '), 'r')
lines = data.readlines()
data.close()

shuffle(lines)

trainingLength = round(2*len(lines) / 3)
testLength = len(lines) - trainingLength

inputCount = input('Number Of Inputs: ')
outputCount = input('Number Of Outputs: ')

training = open(input('File Name To Save Training Set To: '), 'w')
training.write(str(trainingLength)+" "+inputCount+" "+outputCount+"\n")
for i in range(trainingLength-1):
    ls = lines[i][:-1].split(',')
    training.write(ls[0]+" "+ls[2]+" "+str(int(ls[3])))
    training.write("\n")

training.write(lines[trainingLength-1][:-1].replace(',', ' '))
ls = lines[trainingLength-1][:-1].split(',')
training.write(ls[0]+" "+ls[2]+" "+str(int(ls[3])))

training.close()

testing = open(input('File Name To Save Test Set To: '), 'w')
testing.write(str(testLength)+" "+inputCount+" "+outputCount+"\n")
for i in range(testLength-1):
    ls = lines[i+trainingLength][:-1].split(',')
    testing.write(ls[0]+" "+ls[2]+" "+str(int(ls[3])))
    testing.write("\n")


ls = lines[testLength+trainingLength-1][:-1].split(',')
testing.write(ls[0]+" "+ls[2]+" "+str(int(ls[3])))

testing.close()