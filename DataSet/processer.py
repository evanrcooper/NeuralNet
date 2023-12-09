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
    training.write(lines[i][:-2].replace(',', ' '))
    training.write(str(ord(lines[i][-2])-ord('1')))
    training.write("\n")

training.write(lines[trainingLength-1][:-2].replace(',', ' '))
training.write(str(ord(lines[trainingLength-1][-2])-ord('1')))

training.close()

testing = open(input('File Name To Save Test Set To: '), 'w')
testing.write(str(testLength)+" "+inputCount+" "+outputCount+"\n")
for i in range(testLength-1):
    testing.write(lines[i+trainingLength][:-2].replace(',', ' '))
    testing.write(str(ord(lines[i+trainingLength][-2])-ord('1')))
    testing.write("\n")


testing.write(lines[testLength+trainingLength-1][:-2].replace(',', ' '))
testing.write(str(ord(lines[testLength+trainingLength-1][-2])-ord('1')))

testing.close()