#include "neural.h"
double Neuron::sigmoid() {
    if (inputs[0] == NULL) {
        return output;
    }
    return 1/(1 + exp(-Sum()));
}
double Neuron::relu() {
    if (inputs[0] == NULL) {
        return output;
    }
    double s = SumRelu();
    if(s < 0) {
        return 0;
    }
    else {
        return s;
    }
}
double Neuron::reluDev() {
    if (inputs[0] == NULL) {
        return output;
    }
    if(output < 0) {
        return 0;
    }
    else {
        return 1;
    }
}
double Neuron::Sum() {
    if (inputs[0] == NULL) {
        return output;
    }
    output = 0;
    for (int i = 0; i != inputs.size(); ++i) {
        output += inputs[i]->sigmoid() * weight[i];
    }
    return output;
}
double Neuron::SumEnd() {
    double sum = 0;
    for(int i = 0; i != inputs.size(); ++i) {
        sum += inputs[i]->relu() * weight[i];
    }
    return sum;
}
double Neuron::SumRelu() {
    if (inputs[0] == NULL) {
        return output;
    }
    output = 0;
    for (int i = 0; i != inputs.size(); ++i) {
        output += inputs[i]->relu() * weight[i];
    }
    return output;
}
NeuronSystem::NeuronSystem(std::vector<int> NeuronCount, double E, double A) : E(E), A(A) {
    Lays.resize(NeuronCount.size());
    for (int i = 0; i != NeuronCount.size(); ++i) {
        resizeLays(i, NeuronCount[i]);
    }
    for (int i = 0; i != NeuronCount.size() - 1; ++i) {
        neuronShift(i);
    }
    std::ifstream fin;
    fin.open("input.txt");
    for (int i = 1; i != NeuronCount.size(); ++i) {
        inputWeight(i, &fin);
    }
    fin.close();
}
void NeuronSystem::resizeLays(int numberLays, int countNeuron) {
    if (numberLays != Lays.size() - 1) {
        Lays[numberLays].resize(countNeuron + 1);
    }
    else {
        Lays[numberLays].resize(countNeuron);
    }
}
void NeuronSystem::neuronShift(int layNumber) {
    for (int i = 0; i != Lays[layNumber].size(); ++i) {
        Lays[layNumber][i].inputs.resize(1);
        Lays[layNumber][i].output = 1;
        Lays[layNumber][i].inputs[0] = NULL;
    }
}
void NeuronSystem::startNS(std::vector<std::vector<double>> & input, std::vector<double> & output, int EpochEnd) {
    double ErrorSystem = 1;
    int Epoch = 0;
    std::ofstream fout;
        fout.open("log.txt");
    while (Epoch != EpochEnd) {
        double InError = 0;
//            fout << "Epoch: " << Epoch <<'\n';
        for (int i = 0; i != input.size(); ++i) {
            for (int j = 0; j != input[0].size(); ++j) {
                Lays[0][j].output = input[i][j];
            }
            double answer = Lays[Lays.size() - 1][output[i]].sigmoid();
            InError += pow(output[i] - answer, 2);
            std::cout << i + 1 << " answer " << answer << " "<< output[i] <<"\n";
            Lays[Lays.size() - 1][output[i]].error = sigma0(answer, output[i]);
            for (int j = Lays.size() - 2; j != 0; --j) {
                sigma(j);
            }
            for (int j = Lays.size() - 1; j != 0; --j) {
                ChangeWeight(j);
            }
//                fout << "weights: \n" << Lays[1][0].weight[0] << "\n" <<
//                Lays[1][0].weight[1] << "\n" <<
//                Lays[1][1].weight[0] << "\n" <<
//                Lays[1][1].weight[1] << "\n" <<
//                Lays[2][0].weight[0] << "\n" <<
//                Lays[2][0].weight[1] << "\n";
        }
        ErrorSystem = InError / input.size();
        std::cout << "Error: "<< ErrorSystem<<"\n";
        std::cout << "\n";
        ++Epoch;
    }
    std::cout << "ErrorSystem = " << ErrorSystem << "\n";
    std::cout << "Complete" <<"\n";
        fout.close();
}
void NeuronSystem::startNSRelu(std::vector<std::vector<double>> & input, std::vector<double> & output, int EpochEnd) {
    double ErrorSystem = 1;
    int Epoch = 0;
    std::ofstream fout;
    fout.open("log.txt");
    while (Epoch != EpochEnd) {
        double InError = 0;
//            fout << "Epoch: " << Epoch <<'\n';
        for (int i = 0; i != input.size(); ++i) {
            double LError = 0;
            for (int j = 0; j != input[0].size(); ++j) {
                Lays[0][j].output = input[i][j];
            }
            for (int j = 0; j != Lays[Lays.size() - 2].size(); ++j) {
                Lays[Lays.size() - 2][j].relu();
            }
            softmax();
            for (int j = 0; j != Lays[Lays.size() - 1].size(); ++j) {
                if (j == output[i])
                {
                    Lays[Lays.size() - 1][j].error = Lays[Lays.size() - 1][j].output - 1;
                    LError += -log(Lays[Lays.size() - 1][j].output);
                }
                else {
                    Lays[Lays.size() - 1][j].error = Lays[Lays.size() - 1][j].output - 0;
                }
            }
            ChangeWeight0Relu();
            std::cout << i + 1 << " answer " << Lays[Lays.size() - 1][output[i]].output << " "<< output[i] <<" Error: "<< LError <<"\n";

            for (int j = Lays.size() - 2; j != 0; --j) {
                sigmaRelu(j);
            }
            for (int j = Lays.size() - 2; j != 0; --j) {
                ChangeWeightRelu(j);
            }
            InError += LError;
//                fout << "weights: \n" << Lays[1][0].weight[0] << "\n" <<
//                Lays[1][0].weight[1] << "\n" <<
//                Lays[1][1].weight[0] << "\n" <<
//                Lays[1][1].weight[1] << "\n" <<
//                Lays[2][0].weight[0] << "\n" <<
//                Lays[2][0].weight[1] << "\n";
        }
        ErrorSystem = InError / input.size();
        std::cout << "Error: "<< ErrorSystem<<"\n";
        std::cout << "\n";
        ++Epoch;
    }
    std::cout << "ErrorSystem = " << ErrorSystem << "\n";
    std::cout << "Complete" <<"\n";
    fout.close();
}
void NeuronSystem::softmax() {
    double omax = 0;
    for (int i = 0; i != Lays[Lays.size() - 1].size(); ++i) {
        Lays[Lays.size() - 1][i].output = Lays[Lays.size() - 1][i].SumEnd();
        if (Lays[Lays.size() - 1][i].output > omax) {
            omax = Lays[Lays.size() - 1][i].output;
        }
    }
    for (int i = 0; i != Lays[Lays.size() - 1].size(); ++i) {
        Lays[Lays.size() - 1][i].output = exp(Lays[Lays.size() - 1][i].output - omax);
    }
    double sum = 0;
    for (int i = 0; i != Lays[Lays.size() - 1].size(); ++i) {
        sum += Lays[Lays.size() - 1][i].output;
    }
    for (int i = 0; i != Lays[Lays.size() - 1].size(); ++i) {
        Lays[Lays.size() - 1][i].output = Lays[Lays.size() - 1][i].output/sum;
    }
}
void NeuronSystem::ChangeWeight0Relu() {
    for (int i = 0; i != Lays[Lays.size() - 1].size(); ++i) {
        for(int j = 0; j != Lays[Lays.size() - 1][0].inputs.size(); ++j) {
            Lays[Lays.size() - 1][i].changeWeight[j] = E * Lays[Lays.size() - 1][i].error * Lays[Lays.size() - 2][j].output + A * Lays[Lays.size() - 1][i].changeWeight[j];
            Lays[Lays.size() - 1][i].weight[j] += Lays[Lays.size() - 1][i].changeWeight[j];
        }
    }
}
void NeuronSystem::sigmaRelu(int CurrentLay) {
    for(int i = 0; i != Lays[CurrentLay].size() - 1; ++i) {
        double sum = 0;
        for (int j = 0; j != Lays[CurrentLay + 1].size() - 1; ++j) {
            sum += Lays[CurrentLay + 1][j].weight[i] * Lays[CurrentLay + 1][j].error;
        }
        Lays[CurrentLay][i].error =  Lays[CurrentLay][i].reluDev()*sum;
    }
};
void NeuronSystem::ChangeWeightRelu(int Lay) {
    if (Lay == Lays.size() - 1) {
        for (int i = 0; i != Lays[Lay].size(); ++i) {
            for(int j = 0; j != Lays[Lay - 1].size(); ++j) {
                Lays[Lay][i].changeWeight[j] = E * Lays[Lay][i].error * Lays[Lay - 1][j].relu() + A * Lays[Lay][i].changeWeight[j];
                Lays[Lay][i].weight[j] += Lays[Lay][i].changeWeight[j];
            }
        }
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
double NeuronSystem::sigma0(double output, double answer){
    return (answer - output)*((1 - output) * output);
}
void NeuronSystem::sigma(int CurrentLay) {
    if (CurrentLay != Lays.size() - 2) {
        for(int i = 0; i != Lays[CurrentLay].size() - 1; ++i) {
            double sum = 0;
            for (int j = 0; j != Lays[CurrentLay + 1].size() - 1; ++j) {
                sum += Lays[CurrentLay + 1][j].weight[i] * Lays[CurrentLay + 1][j].error;
            }
            Lays[CurrentLay][i].error = ((1 - Lays[CurrentLay][i].sigmoid())*Lays[CurrentLay][i].sigmoid())*sum;
        }
    }
    else {
        for(int i = 0; i != Lays[CurrentLay].size() - 1; ++i) {
            double sum = 0;
            for (int j = 0; j != Lays[CurrentLay + 1].size(); ++j) {
                sum += Lays[CurrentLay + 1][j].weight[i] * Lays[CurrentLay + 1][j].error;
            }
            Lays[CurrentLay][i].error = ((1 - Lays[CurrentLay][i].sigmoid())*Lays[CurrentLay][i].sigmoid())*sum;
        }
    }
}
void NeuronSystem::ChangeWeight(int Lay) {
    if (Lay == Lays.size() - 1) {
        for (int i = 0; i != Lays[Lay].size(); ++i) {
            for(int j = 0; j != Lays[Lay - 1].size(); ++j) {
                Lays[Lay][i].changeWeight[j] = E * Lays[Lay][i].error * Lays[Lay - 1][j].sigmoid() + A * Lays[Lay][i].changeWeight[j];
                Lays[Lay][i].weight[j] += Lays[Lay][i].changeWeight[j];
            }
        }
    }
    else {
        for (int i = 0; i != Lays[Lay].size() - 1; ++i) {
            for(int j = 0; j != Lays[Lay - 1].size(); ++j) {
                Lays[Lay][i].changeWeight[j] = E * Lays[Lay][i].error * Lays[Lay - 1][j].sigmoid() + A * Lays[Lay][i].changeWeight[j];
                Lays[Lay][i].weight[j] += Lays[Lay][i].changeWeight[j];
            }
        }
    }
}
double NeuronSystem::Is(int i, int j) {
    Lays[0][0].output = i;
    Lays[0][1].output = j;
    return Lays[2][0].sigmoid();
}