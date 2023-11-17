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