#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>

#include "../Network/Network.h"

using namespace std;

double stepFunction(double x)
{
    if(x>0.9){
        return 1.0;
    }
    if(x<0.1){
        return 0.0;
    }
    return x;
}

void loadTraining(const char *filename, vector<vector<double> > &input, vector<vector<double> > &output)
{
    int trainingSize = 946;
    input.resize(trainingSize);
    output.resize(trainingSize);

    ifstream file(filename);
    if(file)
    {
        string line;
        int n;

        for (int i=0 ; i<trainingSize ; i++) // load 946 examples
        {
            for (int h=0 ; h<32 ; h++) // 'images' are 32*32 pixels
            {
                getline(file, line);
                for (int w=0 ; w<32 ; w++)
                {
                    input[i].push_back(atoi(line.substr(w,1).c_str()));
                }
            }
            getline(file, line);
            output[i].resize(10); // output is a vector of size 10
            n = atoi(line.substr(0,1).c_str());
            output[i][n] = 1;
        }
    }
    file.close();
}

int main(int argc, char *argv[])
{
    // learning digit recognition
    std::vector<std::vector<double> > inputVector, outputVector;
    loadTraining("training", inputVector, outputVector); // load data from file called "training"

    // 32*32=1024 input neurons (images are 32*32 pixels)
    // 15 hidden neurons (experimental) : you can specify as many hidden layers as you want (you need to add the number of neurons in each)
    // 10 output neurons (for each image output is a vector of size 10, full of zeros and a 1 at the index of the number represented)
    // 0.7 learning rate (experimental)
    Network net({1024, 15, 10}, 0.7);

    // train on 30 iterations
    cout << "Training..." << endl;
    for (int i=0 ; i<30 ; i++)
    {
        for (int j=0 ; j<inputVector.size()-10 ; j++) // skip the 10 last examples to test the program at the end
        {
            net.computeOutput(inputVector[j]);
            net.learn(outputVector[j]);
        }
        cout << "#" << i+1 << "/30" << endl;
    }

    // test
    cout << endl << "Testing..." << endl;
    cout << "expected output : actual output" << endl << endl;
    for (int i=inputVector.size()-10 ; i<inputVector.size() ; i++) // testing on last 10 examples
    {
        for (int j=0 ; j<10 ; j++)
        {
            cout << outputVector[i][j] << " ";
        }
        cout << ": " << net.computeOutput(inputVector[i]).applyFunction(stepFunction) << endl;
        // as the sigmoid function never reaches 0.0 nor 1.0
        // it can be a good idea to consider values greater than 0.9 as 1.0 and values smaller than 0.1 as 0.0
        // hence the step function.
    }

    cout << endl << "Saving parameters...";
    net.saveNetworkParams("params");
    cout << "ok!" << endl;

    // net.loadNetworkParams("params"); or Network net("params");
}
