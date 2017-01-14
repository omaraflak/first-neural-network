#include <iostream>
#include <vector>
#include <assert.h>
#include <png++/png.hpp>

#include "../../Network/Network.h"

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

vector<double> readImage(const char *filename)
{
    int height=32, width=32;

    png::image<png::rgb_pixel> image(filename);
    assert(image.get_width()==width && image.get_height()==height);

    int red,green,blue,p=0;

    vector<double> v(height*width);
    for (int i=0 ; i<height ; i++)
    {
        for (int j=0 ; j<width ; j++)
        {
            red = (int)image[i][j].red;
            green = (int)image[i][j].green;
            blue = (int)image[i][j].blue;
            if(red==255 && green==255 && blue==255) // white pixels are 0 and black pixels are 1 (like the training set)
                v[p++]=0.0;
            else
                v[p++]=1.0;
        }
    }

    return v;
}

int main(int argc, char **argv) {
     vector<double> image = readImage("input.png");

     Network net("../params");
     cout << net.computeOutput(image).applyFunction(stepFunction);
}
