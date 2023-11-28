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

string NeuralNet::doubleToString(double d, int decimals) const {
    string doubleAsString = to_string(d);
    string preciseDouble= "";
    for (int i = 0; i < doubleAsString.length(); i++) {
        if (doubleAsString[i] != '.') {
            preciseDouble.push_back(doubleAsString[i]);
            continue;
        } else {
            preciseDouble.push_back('.');
            i++;
            for (int j = 0; j < decimals; j++) {
                if (i+j < doubleAsString.length()) {
                    preciseDouble.push_back(doubleAsString[i+j]);
                } else {
                    preciseDouble.push_back('0');
                }
            }
            break;
        }
    }
    return preciseDouble;
}

void NeuralNet::saveNeuralNet(string outputFileName) {
    ofstream file(outputFileName);
    if (!file.is_open()) {
        cerr << "Error Creating File";
    }
    file << inputNodes << " " << hiddenLayerNodes << " " << outputNodes << "\n";
    for (int h = 0; h < hiddenLayerNodes; h++) {
        if (h != 0) {file << "\n";}
        file << doubleToString(hiddenLayerBiases[h]) << " ";
        for (int i = 0; i < inputNodes; i++) {
            if (i != 0) {file << " ";}
            file << doubleToString((*inputToHiddenLayerWeights[h])[i]);
        }
    }
    for (int o = 0; o < outputNodes; o++) {
        file << "\n";
        file << doubleToString(outputBiases[o]) << " ";
        for (int h = 0; h < hiddenLayerNodes; h++) {
            if (h != 0) {file << " ";}
            file << doubleToString((*hiddenLayerToOutputWeights[o])[h]);
        }
    }
    file.close();
    return;
}

[[nodiscard]] vector<double> NeuralNet::runNeuralNet(const vector<double> &inputs) const {
    // calculate the values of the hidden layer nodes
    vector<double> hiddenLayerValues = vector<double>();
    for (int h = 0; h < hiddenLayerNodes; h++) {
        double hiddenNodeValue = 0;
        for (int i = 0; i < inputNodes; i++) {
            hiddenNodeValue += inputs[i] * (*inputToHiddenLayerWeights[h])[i];
            // hiddenNodeValue += (inputs[i] >= 0.5) ? (*inputToHiddenLayerWeights[h])[i] : (-1)*(*inputToHiddenLayerWeights[h])[i];
        }
        hiddenLayerValues.push_back(sigmoid(hiddenNodeValue - hiddenLayerBiases[h]));
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

void NeuralNet::trainNeuralNet(const string &testSetFile, const unsigned short int &epochs) {
    // open file
    fstream file;
    file.open(testSetFile);
    if (!file.is_open()) {
        cerr << "File Does Not Exist";
    }

    string line, testCasesStr, testInputsStr, testOutputsStr;
    getline(file, line);
    stringstream buffer(line);

    buffer >> testCasesStr;
    buffer >> testInputsStr;
    buffer >> testOutputsStr;

    int testCases = stoi(testCasesStr);

    if (inputNodes != stoi(testInputsStr) && outputNodes != stoi(testOutputsStr)) {
        cerr << "Test File Is Not Compatible With Neural Net";
    }

    for (int e = 0; e < epochs; e++) {
        for (int t = 0; t < testCases; t++) {

            getline(file, line);
            stringstream buffer(line);
            vector<double> inputs = vector<double>(inputNodes);

            for (int i = 0; i < inputNodes; i++) {
                string currentInput;
                buffer << currentInput;
                inputs[i] = stod(currentInput);
            }

            vector<double> outputs = runNeuralNet(inputs);

        }

        vector<double> outputDeltas = vector<double>(outputNodes);

        for (int o = 0; o < outputNodes; o++) {
            // outputDeltas[o] = sigmoidPrime(nodeOutput) * (desiredOutputs[o] - outputs[o]); // TODO
        }

        vector<double> hiddenLayerDeltas = vector<double>(hiddenLayerNodes);

        for (int h = 0; h < hiddenLayerNodes; h++) {
            // hiddenLayerDeltas[h] = // TODO
        }

        // update weights
        // TODO

    }
}