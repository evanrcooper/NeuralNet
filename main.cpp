#include <iostream>
#include "NN.h"

using namespace std;

int test(NeuralNet &net);

int main() {
    NeuralNet net = NeuralNet();
    net.buildNeuralNet("testUntrained.txt");
    // int before = test(net);
    // net.trainNeuralNet("trainingSet.txt", 100, 0.1);
    // int after = test(net);
    // cout << "\nBefore: " << before << ", After: " << after << "\n";
    // net.saveNeuralNet("testOut.txt");

    net.printMetrics("", "");

    return 0;
}