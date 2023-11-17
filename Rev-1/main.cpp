#include <iostream>
#include "NN.h"

using namespace std;

int main() {
    NeuralNet net = NeuralNet();
    net.buildNeuralNet("testUntrained.txt");
    return 0;
}