#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>

#include "Matrix.h"

using namespace std;

// params
Matrix<double> X, W1, H, W2, Y, Y2, E1, E2, dEdW1, dEdW2, T1, T2;
double learningRate;

double random(double x)
{
    return (double)(rand() % 10000 + 1)/10000-0.5;
}

double sigmoid(double x)
{
    return 1/(1+exp(-x));
}

double sigmoidePrime(double x)
{
    return exp(-x)/(pow(1+exp(-x), 2));
}

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

double pow(double x)
{
    return x*x;
}

double sum(Matrix<double> M)
{
    double s=0.0;
    for (int h=0 ; h<M.getHeight() ; h++)
    {
        for (int w=0 ; w<M.getWidth() ; w++)
        {
            s+=M.get(h,w);
        }
    }
    return s;
}


void init(int inputNeuron, int hiddenNeuron, int outputNeuron, double rate)
{
    learningRate = rate;

    W1 = Matrix<double>(inputNeuron, hiddenNeuron);
    W2 = Matrix<double>(hiddenNeuron, outputNeuron);
    T1 = Matrix<double>(1, hiddenNeuron);
    T2 = Matrix<double>(1, outputNeuron);

    W1 = W1.applyFunction(random);
    W2 = W2.applyFunction(random);
    T1 = T1.applyFunction(random);
    T2 = T2.applyFunction(random);
}

Matrix<double> computeOutput(vector<double> input)
{
    vector<vector<double> > in = {input}; // row matrix
    X = Matrix<double>(in);
    H = X.dot(W1).add(T1).applyFunction(sigmoid);
    Y = H.dot(W2).add(T2).applyFunction(sigmoid);
    return Y;
}

void learn(vector<double> expectedOutput)
{
    vector<vector<double> > out = {expectedOutput}; // row matrix
    Y2 = Matrix<double>(out);

    // Error E = 1/2 (expectedOutput - computedOutput)^2
    // Then, we need to calculate the partial derivative of E with respect to W1,W2,T1,T2

    // compute gradients
    E2 = Y.subtract(Y2).multiply(H.dot(W2).add(T2).applyFunction(sigmoidePrime));
    E1 = E2.dot(W2.transpose()).multiply(X.dot(W1).add(T1).applyFunction(sigmoidePrime));
    dEdW2 = H.transpose().dot(E2);
    dEdW1 = X.transpose().dot(E1);

    // update weights
    W1 = W1.subtract(dEdW1.multiply(learningRate));
    W2 = W2.subtract(dEdW2.multiply(learningRate));
    T1 = T1.subtract(E1.multiply(learningRate)); // (dEdT1 = E1)
    T2 = T2.subtract(E2.multiply(learningRate)); // (dEdT2 = E2)
}

int main(int argc, char *argv[])
{
    srand (time(NULL)); // to generate random weights

    // learning XOR operation
    vector<vector<double> > inputVector = {{0,0}, {0,1}, {1,0}, {1,1}};
    vector<vector<double> > outputVector = {{0}, {1}, {1}, {0}};

    init(2, 3, 1, 0.7); // 2 input neurons (i.e. 2 inputs), 3 hidden neurons (experimental), 1 output neuron (1 output), 0.7 learning rate (experimental)

    ofstream plotX("plotX");
    ofstream plotY("plotY");
    ofstream plotEX("plotEX");
    ofstream plotEY("plotEY");

    plotX << "X" << endl;
    plotY << "Y" << endl;
    plotEX << "EX" << endl;
    plotEY << "EY" << endl;

    // train on 10000 iterations
    for (int i=0 ; i<10000 ; i++)
    {
        for (int j=0 ; j<inputVector.size() ; j++)
        {
            computeOutput(inputVector[j]);
            learn(outputVector[j]);

            for (int h=0 ; h<W1.getHeight() ; h++)
            {
                for (int w=0 ; w<W1.getWidth() ; w++)
                {
                    plotX << i << endl;
                    plotY << W1.get(h,w) << endl;
                }
            }
        }
        plotEX << i << endl;
        plotEY << sum(Y2.subtract(Y).applyFunction(pow)) << endl;
    }

    plotEY.close();
    plotEX.close();
    plotY.close();
    plotX.close();

    // test
    for (int i=0 ; i<inputVector.size() ; i++)
    {
        // as the sigmoid function never reaches 0.0 nor 1.0
        // it can be a good idea to consider values greater than 0.9 as 1.0 and values smaller than 0.1 as 0.0
        // hence the step function.
        cout << computeOutput(inputVector[i]).applyFunction(stepFunction) << endl;
    }
}
