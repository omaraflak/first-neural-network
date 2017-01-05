# Neural Network in C++
A neural network implemented with **matrices** in C++, without any third party library !

# Download project
    git clone https://github.com/omaflak/Neural-Network
    cd Neural-Network
    git clone https://github.com/omaflak/Matrix
    
# Compile & Run
    g++ main.cpp Matrix.h -o main -std=c++11
    ./main
    
# Now you see me
**withPlot.cpp** version is exactly the same as the **main.cpp** one but it prints the weights/error variations in files to plot them later.

Compile and run:

    g++ withPlot.cpp Matrix.h -o main -std=c++11 && ./main
    
Once the program has finished, 4 files should be created in the current directory: plotX, plotY, plotEX, plotEY

+ **plotX/Y :** xy coordinates for weights variation

+ **plotEX/EY :** xy coordinates for error variation

You can plot the data with **[plotly](https://plot.ly/create/)** by pressing the **import** button (top right).

Here is some plot :

![alt tag](https://github.com/omaflak/Neural-Network/blob/master/images/weightsPlot.png?raw=true)
![alt tag](https://github.com/omaflak/Neural-Network/blob/master/images/errorPlot.png?raw=true)
