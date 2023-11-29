#include <iostream>
#include "NN.h"

using namespace std;

int main() {
    NeuralNet net = NeuralNet();
    net.buildNeuralNet("testTrained.txt");
    net.saveNeuralNet("testOut.txt");
    return 0;
}