# Neural Network in C++
A neural network implemented with **matrices** in C++, from scratch !

This program is meant to be used for supervised learning.

# What's in there ?

+ **src/XOR :** Learning XOR operation.
+ **src/Digits-Recognition :** Learning to recognize hand-written digits with a training file.

# Download, Compile & Run
    git clone https://github.com/omaflak/Neural-Network
    cd Neural-Network/src
    git clone https://github.com/omaflak/Matrix

    # cd into one of the directories above and:
    sh compile.sh
    ./main

# Network Class
The Network class contains the gradient descent algorithm.

Both **src/XOR** and **src/Digit-Recognition** are using it. Quick description :

    // constructor
    // vector 'neurons' should contain:
    // - number of input neurons at first index
    // - number of output neurons at last index
    // - number of hidden neurons in between
    // example: {2,5,3,1} = 2 input neurons, 1 output neuron, 2 hidden layers (5 neurons and 3 neurons respectively)
    // learning rate : experimental
    Network(std::vector<int> neurons, double learningRate);

    // make prediction
    Matrix<double> computeOutput(std::vector<double> input);

    // learns from the previous computeOutput()
    void learn(std::vector<double> expectedOutput);

    // save all network's parameters into a file (after a training)
    void saveNetworkParams(const char *filepath);

    // load network's parameters from a file so you don't have to train it again
    void loadNetworkParams(const char *filepath);
    // or use the constructor
    Network(const char *filepath);



# Plot

I was curious to see what would've happened if I had plotted the network's parameters on a graph, so I did it, and the result is actually fun :)

The program was learning XOR operation and saving it's weights and error variation over time.

Then I plotted the data with **[plotly](https://plot.ly/create/)**

And here is the result :

![alt tag](https://github.com/omaflak/Neural-Network/blob/master/images/weightsPlot.png?raw=true)
![alt tag](https://github.com/omaflak/Neural-Network/blob/master/images/errorPlot.png?raw=true)

We can see that the program is actually working: while the weights are converging to specific values, the error is decreasing.

Amen !
