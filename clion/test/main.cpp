#include "iostream"
#include "vector"
#include "math.h"
#include "fstream"
#include "random"
#include "ctime"
using namespace std;
class Neuron {
public:
    double sigmoid() {
        if (inputs[0] == NULL) {
            return output;
        }
        return 1/(1 + exp(-Sum()));
    }
    vector<Neuron *> inputs;
    vector<double> weight;
    vector<double> changeWeight;
    double output;
    double error;
private:
    double Sum() {
        if (inputs[0] == NULL) {
            return output;
        }
        output = 0;
        for (int i = 0; i != inputs.size(); ++i) {
            output += inputs[i]->sigmoid() * weight[i];
        }
        return output;
    }
};
class NeuronSystem {
public:
    NeuronSystem(vector<int> NeuronCount, double E, double A) : E(E), A(A) {
        Lays.resize(NeuronCount.size());
        for (int i = 0; i != NeuronCount.size(); ++i) {
            resizeLays(i, NeuronCount[i]);
        }
        for (int i = 0; i != NeuronCount.size() - 1; ++i) {
            neuronShift(i);
        }
        ifstream fin;
        fin.open("input.txt");
        for (int i = 1; i != NeuronCount.size(); ++i) {
            inputWeight(i, &fin);
        }
        fin.close();
//        Lays[1][0].weight[0] = 0.45;
//        Lays[1][0].weight[1] = -0.12;
//        Lays[1][1].weight[0] = 0.78;
//        Lays[1][1].weight[1] = -0.13;
//        Lays[2][0].weight[0] = 1.5;
//        Lays[2][0].weight[1] = -2.3;
    }
    void resizeLays(int numberLays, int countNeuron) {
        if (numberLays != Lays.size() - 1) {
            Lays[numberLays].resize(countNeuron + 1);
        }
        else {
            Lays[numberLays].resize(countNeuron);
        }
    }
    void neuronShift(int layNumber) {
        for (int i = 0; i != Lays[layNumber].size(); ++i) {
            Lays[layNumber][i].inputs.resize(1);
            Lays[layNumber][i].output = 1;
            Lays[layNumber][i].inputs[0] = NULL;
        }
    }
    void startNS(vector<vector<double>> & input, vector<double> & output) {
        double ErrorSystem = 1;
        int Epoch = 0;
        ofstream fout;
//        fout.open("log.txt");
        while (ErrorSystem > 0.0000001) {
            double InError = 0;
//            fout << "Epoch: " << Epoch <<'\n';
            for (int i = 0; i != input.size(); ++i) {
                for (int j = 0; j != input[0].size(); ++j) {
                    Lays[0][j].output = input[i][j];
                }
                double answer = Lays[Lays.size() - 1][0].sigmoid();
                InError += pow(output[i] - answer, 2);
//                fout << i + 1 << " answer " << answer << " "<< output[i] <<"\n";
                Lays[Lays.size() - 1][0].error = sigma0(answer, output[i]);
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
            if (Epoch % 100000 == 0) {
                cout << "Error: "<< ErrorSystem<<"\n";
                cout << "\n";
            }
            ++Epoch;
        }
        cout << "ErrorSystem = " << ErrorSystem << "\n";
        cout << "Complete" <<"\n";
//        fout.close();
    }
    void inputWeight (int layNumber, ifstream * fin) {
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
    void currentWeight (int currentLay, ofstream * fout) {
        for(int i = 0; i != Lays[currentLay].size() - 1; ++i) {
            for (int j = 0; j != Lays[currentLay - 1].size(); ++j) {
                *fout << Lays[currentLay][i].weight[j] <<" ";
            }
        }
    }
    void coutWeight () {
        ofstream fout;
        fout.open("input.txt");
        for (int i = 1; i != Lays.size(); ++i) {
            currentWeight(i, &fout);
        }
        fout.close();
    }
    double sigma0(double output, double answer){
        return (answer - output)*((1 - output) * output);
    }
    void sigma(int CurrentLay) {
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
    void ChangeWeight(int Lay) {
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
    double Is(int i, int j) {
        Lays[0][0].output = i;
        Lays[0][1].output = j;
        return Lays[2][0].sigmoid();
    }
    double E;
    double A;
private:
    vector<vector<Neuron>> Lays;
};

int main() {
    vector<int> v = {2, 2, 1};
    bool generate = true;
    cout << "generate new weight?" <<"\n";
    cin >> generate;
    if (generate) {
        int sum = 0;
        for (int i = 0; i != v.size() - 1; ++i) {
            sum += (v[i] + 1)* v[i + 1];
        }
        std::mt19937 gen(time(0));
        std::uniform_real_distribution<> urd(0, 1);
        ofstream fout;
        fout.open("input.txt");
        fout << urd(gen) << "\n";
    }
    NeuronSystem NS(v, 0.7, 0.3);
    vector<vector<double>> input (4, vector<double> (2));
    input = {{1, 0},{0, 1},{1, 1}, {0,0}};
    vector<double> output (4);
    output = {1, 1, 0, 0};
    NS.startNS(input, output);
    NS.coutWeight();
    int x, y;
    bool Do = true;
    while (Do) {
        cout << "input x, y" << "\n";
        cin >> x >> y;
        cout << NS.Is(x, y) << "\n";
//        if (NS.Is(x, y) > 0.99) {
//            cout << 1 << '\n';
//        }
//        else if (NS.Is(x, y) < 0.001){
//            cout << 0 <<"\n";
//        }
//        else {
//            cout << "error" <<"\n";
//        }
        cout << "continue?" <<"\n";
        cin >> Do;
    }
}