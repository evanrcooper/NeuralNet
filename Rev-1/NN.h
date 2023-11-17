#include <cmath>
#include <vector>
#include <iostream>

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
            
        }
};