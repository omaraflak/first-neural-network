#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

using namespace std;

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
            output[i].resize(10);
            n = atoi(line.substr(0,1).c_str());
            output[i][n] = 1;
        }
    }
    file.close();
}
