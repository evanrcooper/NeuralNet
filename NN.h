#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

struct confusionMatrix {
    confusionMatrix(int A = 0, int B = 0, int C = 0, int D = 0) {
        this->A = A;
        this->B = B;
        this->C = C;
        this->D = D;
    }
    int A, B, C, D;
};

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

        // builds the neural net from an input file
        void buildNeuralNet(string inputFileName);

        // saves the weights and biases to a file
        void saveNeuralNet(string outputFileName) const;

        // runs the neural net on a single input case and stores the outputs of each node in the hidden layer
        vector<double> runNeuralNet(const vector<double> &inputs, vector<double> *hiddenLayerOutputs = nullptr) const;

        // trains the neural net on the given test set for specified epochs
        void trainNeuralNet(const string &trainingSetFile, const unsigned long int &epochs, const double &learningRate);

        // produces a contigency table for the given test set
        [[nodiscard]] vector<confusionMatrix> makeContingencyTable(const string &testSetFileName) const;

        // saves the accuracy, precision, recall, and etc. for each output of the NeuralNet to the given file
        void printMetrics(const string &testSetFileName, const string &outputFileName) const;
        
    private:

        int inputNodes = 0; // number of input nodes
        int hiddenLayerNodes = 0; // number of nodes in the hidden layer
        int outputNodes = 0; // number of output nodes
        
        vector<vector<double>*> inputToHiddenLayerWeights; // (*inputToHiddenLayerWeights[hidden])[input]
        vector<vector<double>*> hiddenLayerToOutputWeights; // (*hiddenLayerToOutputWeights[output])[hidden]
        vector<double> hiddenLayerBiases; // hiddenLayerBiases[hidden]
        vector<double> outputBiases; // outputBiases[output]

        // trains neural net for a single epoch on the entire test set
        void singleEpoch(const string &trainingSetFile, const double &learningRate);

        // 1 / (1 + e^-d)
        [[nodiscard]] inline constexpr double sigmoid(const double &d) const {return 1.0/(1.0+exp(-d));}

        // nodeOutput * (1 - nodeOutput)
        [[nodiscard]] inline constexpr double sigmoidPrime(const double &nodeOutput) const {return nodeOutput*(1.0-nodeOutput);}

        // helper function for printing doubles up to given decimal places
        [[nodiscard]] string doubleToString(const double &d, const int &decimals = 3) const;
};