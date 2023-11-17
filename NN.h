#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class NeuralNet {
    public:
        inline NeuralNet() {
            inputToHiddenLayerWeights = vector<vector<double>*>();
            hiddenLayerToOutputWeights = vector<vector<double>*>();
            hiddenLayerBiases = vector<double>();
            outputBiases = vector<double>();
        }
        inline void buildNeuralNet(string inputFileName) {
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
        inline vector<double> runNeuralNet(const vector<double> &inputs) {
            vector<double> outputs;
            return outputs;
        }
    private:
        int inputNodes = 0; // number of input nodes
        int hiddenLayerNodes = 0; // number of nodes in the hidden layer
        int outputNodes = 0; // number of output nodes
        vector<vector<double>*> inputToHiddenLayerWeights; // inputToHiddenLayerWeights[hidden][output]
        vector<vector<double>*> hiddenLayerToOutputWeights; // hiddenLayerToOutputWeights[input][hidden]
        vector<double> hiddenLayerBiases; // hiddenLayerBiases[hidden]
        vector<double> outputBiases; // outputBiases[output]
        // 1 / (1 + e^n)
        inline double sigmoid(double n) {return 1/(1+exp(n));}
};