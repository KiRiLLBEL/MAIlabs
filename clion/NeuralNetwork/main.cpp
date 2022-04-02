#include "iostream"
#include "fstream"
#include "vector"
#include "math.h"
#include "random"
#include "chrono"
#include "bitmap_image.hpp"
using namespace std;
unsigned char** read_mnist_images(string full_path, int& number_of_images, int& image_size) {
    auto reverseInt = [](int i) {
        unsigned char c1, c2, c3, c4;
        c1 = i & 255, c2 = (i >> 8) & 255, c3 = (i >> 16) & 255, c4 = (i >> 24) & 255;
        return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
    };

    typedef unsigned char uchar;

    ifstream file(full_path, ios::binary);
    if(file.is_open()) {
        int magic_number = 0, n_rows = 0, n_cols = 0;

        file.read((char *)&magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);

        if(magic_number != 2051) throw runtime_error("Invalid MNIST image file!");

        file.read((char *)&number_of_images, sizeof(number_of_images)), number_of_images = reverseInt(number_of_images);
        file.read((char *)&n_rows, sizeof(n_rows)), n_rows = reverseInt(n_rows);
        file.read((char *)&n_cols, sizeof(n_cols)), n_cols = reverseInt(n_cols);

        image_size = n_rows * n_cols;
        uchar** _dataset = new uchar*[number_of_images];
        for(int i = 0; i < number_of_images; i++) {
            _dataset[i] = new uchar[image_size];
            file.read((char *)_dataset[i], image_size);
        }
        return _dataset;
    } else {
        throw runtime_error("Cannot open file `" + full_path + "`!");
    }
}
unsigned char* read_mnist_labels(string full_path, int& number_of_labels) {
    auto reverseInt = [](int i) {
        unsigned char c1, c2, c3, c4;
        c1 = i & 255, c2 = (i >> 8) & 255, c3 = (i >> 16) & 255, c4 = (i >> 24) & 255;
        return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
    };

    typedef unsigned char uchar;

    ifstream file(full_path, ios::binary);

    if(file.is_open()) {
        int magic_number = 0;
        file.read((char *)&magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);

        if(magic_number != 2049) throw runtime_error("Invalid MNIST label file!");

        file.read((char *)&number_of_labels, sizeof(number_of_labels)), number_of_labels = reverseInt(number_of_labels);

        uchar* _dataset = new uchar[number_of_labels];
        for(int i = 0; i < number_of_labels; i++) {
            file.read((char*)&_dataset[i], 1);
        }
        return _dataset;
    } else {
        throw runtime_error("Unable to open file `" + full_path + "`!");
    }
}
class Neuron {
public:
    void sigmoid() {
        hi = 1 / (1 + exp(-zi));
    }
    void relu() {
        hi = (zi > 0) ? zi : 0;
    }
    void sum() {
        int Count = inputs.size();
        zi = 0;
        for(int i = 0; i != Count; ++i) {
            zi += weight[i]*inputs[i]->hi;
        }
    }
    vector<Neuron *> inputs;
    vector<double> weight;
    vector<double> changeWeight;
    double zi;
    double hi;
    double delta;
};
class NeuronSystem {
public:
    NeuronSystem(vector<int> NeuronCount, double E, double A) : E(E), A(A) {
        int NeuronCounts = NeuronCount.size();
        Lays.resize(NeuronCounts);
        for (int i = 0; i != NeuronCounts; ++i) {
            resizeLays(i, NeuronCount[i]);
        }
        for (int i = 0; i != NeuronCounts - 1; ++i) {
            neuronBias(i);
        }
        ifstream fin;
        fin.open("input.txt");
        for (int i = 1; i != NeuronCounts; ++i) {
            inputWeight(i, &fin);
        }
        fin.close();
    }
    void neuronBias(int CurrentLay) {
        int count = Lays[CurrentLay].size();
        Lays[CurrentLay][count - 1].hi = 1;
    }
    void resizeLays(int numberLays, int countNeuron) {
        if (numberLays != Lays.size() - 1) {
            Lays[numberLays].resize(countNeuron + 1);
        }
        else {
            Lays[numberLays].resize(countNeuron);
        }
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
    void forwardfeed(string activationFunction) {
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
    void IterationSigmoid(int CurrentLay) {
        int CountNeuron = Lays[CurrentLay].size();
        for (int i = 0; i != CountNeuron - 1; ++i) {
            Lays[CurrentLay][i].sum();
            Lays[CurrentLay][i].sigmoid();
        }
    }
    void IterationRelu(int CurrentLay) {
        int CountNeuron = Lays[CurrentLay].size();
        for (int i = 0; i != CountNeuron - 1; ++i) {
            Lays[CurrentLay][i].sum();
            Lays[CurrentLay][i].relu();
        }
    }
    void IterationEndSigmoid() {
        int LastLayer = Lays.size() - 1;
        int CountNeuron = Lays[LastLayer].size();
        for (int i = 0; i != CountNeuron; ++i) {
            Lays[LastLayer][i].sum();
            Lays[LastLayer][i].sigmoid();
        }
    }
    void Softmax() {
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
    double ErrorQuad(vector<double> output) {
        int LastLayer = Lays.size() - 1;
        int CountNeuron = Lays[LastLayer].size();
        double Error = 0;
        for (int i = 0; i != CountNeuron; ++i) {
            Error += pow(Lays[LastLayer][i].hi - output[i], 2);
        }
        return Error;
    }
    double CrossEntropy(vector<double> answers) {
        int LastLayer = Lays.size() - 1;
        int CountNeuron = Lays[LastLayer].size();
        double Error = 0;
        for (int i = 0; i != CountNeuron; ++i) {
            Error += answers[i]* log(Lays[LastLayer][i].hi);
        }
        return -Error;
    }
    void backpropagation(string activationFunction) {
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
    void deltaEndSigmoid(vector<double> output) {
        int LastLayer = Lays.size() - 1;
        int CountNeuron = Lays[LastLayer].size();
        for (int i = 0; i != CountNeuron; ++i) {
            Lays[LastLayer][i].delta = (output[i] - Lays[LastLayer][i].hi)*((1 - Lays[LastLayer][i].hi)*Lays[LastLayer][i].hi);
        }
    }
    void deltaEndRelu(vector<double> answers) {
        int LastLayer = Lays.size() - 1;
        int CountNeuron = Lays[LastLayer].size();
        for (int i = 0; i != CountNeuron; ++i) {
            Lays[LastLayer][i].delta = -(Lays[LastLayer][i].hi - answers[i]);
        }
    }
    void deltaSigmoid(int CurrentLay) {
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
    void deltaRelu(int CurrentLay) {
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
    void ChangeWeight(int CurrentLay) {
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
    void NeuronSystemStart(vector<vector<double>> input, vector<double> output, string activatonFunction) {
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
                cout << "Error: "<< ErrorSystem<<"\n";
                cout << "\n";
                ++Epoch;
            }
            cout << "Complete" <<"\n";
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
                    vector<double> answers(Lays[LastLayer].size(), 0);
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
                cout << "-----------Epoch Error: "<< ErrorSystem<<"\n";
                cout << "\n";
                ++Epoch;
            }
        }
        else {
            cout << "Error - not mode" <<"\n";
        }
    }
    double Is(int i, int j) {
        Lays[0][0].hi = i;
        Lays[0][1].hi = j;
        forwardfeed("sigmoid");
        return Lays[2][0].hi;
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
    void NeuralSystemAnswer(vector<vector<double>> input, string activatonFunction) {
        if (activatonFunction == "sigmoid") {
            int inputSize = input.size();
            int inputSize1 = input[0].size();
            for (int i = 0; i != inputSize; ++i) {
                for (int j = 0; j != inputSize1; ++j) {
                    Lays[0][j].hi = input[i][j];
                }
                forwardfeed("sigmoid");
                cout << "Answer = " << Lays[Lays.size() - 1][0].hi << "\n";
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
                cout << "\nAnswer = " << AnswerI << "\n";
            }
        }
        else {
            cout << "Error - not mode" <<"\n";
        }
    }
    double E;
    double A;
private:
    vector<vector<Neuron>> Lays;
};

int main () {
    vector<int> v = {758, 128, 10};
    bool generate = true;
    cout << "generate new weight?" <<"\n";
    cin >> generate;
    if (generate) {
        ofstream fout;
        fout.open("input.txt");
        int sum = 0;
        for (int i = 0; i != v.size() - 1; ++i) {
            sum += (v[i] + 1)* v[i + 1];
        }
        std::mt19937 gen(time(0));
        std::uniform_real_distribution<> urd(-1, 1);
        for (int i = 0; i != sum; ++i) {
            fout << urd(gen) << "\n";
        }
        fout.close();
    }
    unsigned char ** dataset;
    int x, y;
    dataset = read_mnist_images("C:/Users/kiril/Projects/clion/imageTest/cmake-build-debug/train-images.idx3-ubyte", x, y);
    vector <vector <double>> input(x, vector<double> (y));
    for (int i = 0; i != x; ++i) {
        for (int j = 0; j != y; ++j) {
            input[i][j] = (double)(unsigned)dataset[i][j] / 255;
        }
    }
    delete [] dataset;
    unsigned char * data;
    int z;
    data = read_mnist_labels("C:/Users/kiril/Projects/clion/NeuralTest/cmake-build-debug/train-labels.idx1-ubyte", z);
    vector<double> output (z);
    for (int i = 0; i != z; ++i) {
        output[i] = (unsigned)data[i];
    }
    delete [] data;
    NeuronSystem NS(v, 0.005, 0.03);
    bool LearnDo = true;
    cout << "Start new learn?" << "\n";
    cin >> LearnDo;
    if (LearnDo){
        NS.NeuronSystemStart(input, output, "relu");
        NS.coutWeight();
    }
    bitmap_image image("input.bmp");

    if (!image)
    {
        printf("Error - Failed to open: input.bmp\n");
        return 1;
    }

    unsigned int total_number_of_pixels = 0;

    const unsigned int height = image.height();
    const unsigned int width  = image.width();
    input.resize(1);
    int i = 0;
    for (std::size_t y = 0; y < height; ++y)
    {
        for (std::size_t x = 0; x < width; ++x)
        {
            rgb_t colour;
            image.get_pixel(x, y, colour);
            input[0][i] = (unsigned)colour.red / 255;
            //cout << input[0][i] << " ";
            ++i;
        }
    }
    NS.NeuralSystemAnswer(input, "relu");
    return 0;

}
