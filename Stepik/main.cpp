#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
int main () {
    ifstream fin;
    fin.open("input.txt");
    ofstream fout;
    fout.open("output.txt");
    string a;
    bool Do = false;
    while (fin >> a) {
        for (int i = 0; i != a.size(); ++i) {
            if (a[i] == '@') {
                fout << a[i];
                Do = true;
            }
            else if(a[i] == '<') {
                if (Do) 
                    fout << "(&#4448;) ";
                Do = false;
            }
            else if(Do) {
                fout << a[i];
            }
        }
    }
}