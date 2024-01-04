from random import shuffle

data = open('data.csv', 'r')
lines = data.readlines()[1:]
data.close()

maxAge = 0
minAge = 1000

for i in range(len(lines)):
    maxAge = max(maxAge, int(lines[i].split(',')[0]))
    minAge = min(minAge, int(lines[i].split(',')[0]))

# print(minAge)
# print(maxAge)

shuffle(lines)

INPUTS = 16
OUTPUTS = 1
TRAIN_SIZE = round((2 * len(lines)) / 3)
TEST_SIZE = len(lines) - TRAIN_SIZE

def dataToInt(data):
    match data:
        case "Yes" :
            return 1
        case "No" :
            return 0
        case "Male" :
            return 1
        case "Female" :
            return 0
        case "Positive" :
            return 1
        case "Negative" :
            return 0
        case 1 :
            return 0
        case 2 :
            return 1
        case _ :
          return data

def mapTo(age):
    age = int(age) + 0.0
    age -= minAge
    age /= (maxAge-minAge)
    age *= 1000
    age = round(age)
    age /= 1000.0
    age = str(age)
    while len(age) < 5:
        age += '0'
    age = str(age)
    return age

# Age,Gender,Polyuria,Polydipsia,sudden weight loss,weakness,Polyphagia,Genital thrush,visual blurring,Itching,Irritability,delayed healing,partial paresis,muscle stiffness,Alopecia,Obesity,class

training = open('trainingSet.txt', 'w')
training.write(str(TRAIN_SIZE)+" "+str(INPUTS)+" "+str(OUTPUTS)+"\n")

for i in range(TRAIN_SIZE):
    if i != 0:
        training.write("\n")
    line = lines.pop()[:-1]
    data = line.split(',')
    training.write(str(mapTo(int(data[0])))+" ")
    for j in data[1:-1]:
        training.write(str(dataToInt(j))+" ")
    training.write(str(dataToInt(data[-1])))

training.close()

testing = open('testSet.txt', 'w')
testing.write(str(TEST_SIZE)+" "+str(INPUTS)+" "+str(OUTPUTS)+"\n")

for i in range(TEST_SIZE):
    if i != 0:
        testing.write("\n")
    line = lines.pop()[:-1]
    data = line.split(',')
    testing.write(str(mapTo(int(data[0])))+" ")
    for j in data[1:-1]:
        testing.write(str(dataToInt(j))+" ")
    testing.write(str(dataToInt(data[-1])))

testing.close()