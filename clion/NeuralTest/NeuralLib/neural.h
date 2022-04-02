#ifndef NEURAL_H
#define NEURAL_H
#include "iostream"
#include "vector"
#include "math.h"
#include "fstream"
#include "random"
#include "ctime"
class Neuron {
public:
    double sigmoid();
    double relu();
    double SumEnd();
    double reluDev();
    std::vector<Neuron *> inputs;
    std::vector<double> weight;
    std::vector<double> changeWeight;
    double output;
    double error;
private:
    double SumRelu();
    double Sum();
};
class NeuronSystem {
public:
    NeuronSystem(std::vector<int> NeuronCount, double E, double A);
    void softmax();
    void resizeLays(int numberLays, int countNeuron);
    void neuronShift(int layNumber);
    void startNS(std::vector<std::vector<double>> & input, std::vector<double> & output, int EpochEnd);
    void startNSRelu(std::vector<std::vector<double>> & input, std::vector<double> & output, int EpochEnd);
    void inputWeight (int layNumber, std::ifstream * fin);
    void currentWeight (int currentLay, std::ofstream * fout);
    void coutWeight ();
    double sigma0(double output, double answer);
    void sigmaRelu(int CurrentLay);
    void ChangeWeight0Relu();
    void sigma(int CurrentLay);
    void ChangeWeight(int Lay);
    void ChangeWeightRelu(int Lay);
    double Is(int i, int j);
    double E;
    double A;
private:
    std::vector<std::vector<Neuron>> Lays;
};
#endif