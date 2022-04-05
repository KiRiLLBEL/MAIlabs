#ifndef NEURALNETWORK_NEURALNETWORK_H
#define NEURALNETWORK_NEURALNETWORK_H
#include "iostream"
#include "fstream"
#include "vector"
#include "math.h"
#include "random"
#include "chrono"
#include "bitmap_image.hpp"
class Neuron {
public:
    void sigmoid();
    void relu();
    void sum();
    std::vector<Neuron *> inputs;
    std::vector<double> weight;
    std::vector<double> changeWeight;
    double zi;
    double hi;
    double delta;
};
class NeuronSystem {
public:
    NeuronSystem(std::vector<int> NeuronCount, double E, double A);
    void neuronBias(int CurrentLay);
    void resizeLays(int numberLays, int countNeuron);
    void inputWeight (int layNumber, std::ifstream * fin);
    void forwardfeed(std::string activationFunction);
    void IterationSigmoid(int CurrentLay);
    void IterationRelu(int CurrentLay);
    void IterationEndSigmoid();
    void Softmax();
    double ErrorQuad(std::vector<double> output);
    double CrossEntropy(std::vector<double> answers);
    void backpropagation(std::string activationFunction);
    void deltaEndSigmoid(std::vector<double> output);
    void deltaEndRelu(std::vector<double> answers);
    void deltaSigmoid(int CurrentLay);
    void deltaRelu(int CurrentLay);
    void ChangeWeight(int CurrentLay);
    void NeuronSystemStart(std::vector<std::vector<double>> input, std::vector<double> output, std::string activatonFunction);
    double Is(int i, int j);
    void currentWeight (int currentLay, std::ofstream * fout);
    void coutWeight ();
    void NeuralSystemAnswer(std::vector<std::vector<double>> input, std::string activatonFunction);
    double E;
    double A;
private:
    std::vector<std::vector<Neuron>> Lays;
};

#endif //NEURALNETWORK_NEURALNETWORK_H
