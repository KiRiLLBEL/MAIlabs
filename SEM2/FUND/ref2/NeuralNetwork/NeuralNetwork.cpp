#include "NeuralNetwork.h"
void Neuron::sigmoid() {
    hi = 1 / (1 + exp(-zi));
}
void Neuron::relu() {
    hi = (zi > 0) ? zi : 0;
}
void Neuron::sum() {
    int Count = inputs.size();
    zi = 0;
    for(int i = 0; i != Count; ++i) {
        zi += weight[i]*inputs[i]->hi;
    }
}
NeuronSystem::NeuronSystem(std::vector<int> NeuronCount, double E, double A) : E(E), A(A) {
    int NeuronCounts = NeuronCount.size();
    Lays.resize(NeuronCounts);
    for (int i = 0; i != NeuronCounts; ++i) {
        resizeLays(i, NeuronCount[i]);
    }
    for (int i = 0; i != NeuronCounts - 1; ++i) {
        neuronBias(i);
    }
    std::ifstream fin;
    fin.open("input.txt");
    for (int i = 1; i != NeuronCounts; ++i) {
        inputWeight(i, &fin);
    }
    fin.close();
}
void NeuronSystem::neuronBias(int CurrentLay) {
    int count = Lays[CurrentLay].size();
    Lays[CurrentLay][count - 1].hi = 1;
}
void NeuronSystem::resizeLays(int numberLays, int countNeuron) {
    if (numberLays != Lays.size() - 1) {
        Lays[numberLays].resize(countNeuron + 1);
    }
    else {
        Lays[numberLays].resize(countNeuron);
    }
}
void NeuronSystem::inputWeight (int layNumber, std::ifstream * fin) {
    if (layNumber != Lays.size() - 1) {
        for(int i = 0; i != Lays[layNumber].size() - 1; ++i) {
            Lays[layNumber][i].inputs.resize(Lays[layNumber - 1].size());
            Lays[layNumber][i].weight.resize(Lays[layNumber - 1].size());
            Lays[layNumber][i].changeWeight.resize(Lays[layNumber - 1].size());
            for (int j = 0; j != Lays[layNumber - 1].size(); ++j) {
                Lays[layNumber][i].inputs[j] = &Lays[layNumber - 1][j];
                *fin >> Lays[layNumber][i].weight[j];
            }
        }
    }
    else {
        for(int i = 0; i != Lays[layNumber].size(); ++i) {
            Lays[layNumber][i].inputs.resize(Lays[layNumber - 1].size());
            Lays[layNumber][i].weight.resize(Lays[layNumber - 1].size());
            Lays[layNumber][i].changeWeight.resize(Lays[layNumber - 1].size());
            for (int j = 0; j != Lays[layNumber - 1].size(); ++j) {
                Lays[layNumber][i].inputs[j] = &Lays[layNumber - 1][j];
                *fin >> Lays[layNumber][i].weight[j];
            }
        }
    }
}
void NeuronSystem::forwardfeed(std::string activationFunction) {
    if (activationFunction == "sigmoid") {
        int CountOfLays = Lays.size();
        for (int i = 1; i != CountOfLays - 1; ++i) {
            IterationSigmoid(i);
        }
        IterationEndSigmoid();
    }
    else if (activationFunction == "relu") {
        int CountOfLays = Lays.size();
        for (int i = 1; i != CountOfLays - 1; ++i) {
            IterationRelu(i);
        }
        Softmax();
    }
}
void NeuronSystem::IterationSigmoid(int CurrentLay) {
    int CountNeuron = Lays[CurrentLay].size();
    for (int i = 0; i != CountNeuron - 1; ++i) {
        Lays[CurrentLay][i].sum();
        Lays[CurrentLay][i].sigmoid();
    }
}
void NeuronSystem::IterationRelu(int CurrentLay) {
    int CountNeuron = Lays[CurrentLay].size();
    for (int i = 0; i != CountNeuron - 1; ++i) {
        Lays[CurrentLay][i].sum();
        Lays[CurrentLay][i].relu();
    }
}
void NeuronSystem::IterationEndSigmoid() {
    int LastLayer = Lays.size() - 1;
    int CountNeuron = Lays[LastLayer].size();
    for (int i = 0; i != CountNeuron; ++i) {
        Lays[LastLayer][i].sum();
        Lays[LastLayer][i].sigmoid();
    }
}
void NeuronSystem::Softmax() {
    int LastLayer = Lays.size() - 1;
    int CountNeuron = Lays[LastLayer].size();
    double sumExp = 0;
    double Max = 0;
    for (int i = 0; i != CountNeuron; ++i) {
        Lays[LastLayer][i].sum();
        if (Lays[LastLayer][i].zi > Max) {
            Max = Lays[LastLayer][i].zi;
        }
    }
    for (int i = 0; i != CountNeuron; ++i) {
        Lays[LastLayer][i].hi = exp(Lays[LastLayer][i].zi - Max);
        sumExp += Lays[LastLayer][i].hi;
    }
    for (int i = 0; i != CountNeuron; ++i) {
        Lays[LastLayer][i].hi = Lays[LastLayer][i].hi / sumExp;
    }
}
double NeuronSystem::ErrorQuad(std::vector<double> output) {
    int LastLayer = Lays.size() - 1;
    int CountNeuron = Lays[LastLayer].size();
    double Error = 0;
    for (int i = 0; i != CountNeuron; ++i) {
        Error += pow(Lays[LastLayer][i].hi - output[i], 2);
    }
    return Error;
}
double NeuronSystem::CrossEntropy(std::vector<double> answers) {
    int LastLayer = Lays.size() - 1;
    int CountNeuron = Lays[LastLayer].size();
    double Error = 0;
    for (int i = 0; i != CountNeuron; ++i) {
        Error += answers[i]* log(Lays[LastLayer][i].hi);
    }
    return -Error;
}
void NeuronSystem::backpropagation(std::string activationFunction) {
    if (activationFunction == "sigmoid") {
        int CountOfLay = Lays.size();
        for (int i = CountOfLay - 2; i != 0; --i) {
            deltaSigmoid(i);
        }
        for (int i = CountOfLay - 1; i != 0; --i) {
            ChangeWeight(i);
        }
    }
    else if (activationFunction == "relu") {
        int CountOfLay = Lays.size();
        for (int i = CountOfLay - 2; i != 0; --i) {
            deltaRelu(i);
        }
        for (int i = CountOfLay - 1; i != 0; --i) {
            ChangeWeight(i);
        }
    }
}
void NeuronSystem::deltaEndSigmoid(std::vector<double> output) {
    int LastLayer = Lays.size() - 1;
    int CountNeuron = Lays[LastLayer].size();
    for (int i = 0; i != CountNeuron; ++i) {
        Lays[LastLayer][i].delta = (output[i] - Lays[LastLayer][i].hi)*((1 - Lays[LastLayer][i].hi)*Lays[LastLayer][i].hi);
    }
}
void NeuronSystem::deltaEndRelu(std::vector<double> answers) {
    int LastLayer = Lays.size() - 1;
    int CountNeuron = Lays[LastLayer].size();
    for (int i = 0; i != CountNeuron; ++i) {
        Lays[LastLayer][i].delta = -(Lays[LastLayer][i].hi - answers[i]);
    }
}
void NeuronSystem::deltaSigmoid(int CurrentLay) {
    int CountNeuron = Lays[CurrentLay].size();
    for (int i = 0; i != CountNeuron; ++i) {
        int CountNeuronNext = Lays[CurrentLay + 1].size();
        double sum = 0;
        for (int j = 0; j != CountNeuronNext; ++j) {
            sum += Lays[CurrentLay + 1][j].delta * Lays[CurrentLay + 1][j].weight[i];
        }
        Lays[CurrentLay][i].delta = ((1 - Lays[CurrentLay][i].hi) * Lays[CurrentLay][i].hi) * sum;
    }
}
void NeuronSystem::deltaRelu(int CurrentLay) {
    int CountNeuron = Lays[CurrentLay].size();
    for (int i = 0; i != CountNeuron; ++i) {
        int CountNeuronNext = Lays[CurrentLay + 1].size();
        double sum = 0;
        for (int j = 0; j != CountNeuronNext; ++j) {
            sum += Lays[CurrentLay + 1][j].delta * Lays[CurrentLay + 1][j].weight[i];
        }
        Lays[CurrentLay][i].delta = ((Lays[CurrentLay][i].zi > 0) ? 1 : 0) * sum;
    }
}
void NeuronSystem::ChangeWeight(int CurrentLay) {
    int CountOfLays = Lays.size();
    if (CurrentLay == CountOfLays - 1) {
        int CountOfNeurons = Lays[CurrentLay].size();
        for (int i = 0; i != CountOfNeurons; ++i) {
            int CountOfNeuronsNext = Lays[CurrentLay - 1].size();
            for(int j = 0; j != CountOfNeuronsNext; ++j) {
                Lays[CurrentLay][i].changeWeight[j] = E * Lays[CurrentLay][i].delta * Lays[CurrentLay - 1][j].hi + A * Lays[CurrentLay][i].changeWeight[j];
                Lays[CurrentLay][i].weight[j] += Lays[CurrentLay][i].changeWeight[j];
            }
        }
    }
    else {
        int CountOfNeurons = Lays[CurrentLay].size();
        for (int i = 0; i != CountOfNeurons - 1; ++i) {
            int CountOfNeuronsNext = Lays[CurrentLay - 1].size();
            for(int j = 0; j != CountOfNeuronsNext; ++j) {
                Lays[CurrentLay][i].changeWeight[j] = E * Lays[CurrentLay][i].delta * Lays[CurrentLay - 1][j].hi + A * Lays[CurrentLay][i].changeWeight[j];
                Lays[CurrentLay][i].weight[j] += Lays[CurrentLay][i].changeWeight[j];
            }
        }
    }
}
void NeuronSystem::NeuronSystemStart(std::vector<std::vector<double>> input, std::vector<double> output, std::string activatonFunction) {
    if (activatonFunction == "sigmoid") {
        double ErrorSystem;
        int Epoch = 0;
        while (Epoch != 1000000) {
            double InError = 0;
            int inputSize = input.size();
            int inputSize1 = input[0].size();
            for (int i = 0; i != inputSize; ++i) {
                for (int j = 0; j != inputSize1; ++j) {
                    Lays[0][j].hi = input[i][j];
                }
                forwardfeed("sigmoid");
                InError = ErrorQuad(output);
                deltaEndSigmoid(output);
                backpropagation("sigmoid");

            }
            ErrorSystem = InError / input.size();
            std::cout << "Error: "<< ErrorSystem<<"\n";
            std::cout << "\n";
            ++Epoch;
        }
        std::cout << "Complete" <<"\n";
    }
    else if(activatonFunction == "relu") {
        double ErrorSystem;
        int Epoch = 0;
        while (Epoch != 20) {
            double InError = 0;
            int inputSize = input.size();
            int inputSize1 = input[0].size();
            for (int i = 0; i != inputSize; ++i) {
                for (int j = 0; j != inputSize1; ++j) {
                    Lays[0][j].hi = input[i][j];
                }
                int LastLayer = Lays.size() - 1;
                std::vector<double> answers(Lays[LastLayer].size(), 0);
                for (int j = 0; j != Lays[LastLayer].size(); ++j) {
                    answers[output[i]] = 1;
                }
                double AtError;
                forwardfeed("relu");
                AtError = CrossEntropy(answers);
                deltaEndRelu(answers);
                backpropagation("relu");
                InError += AtError;
            }
            ErrorSystem = InError / input.size();
            std::cout << "-----------Epoch Error: "<< ErrorSystem<<"\n";
            std::cout << "\n";
            ++Epoch;
        }
    }
    else {
        std::cout << "Error - not mode" <<"\n";
    }
}
double NeuronSystem::Is(int i, int j) {
    Lays[0][0].hi = i;
    Lays[0][1].hi = j;
    forwardfeed("sigmoid");
    return Lays[2][0].hi;
}
void NeuronSystem::currentWeight (int currentLay, std::ofstream * fout) {
    for(int i = 0; i != Lays[currentLay].size() - 1; ++i) {
        for (int j = 0; j != Lays[currentLay - 1].size(); ++j) {
            *fout << Lays[currentLay][i].weight[j] <<" ";
        }
    }
}
void NeuronSystem::coutWeight () {
    std::ofstream fout;
    fout.open("input.txt");
    for (int i = 1; i != Lays.size(); ++i) {
        currentWeight(i, &fout);
    }
    fout.close();
}
void NeuronSystem::NeuralSystemAnswer(std::vector<std::vector<double>> input, std::string activatonFunction) {
    if (activatonFunction == "sigmoid") {
        int inputSize = input.size();
        int inputSize1 = input[0].size();
        for (int i = 0; i != inputSize; ++i) {
            for (int j = 0; j != inputSize1; ++j) {
                Lays[0][j].hi = input[i][j];
            }
            forwardfeed("sigmoid");
            std::cout << "Answer = " << Lays[Lays.size() - 1][0].hi << "\n";
        }
    }
    else if(activatonFunction == "relu") {
        int inputSize = input.size();
        int inputSize1 = input[0].size();
        for (int i = 0; i != inputSize; ++i) {
            for (int j = 0; j != inputSize1; ++j) {
                Lays[0][j].hi = input[i][j];
            }
            int LastLayer = Lays.size() - 1;
            forwardfeed("relu");
            int AnswerI = 0;
            double Max = 0;
            for (int j = 0; j != Lays[LastLayer].size(); ++j) {
                if (Lays[LastLayer][j].hi > Max) {
                    Max = Lays[LastLayer][j].hi;
                    AnswerI = j;
                }
            }
            std::cout << "\nAnswer = " << AnswerI << "\n";
        }
    }
    else {
        std::cout << "Error - not mode" <<"\n";
    }
}
