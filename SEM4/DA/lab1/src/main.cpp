#include <iostream>
#include <cstring>
#include "vector.hpp"

using namespace NMystd;
using ll = long long;

const int MAX_VAL_LEN = 2048;
const int MAX_KEY_LEN = 65535;

struct TMyPair {
    TMyPair() {
    }
    TMyPair(int f, char * s) : first(f), second(s) {
    }

    ~TMyPair() {

    }

    TMyPair& operator=(const TMyPair& rhs) {
		if(this == &rhs) {
			return *this;
		}
		this->first = rhs.first;
        memcpy(second, rhs.second, MAX_VAL_LEN);
		return *this;
	}
    int FirstGet() const {
        return first;
    }

    const char * SecondGet() const {
        return second;
    }
    int first;
    char * second;
};

int main () {
	std::cin.tie(0);
    std::ios::sync_with_stdio(false);

    int key;
    char buffer[MAX_VAL_LEN + 1];
    TVector<TMyPair *> vec; 

    while(std::cin >> key >> buffer) {
		char * ptrBuffer = strdup(buffer);
        TMyPair * pair = new TMyPair(key, ptrBuffer);
        vec.PushBack(pair);
    }

    TVector<TMyPair *> res(vec.Size());
    TVector<size_t> countKey(MAX_KEY_LEN + 1, 0);

    for(int i = 0; i < vec.Size(); ++i) {
        ++countKey[vec[i]->FirstGet()];
    }
    size_t sum = 0;
    for(int i = 0; i < countKey.Size(); ++i) {
        size_t t = countKey[i];
        countKey[i] = sum;
        sum += t;
    }

    for(int i = 0; i < vec.Size(); ++i) {
        res[countKey[vec[i]->FirstGet()]] = vec[i];
        ++countKey[vec[i]->FirstGet()];
    }

    for(int i = 0; i < res.Size(); ++i) {
        std::cout << res[i]->FirstGet() << "\t" << res[i]->SecondGet() << "\n";
    }

    for(int i = 0; i < res.Size(); ++i) {
        free(res[i]->second);
        delete res[i];
    }
}