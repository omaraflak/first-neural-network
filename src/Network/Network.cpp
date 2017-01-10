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

Network::Network(const char *filepath)
{
    loadNetworkParams(filepath);
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

void Network::saveNetworkParams(const char *filepath)
{
    std::ofstream out(filepath);
    Matrix<double> params[] = {W1,W2,T1,T2};
    int h,w;

    out << learningRate << std::endl;
    for (Matrix<double> m : params){
        h = m.getHeight();
        w = m.getWidth();

        out << h << std::endl;
        out << w << std::endl;
        for (int i=0 ; i<h ; i++)
        {
            for (int j=0 ; j<w ; j++)
            {
                out << m.get(i,j) << (j!=w-1?" ":"");
            }
            out << std::endl;
        }
    }
    out.close();
}

void Network::loadNetworkParams(const char *filepath)
{
    std::ifstream in(filepath);
    std::vector<Matrix<double> > params(4);
    double val;
    int h,w;

    if(in)
    {
        in >> learningRate;
        for(int i=0 ; i<params.size() ; i++)
        {
            in >> h;
            in >> w;
            Matrix<double> m(h,w);
            for (int hh=0 ; hh<h ; hh++)
            {
                for (int ww=0 ; ww<w ; ww++)
                {
                    in >> val;
                    m.put(hh,ww,val);
                }
            }

            params[i] = m;
        }
    }
    in.close();

    // assign values
    W1 = params[0];
    W2 = params[1];
    T1 = params[2];
    T2 = params[3];
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
