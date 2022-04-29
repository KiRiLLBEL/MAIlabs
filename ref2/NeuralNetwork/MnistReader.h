#ifndef NEURALNETWORK_MNISTREADER_H
#define NEURALNETWORK_MNISTREADER_H
#include "iostream"
#include "fstream"
#include "vector"
#include "math.h"
#include "random"
#include "chrono"
#include "bitmap_image.hpp"
#include "NeuralNetwork.h"
#include "MnistReader.h"
unsigned char** read_mnist_images(std::string full_path, int& number_of_images, int& image_size);
unsigned char* read_mnist_labels(std::string full_path, int& number_of_labels);
#endif //NEURALNETWORK_MNISTREADER_H
