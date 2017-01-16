#ifndef DEF_NETWORK
#define DEF_NETWORK

#include <vector>
#include <fstream>
#include <cmath>
#include <time.h>
#include <stdlib.h>

#include "../Matrix/Matrix.h"

class Network
{
public:
    Network(std::vector<int> neurons, double learningRate);
    Network(const char *filepath);

    Matrix<double> computeOutput(std::vector<double> input);
    void learn(std::vector<double> expectedOutput);

    void saveNetworkParams(const char *filepath);
    void loadNetworkParams(const char *filepath);

private:
    std::vector<Matrix<double> > H;
    std::vector<Matrix<double> > W;
    std::vector<Matrix<double> > B;
    std::vector<Matrix<double> > dEdW;
    std::vector<Matrix<double> > dEdB;

    Matrix<double> Y2;

    int hiddenLayersCount;
    double learningRate;

    static double random(double x);
    static double sigmoid(double x);
    static double sigmoidePrime(double x);

    void printToFile(Matrix<double> &m, std::ofstream &file);
};

#endif
