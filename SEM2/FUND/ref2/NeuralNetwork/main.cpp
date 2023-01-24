#include "iostream"
#include "vector"
#include "math.h"
#include "random"
#include "chrono"
#include "bitmap_image.hpp"
#include "NeuralNetwork.h"
#include "MnistReader.h"
using namespace std;
int main () {
    vector<int> v = {784, 128, 10};
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
    dataset = read_mnist_images("C:/Users/kiril/Projects/ref2/NeuralNetwork/cmake-build-debug/train-images.idx3-ubyte", x, y);
    vector <vector <double>> input(x, vector<double> (y));
    for (int i = 0; i != x; ++i) {
        for (int j = 0; j != y; ++j) {
            input[i][j] = (double)(unsigned)dataset[i][j] / 255;
        }
    }
    vector<vector<double>> test (1, vector<double> (784));
    for (int j = 0; j != 784; ++j) {
        test[0][j] = (double)(unsigned)dataset[15][j] / 255;
    }
    delete [] dataset;
    unsigned char * data;
    int z;
    data = read_mnist_labels("C:/Users/kiril/Projects/ref2/NeuralNetwork/cmake-build-debug/train-labels.idx1-ubyte", z);
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
            ++i;
        }
    }
    NS.NeuralSystemAnswer(test, "relu");
    return 0;

}
