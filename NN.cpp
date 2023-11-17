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

inline vector<double> NeuralNet::runNeuralNet(const vector<double> &inputs) {
    // calculate the values of the hidden layer nodes
    vector<double> hiddenLayerValues = vector<double>();
    for (int h = 0; h < hiddenLayerNodes; h++) {
        double hiddenNodeValue = 0;
        for (int i = 0; i < inputNodes; i++) {
            hiddenNodeValue += inputs[i] * (*inputToHiddenLayerWeights[h])[i];
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