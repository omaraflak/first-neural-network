#! /bin/sh

g++ main.cpp -o main ../../Network/Network.h ../../Network/Network.cpp `libpng-config --cflags --ldflags --libs` -std=c++11
