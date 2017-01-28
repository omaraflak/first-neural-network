#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>

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

int main(int argc, char *argv[])
{
    // learning XOR operation
    vector<vector<double> > inputVector = {{0,0}, {0,1}, {1,0}, {1,1}};
    vector<vector<double> > outputVector = {{0}, {1}, {1}, {0}};

    Network net({2, 3, 1}, 1.0);
    // 2 input neurons (i.e. 2 inputs)
    // 3 hidden neurons (experimental) : you can specify as many hidden layers as you want (you need to add the number of neurons in each)
    // 1 output neuron (1 output)
    // 1.0 learning rate (experimental)

    // PLOT
    ofstream X("X");
    ofstream Y("Y");

    // train on 10000 iterations
    for (int i=0 ; i<10000 ; i++)
    {
        for (int j=0 ; j<inputVector.size() ; j++)
        {
            net.computeOutput(inputVector[j]);
            net.learn(outputVector[j]);
        }

        // PLOT
        for (int k=0 ; k<net.W.size() ; k++)
        {
            for (int h=0 ; h<net.W[k].getHeight() ; h++)
            {
                for (int w=0 ; w<net.W[k].getWidth() ; w++)
                {
                    X << i << endl;
                    Y << net.W[k](h,w) << endl;
                }
            }
        }
        // PLOT
    }

    // PLOT
    Y.close();
    X.close();

    // test
    for (int i=0 ; i<inputVector.size() ; i++)
    {
        // as the sigmoid function never reaches 0.0 nor 1.0
        // it can be a good idea to consider values greater than 0.9 as 1.0 and values smaller than 0.1 as 0.0
        // hence the step function.
        cout << net.computeOutput(inputVector[i]).applyFunction(stepFunction) << endl;
    }
}
