from random import shuffle
import math

def normalize(min, max, val):
    return (val-min)/(max-min)

def sigmoid(x):
    return 1 / (1 + math.exp(-x))

def get_data(val):
    match val:
        case 'Male':
            return 1.0
        case 'Female':
            return 0.0
        case 'Graduate':
            return 1.0
        case 'Not Graduate':
            return 1.0
        case 'Urban':
            return 1.0
        case 'Semiurban':
            return 0.5
        case 'Rural':
            return 0.0
        case 'Yes':
            return 1.0
        case 'No':
            return 0.0
        case 'Y':
            return 1
        case 'N':
            return 0
        case '3+':
            return 4
        case _:
            try:
                return float(val)
            except:
                return 0.0

data = open('loan_data.csv', 'r')
lines = data.readlines()
cols = [item.strip() for item in lines[0].split(',')[1:]]
lines = lines[1:]
values = [[get_data(val.strip()) for val in line.split(',')[1:]] for line in lines]
data.close()

def getMinMax(values: list[list[float]], index: int) -> tuple[int, int]:
    return min([values[i][index] for i in range(len(values))]), max([values[i][index] for i in range(len(values))])

minDependents, maxDependents = getMinMax(values, cols.index('Dependents'))
minApplicantIncome, maxApplicantIncome = getMinMax(values, cols.index('ApplicantIncome'))
minCoapplicantIncome, maxCoapplicantIncome = getMinMax(values, cols.index('CoapplicantIncome'))
minLoanAmount, maxLoanAmount = getMinMax(values, cols.index('LoanAmount'))
minLoanAmountTerm, maxLoanAmountTerm = getMinMax(values, cols.index('LoanAmountTerm'))

for i, row in enumerate(values):
    row[cols.index('Dependents')] = normalize(minDependents, maxDependents, row[cols.index('Dependents')])
    row[cols.index('ApplicantIncome')] = normalize(minApplicantIncome, maxApplicantIncome, row[cols.index('ApplicantIncome')])
    row[cols.index('CoapplicantIncome')] = normalize(minCoapplicantIncome, maxCoapplicantIncome, row[cols.index('CoapplicantIncome')])
    row[cols.index('LoanAmount')] = normalize(minLoanAmount, maxLoanAmount, row[cols.index('LoanAmount')])
    row[cols.index('LoanAmountTerm')] = normalize(minLoanAmountTerm, maxLoanAmountTerm, row[cols.index('LoanAmountTerm')])

dataSetSize = len(values)

shuffle(values)

OUTPUTS = 1
INPUTS = len(values[0])-OUTPUTS
TRAIN_SIZE = round((2 * dataSetSize) / 3)
TEST_SIZE = dataSetSize - TRAIN_SIZE

training = open('trainingSet.txt', 'w')
training.write(str(TRAIN_SIZE)+" "+str(INPUTS)+" "+str(OUTPUTS)+"\n")

for i in range(TRAIN_SIZE-1):
    training.write(' '.join(f'{val:.3f}' for val in values[i])+'\n')
training.write(' '.join(f'{val:.3f}' for val in values[TRAIN_SIZE-1]))
training.close()

training = open('testSet.txt', 'w')
training.write(str(TEST_SIZE)+" "+str(INPUTS)+" "+str(OUTPUTS)+"\n")

for i in range(TEST_SIZE-1):
    training.write(' '.join(f'{val:.3f}' for val in values[i+TRAIN_SIZE])+'\n')
training.write(' '.join(f'{val:.3f}' for val in values[TEST_SIZE-1+TRAIN_SIZE]))
training.close()