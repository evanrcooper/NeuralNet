#include <iostream>
#include "NN.h"

using namespace std;

bool isValidSelection(const string &selection);

int main() {
    
    NeuralNet net = NeuralNet();

    // char c;
    // string selection;

    // do {
    //     cout << "Choose 1-5: ";
    //     cin >> selection;
    //     while (!isValidSelection(selection)) {
    //         cout << "Invalid, Choose 1-5: ";
    //         cin >> selection;
    //     }
    //     c = selection[0];
    //     switch (c) {

    //         case '1':
    //             // Build Neural Net
    //             break;

    //         case '2':
    //             // Save Neural Net
    //             break;

    //         case '3':
    //             // Train Neural Net
    //             break;

    //         case '4':
    //             // Test Neural Net
    //             break;

    //         case '5':
    //             // Quit
    //             break;

    //         default:
    //             cerr << "Invalid Choice";
    //     }

    // } while (c != '5');

    net.buildNeuralNet("testUntrained.txt");
    net.trainNeuralNet("trainingSet.txt", 100, 0.1);
    net.saveNeuralNet("testOut.txt");

    // net.printMetrics("", "");

    return 0;
}

bool isValidSelection(const string &selection) {

    constexpr char NUMBER_OF_SELECTIONS = 5;

    if (selection.length() < 1) {
        return false;
    }

    if ((selection[0]-'0') < 1) {
        return false;
    }

    if ((selection[0]-'0') > NUMBER_OF_SELECTIONS) {
        return false;
    }

    return true;
}