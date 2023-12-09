#include "NN.h"

using namespace std;

void NeuralNet::buildNeuralNet(string inputFileName) {
    // open file
    fstream file;
    file.open(inputFileName);
    if (!file.is_open()) {
        cerr << "File Does Not Exist";
    }

    string line, inNodes, hNodes, outNodes;
    getline(file, line);
    stringstream buffer(line);

    // get member variables
    buffer >> inNodes;
    buffer >> hNodes;
    buffer >> outNodes;
    inputNodes = stoi(inNodes);
    hiddenLayerNodes = stoi(hNodes);
    outputNodes = stoi(outNodes);

    if (inputNodes == 0 || hiddenLayerNodes == 0 || outputNodes == 0) {
        cerr << "Invalid Neural Net Structure";
    }

    // get weights and biases of input->hiddenLayer
    string bias, weight;
    for (int h = 0; h < hiddenLayerNodes; h++) {
        getline(file, line);
        stringstream buffer(line);
        buffer >> bias;
        hiddenLayerBiases.push_back(stod(bias));
        inputToHiddenLayerWeights.push_back(new vector<double>());
        for (int i = 0; i < inputNodes; i++) {
            buffer >> weight;
            inputToHiddenLayerWeights[h]->push_back(stod(weight));
        }
    }

    // get weights and biases of hiddenLayer->output
    for (int o = 0; o < outputNodes; o++) {
        getline(file, line);
        stringstream buffer(line);
        buffer >> bias;
        outputBiases.push_back(stod(bias));
        hiddenLayerToOutputWeights.push_back(new vector<double>());
        for (int h = 0; h < hiddenLayerNodes; h++) {
            buffer >> weight;
            hiddenLayerToOutputWeights[o]->push_back(stod(weight));
        }
    }

    file.close();
}

void NeuralNet::saveNeuralNet(string outputFileName) const {
    ofstream file(outputFileName);
    if (!file.is_open()) {
        cerr << "Error Creating File";
    }
    file << inputNodes << " " << hiddenLayerNodes << " " << outputNodes << "\n";
    for (int h = 0; h < hiddenLayerNodes; h++) {
        if (h != 0) {file << "\n";}
        file << fixed << setprecision(3);
        file << hiddenLayerBiases[h] << " ";
        for (int i = 0; i < inputNodes; i++) {
            if (i != 0) {file << " ";}
            file << fixed << setprecision(3);
            file << (*inputToHiddenLayerWeights[h])[i];
        }
    }
    for (int o = 0; o < outputNodes; o++) {
        file << "\n";
        file << fixed << setprecision(3);
        file << outputBiases[o] << " ";
        for (int h = 0; h < hiddenLayerNodes; h++) {
            if (h != 0) {file << " ";}
            file << fixed << setprecision(3);
            file << (*hiddenLayerToOutputWeights[o])[h];
        }
    }
    file.close();
    return;
}

// forward propagation
vector<double> NeuralNet::runNeuralNet(const vector<double> &inputs, vector<double> *hiddenLayerOutputs) const {
    // calculate the values of the hidden layer nodes
    vector<double> hiddenLayerValues = vector<double>();
    
    if (hiddenLayerOutputs) {
        hiddenLayerOutputs->clear();
    }

    for (int h = 0; h < hiddenLayerNodes; h++) {
        double hiddenNodeValue = 0;
        for (int i = 0; i < inputNodes; i++) {
            hiddenNodeValue += inputs[i] * (*inputToHiddenLayerWeights[h])[i];
            // hiddenNodeValue += (inputs[i] >= 0.5) ? (*inputToHiddenLayerWeights[h])[i] : (-1)*(*inputToHiddenLayerWeights[h])[i];
        }
        double hiddenOut = sigmoid(hiddenNodeValue - hiddenLayerBiases[h]);
        hiddenLayerValues.push_back(hiddenOut);
        if (hiddenLayerOutputs) {
            hiddenLayerOutputs->push_back(hiddenOut);
        }
    }

    // calculate the values of the output nodes
    vector<double> outputNodeValues = vector<double>();
    for (int o = 0; o < outputNodes; o++) {
        double outputNodeValue = 0;
        for (int h = 0; h < hiddenLayerNodes; h++) {
            outputNodeValue += hiddenLayerValues[h] * (*hiddenLayerToOutputWeights[o])[h];
        }
        outputNodeValues.push_back(sigmoid(outputNodeValue - outputBiases[o]));
    }
    
    return outputNodeValues;
}

void NeuralNet::trainNeuralNet(const string &trainingSetFile, const unsigned long int &epochs, const double &learningRate) {
    
    // check file
    fstream file;
    file.open(trainingSetFile);
    if (!file.is_open()) {
        cerr << "File Does Not Exist";
    }

    for (int e = 0; e < epochs; e++) {
        singleEpoch(trainingSetFile, learningRate);
        // cout << "Epoch #" << e+1 << " Completed\n";
    }

    file.close();
}

void NeuralNet::singleEpoch(const string &trainingSetFile, const double &learningRate) {

    fstream file;
    file.open(trainingSetFile);

    string line, trainingExamplesStr, testInputsStr, testOutputsStr;
    getline(file, line);
    stringstream bufferFirstLine(line);

    bufferFirstLine >> trainingExamplesStr;
    bufferFirstLine >> testInputsStr;
    bufferFirstLine >> testOutputsStr;

    int trainingExamples = stoi(trainingExamplesStr);
    if (inputNodes != stoi(testInputsStr) && outputNodes != stoi(testOutputsStr)) {
        cerr << "Test File Is Not Compatible With Neural Net";
    }

    for (int t = 0; t < trainingExamples; t++) {

        getline(file, line);
        stringstream buffer(line);
        vector<double> inputs = vector<double>(inputNodes);
        vector<double> desiredOutputs = vector<double>(outputNodes);
        
        string currentInput;
        for (int i = 0; i < inputNodes; i++) {
            buffer >> currentInput;
            inputs[i] = stod(currentInput);
        }

        string currentOutput;
        for (int d = 0; d < outputNodes; d++) {
            buffer >> currentOutput;
            desiredOutputs[d] = stod(currentOutput);
        }

        vector<double> hiddenlayerOutputs = vector<double>();

        vector<double> outputs = runNeuralNet(inputs, &hiddenlayerOutputs);

        vector<double> outputDeltas = vector<double>(outputNodes); // output deltas
        vector<double> hiddenLayerDeltas = vector<double>(hiddenLayerNodes, 0.0);

        for (int o = 0; o < outputNodes; o++) {
            outputDeltas[o] = sigmoidPrime(outputs[o]) * (desiredOutputs[o] - outputs[o]);
        }

        for (int h = 0; h < hiddenLayerNodes; h++) {
            for (int o = 0; o < outputNodes; o++) {
                hiddenLayerDeltas[h] += (*hiddenLayerToOutputWeights[o])[h] * outputDeltas[o];
            }
            hiddenLayerDeltas[h] *= sigmoidPrime(hiddenlayerOutputs[h]);
        }

        // update weights and biases

        // input -> hidden
        for (int h = 0; h < hiddenLayerNodes; h++) {
            for (int i = 0; i < inputNodes; i++) {
                (*inputToHiddenLayerWeights[h])[i] += learningRate * inputs[i] * hiddenLayerDeltas[h];
            }
        }

        // hidden -> output
        for (int o = 0; o < outputNodes; o++) {
            for (int h = 0; h < hiddenLayerNodes; h++) {
                (*hiddenLayerToOutputWeights[o])[h] += learningRate * hiddenlayerOutputs[h] * outputDeltas[o];
            }
        }

        // hidden biases
        for (int h = 0; h < hiddenLayerNodes; h++) {
            hiddenLayerBiases[h] += (-1)*learningRate*hiddenLayerDeltas[h];
        }

        // output biases
        for (int o = 0; o < outputNodes; o++) {
            outputBiases[o] += (-1)*learningRate*outputDeltas[o];
        }

    }

    if (file.is_open()) {
        file.close();
    }
}

vector<confusionMatrix> NeuralNet::makeContingencyTable(const string &testSetFileName) const {

    // open file
    fstream file;
    file.open(testSetFileName);
    if (!file.is_open()) {
        cerr << "File Does Not Exist";
    }

    string line, testSetLength, inputLength, outputLength, input, output;
    getline(file, line);
    stringstream buffer(line);
    
    buffer >> testSetLength;
    buffer >> inputLength;
    buffer >> outputLength;

    if (stoi(inputLength) != inputNodes || stoi(outputLength) != outputNodes) {
        cout << "File Name To Save Neural Net";
        string saveFileName;
        cin >> saveFileName;
        saveNeuralNet(saveFileName);
        cerr << "Neural Net Is Incompatible With Test Set";
    }

    vector<confusionMatrix> matrices = vector<confusionMatrix>(outputNodes);
    for (int o = 0; o < outputNodes; o++) {
        matrices[o] = confusionMatrix();
    }
    
    int testCases = stoi(testSetLength);

    if (testCases <= 0) {
        cerr << "Invalid Test Case File";
    }

    for (int t = 0; t < testCases; t++) {

        getline(file, line);
        stringstream buffer(line);

        vector<double> inputs = vector<double>(inputNodes);
        vector<int> expectedOutputs = vector<int>(outputNodes);

        for (int i = 0; i < inputNodes; i++) {
            buffer >> input;
            inputs[i] = stod(input);
        }

        for (int o = 0; o < outputNodes; o++) {
            buffer >> output;
            expectedOutputs[o] = stoi(output);
        }

        vector<double> actualOutputs = this->runNeuralNet(inputs);

        for (int o = 0; o < outputNodes; o++) {

            if (expectedOutputs[o] == 1) {
                if (actualOutputs[o] >= 0.5) {
                    matrices[o].A++;
                } else if (actualOutputs[o] < 0.5) {
                    matrices[o].C++;
                }
            } else if (expectedOutputs[o] == 0) {
                if (actualOutputs[o] >= 0.5) {
                    matrices[o].B++;
                } else if (actualOutputs[o] < 0.5){
                    matrices[o].D++;
                }
            } else {
                cerr << "Expected Boolean Output In Test Set";
            }

        }

    }

    return matrices;

}

 void NeuralNet::printMetrics(const string &testSetFileName, const string &outputFileName) const {

    ofstream file(outputFileName);
    if (!file.is_open()) {
        cerr << "Error Creating File";
    }

    vector<confusionMatrix> matrices = makeContingencyTable(testSetFileName);

    double macroAvgAccuracy = 0.0;
    double macroAvgPrecision = 0.0;
    double macroAvgRecall = 0.0;
    double macroAvgF1 = 0.0;

    int globalA = 0;
    int globalB = 0;
    int globalC = 0;
    int globalD = 0;

    for (int o = 0; o < outputNodes; o++) {

        int A = matrices[o].A;
        globalA += A;

        int B = matrices[o].B;
        globalB += B;
        
        int C = matrices[o].C;
        globalC += C;
        
        int D = matrices[o].D;
        globalD += D;
        
        /*
            (1)	Overall accuracy = (A + D) / (A + B + C + D);
            (2)	Precision = A / (A + B);
            (3)	Recall = A / (A + C);
            (4)	F1 = (2 * Precision * Recall) / (Precision + Recall);
        */

        if ((A + B) == 0 || (A + C) == 0) {
            cerr << "Division By 0: NeuralNet::printMetrics()";
        }

        double accuracy = double(A + D) / (A + B + C + D);
        macroAvgAccuracy += accuracy;

        double precision = double(A) / (A + B);
        macroAvgPrecision += precision;
        
        double recall = double(A) / (A + C);
        macroAvgRecall += recall;
        
        double f1 = double(2 * precision * recall) / (precision + recall);
        macroAvgF1 += f1;
        

        file << A << " ";
        file << B << " ";
        file << C << " ";
        file << D << " ";

        file << fixed << setprecision(3);
        file << accuracy << " ";

        file << fixed << setprecision(3);
        file << precision << " ";

        file << fixed << setprecision(3);
        file << recall << " ";

        file << fixed << setprecision(3);
        file << f1 << '\n';

    }

    // Micro Averages

    double microAvgAccuracy = double(globalA + globalD) / (globalA + globalB + globalC + globalD);
    double microAvgPrecision = double(globalA) / (globalA + globalB);
    double microAvgRecall = double(globalA) / (globalA + globalC);
    double microAvgF1 = double(2 * microAvgPrecision * microAvgRecall) / (microAvgPrecision + microAvgRecall);

    file << fixed << setprecision(3);
    file << microAvgAccuracy << " ";

    file << fixed << setprecision(3);
    file << microAvgPrecision << " ";
    
    file << fixed << setprecision(3);
    file << microAvgRecall << " ";
    
    file << fixed << setprecision(3);
    file << microAvgF1 << '\n';

    // Macro Averages

    macroAvgAccuracy /= outputNodes;
    macroAvgPrecision /= outputNodes;
    macroAvgRecall /= outputNodes;
    macroAvgF1 /= outputNodes;

    file << fixed << setprecision(3);
    file << macroAvgAccuracy << " ";

    file << fixed << setprecision(3);
    file << macroAvgPrecision << " ";
    
    file << fixed << setprecision(3);
    file << macroAvgRecall << " ";
    
    file << fixed << setprecision(3);
    file << macroAvgF1 << '\n';

    file.close();
    
 }