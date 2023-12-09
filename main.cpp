#include <iostream>
#include "NN.h"

using namespace std;

// helper functions to determine and get valid user inputs
bool isValidSelection(const string &selection);
int getEpochs();
double getLearningRate();

int main() {

    const string OFFSET = "  ";

    NeuralNet net = NeuralNet();

    char c;
    string selection, inputFileName, outputFileName;

    do {

        cout << "\n" << "Options:\n";
        cout << OFFSET << "1. Build Neural Net From File\n";
        cout << OFFSET << "2. Save Neural Net To A File\n";
        cout << OFFSET << "3. Train Neural Net From A File\n";
        cout << OFFSET << "4. Test And Save Results Of Neural Net\n";
        cout << OFFSET << "5. Quit\n";
        cout << "Choice: ";

        cin >> selection;
        while (!isValidSelection(selection)) {
            cout << "Invalid, Choose 1-5: ";
            cin >> selection;
        }
        c = selection[0];

        switch (c) {

            // Build Neural Net
            case '1':
                cout << "\n" << "File To Build Neural Net From: ";
                cin >> inputFileName;
                net.buildNeuralNet(inputFileName);
                break;

            // Save Neural Net
            case '2':
                cout << "\n" << "File To Save Neural Net To: ";
                cin >> outputFileName;
                net.saveNeuralNet(outputFileName);
                break;

            // Train Neural Net
            case '3':
                cout << "\n" << "File To Train Neural Net From: ";
                cin >> inputFileName;
                net.trainNeuralNet(inputFileName, getEpochs(), getLearningRate());
                break;

            // Test Neural Net
            case '4':
                cout << "\n" << "File To Test Neural Net From: ";
                cin >> inputFileName;
                cout << "File To Save Results To: ";
                cin >> outputFileName;
                net.printMetrics(inputFileName, outputFileName);
                break;

            // Quit
            case '5':
                cout << "\n" << "Quitting..." << "\n\n";
                break;

            default:
                cerr << "Invalid Choice...\n";
        }

    } while (c != '5');

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

int getEpochs() {

    string input;
    int i;

    do {

        cout << "Number Of Epochs: ";
        cin >> input;

        try {

            i = stoi(input);

        } catch (std::invalid_argument) {

            cout << "Invalid Argument.\n";
            i = 0;

        }

    } while (i <= 0);

    return i;
}

double getLearningRate() {

    string input;
    double d;

    do {

        cout << "Learning Rate: ";
        cin >> input;

        try {

            d = stod(input);

        } catch (std::invalid_argument) {

            cout << "Invalid Argument.\n";
            d = 0;

        }

    } while (d <= 0);

    return d;
}