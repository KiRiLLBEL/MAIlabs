#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include "string.hpp"
#include "vector.hpp"
#include "btree.hpp"

int main() {
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);
    TString command;
    TString key;
    TString path;
    unsigned long long value;
    TBTree tree(3);
    while(std::cin >> command) {

        if(command[0] == '+') {
            std::cin >> key >> value;
            key = key.ToLower();
            if(tree.Insert(key, value)) {
                cout << "OK" << '\n';
            } else {
                cout << "Exist" << '\n';
            }
        } else if(command[0] == '-') {
            std::cin >> key;
            key = key.ToLower();
            if(tree.Delete(key)) {
                cout << "OK" << '\n';
            } else {
                cout << "NoSuchWord" << '\n';
            }
        } else if(command[0] == '!') {
            cin >> key >> path;
            if(key[0] == 'L') {
                ifstream File(path.CStr(), ios_base::binary);
                tree.ReadFromFile(File);
                File.close();
            } else {
                ofstream File(path.CStr(), ios_base::binary | ios_base::trunc);
                tree.WriteToFile(File);
                File.close();

            }
        } else {
            command = command.ToLower();
            if(tree.Find(command)) {
                cout << "OK: " << tree[command] << '\n';
            } else {
                cout << "NoSuchWord" << '\n';
            }
        }

    }

    return 0;
}