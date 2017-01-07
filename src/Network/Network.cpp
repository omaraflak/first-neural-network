#include "Network.h"

Network::Network(int inputNeuron, int hiddenNeuron, int outputNeuron, double learningRate)
{
    srand (time(NULL));
    
    this->learningRate = learningRate;

    W1 = Matrix<double>(inputNeuron, hiddenNeuron);
    W2 = Matrix<double>(hiddenNeuron, outputNeuron);
    T1 = Matrix<double>(1, hiddenNeuron);
    T2 = Matrix<double>(1, outputNeuron);

    W1 = W1.applyFunction(random);
    W2 = W2.applyFunction(random);
    T1 = T1.applyFunction(random);
    T2 = T2.applyFunction(random);
}

Matrix<double> Network::computeOutput(std::vector<double> input)
{
    std::vector<std::vector<double> > in = {input}; // row matrix
    X = Matrix<double>(in);
    H = X.dot(W1).add(T1).applyFunction(sigmoid);
    Y = H.dot(W2).add(T2).applyFunction(sigmoid);
    return Y;
}

void Network::learn(std::vector<double> expectedOutput)
{
    std::vector<std::vector<double> > out = {expectedOutput}; // row matrix
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

double Network::random(double x)
{
    return (double)(rand() % 10000 + 1)/10000-0.5;
}

double Network::sigmoid(double x)
{
    return 1/(1+exp(-x));
}

double Network::sigmoidePrime(double x)
{
    return exp(-x)/(pow(1+exp(-x), 2));
}
