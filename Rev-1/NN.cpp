#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class NeuralNet {
    private:
        int inputNodes; // number of input nodes
        int hiddenLayerNodes; // number of nodes in the hidden layer
        int outputNodes; // number of output nodes
        vector<vector<double>*> hiddenLayerToOutputWeights; // hiddenLayerToOutputWeights[input][hidden]
        vector<vector<double>*> inputToHiddenLayerWeights; // inputToHiddenLayerWeights[hidden][output]
        vector<double> hiddenLayerBiases; // hiddenLayerBiases[hidden]
        vector<double> outputBiases; // outputBiases[output]
        // 1 / (1 + e^n)
        inline double sigmoid(double n) {return 1/(1+exp(n));}
    public:
        inline void buildNeuralNet(string inputFileName) {
            fstream file;
            file.open(inputFileName); 
            if (!file.is_open()) {
                cerr << "File Does Not Exist";
            }
            string line, inNodes, hNodes, outNodes;
            getline(file, line);
            stringstream buffer(line);
            buffer >> inNodes;
            buffer >> hNodes;
            buffer >> outNodes;
            inputNodes = stod(inNodes);
            hiddenLayerNodes = stod(hNodes);
            outputNodes = stod(outNodes);

            // TODO

            file.close();
        }
        inline vector<double> runNeuralNet(const vector<double> &inputs) {
            vector<double> outputs;
            return outputs;
        }
};