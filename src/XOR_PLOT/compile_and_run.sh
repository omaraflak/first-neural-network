#! bin/sh

g++ main.cpp ../Network/Network.h ../Network/Network.cpp -o main -std=c++11
./main
python ../plotXY.py X Y
