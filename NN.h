#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class NeuralNet {
    public:
        NeuralNet() {
            inputToHiddenLayerWeights = vector<vector<double>*>();
            hiddenLayerToOutputWeights = vector<vector<double>*>();
            hiddenLayerBiases = vector<double>();
            outputBiases = vector<double>();
        }
        ~NeuralNet() {
            for (int h = 0; h < hiddenLayerNodes; h++) {
                delete inputToHiddenLayerWeights[h];
            }
            for (int o = 0; o < outputNodes; o++) {
                delete hiddenLayerToOutputWeights[o];
            }
        }
        void buildNeuralNet(string inputFileName);
        vector<double> runNeuralNet(const vector<double> &inputs);
    private:
        int inputNodes = 0; // number of input nodes
        int hiddenLayerNodes = 0; // number of nodes in the hidden layer
        int outputNodes = 0; // number of output nodes
        vector<vector<double>*> inputToHiddenLayerWeights; // inputToHiddenLayerWeights[hidden][input]
        vector<vector<double>*> hiddenLayerToOutputWeights; // hiddenLayerToOutputWeights[output][hidden]
        vector<double> hiddenLayerBiases; // hiddenLayerBiases[hidden]
        vector<double> outputBiases; // outputBiases[output]
        // 1 / (1 + e^n)
        inline double sigmoid(double n) {return 1/(1+exp(n));}
};