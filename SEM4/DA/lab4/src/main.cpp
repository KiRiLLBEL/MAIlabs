#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>

using TSize = unsigned int;
struct TNumber {
    TNumber() : number(0), row(0), colomn(0) {

    }
    TNumber(TSize number, TSize row, TSize colomn) : number(number), row(row), colomn(colomn) {

    }
    TSize number;
    TSize row, colomn;
};
bool operator==(const TNumber& lhs, const TNumber& rhs) {
    return lhs.number == rhs.number;
}
bool operator!=(const TNumber& lhs, const TNumber& rhs) {
    return lhs.number != rhs.number;
}
std::vector<TSize> ZFunction(const std::vector<TNumber>& pattern) {
    TSize n = pattern.size();
    std::vector<TSize> z(n);
    z[0] = n;
    TSize l = 0, r = 0;
    for(TSize i = 1; i < n; ++i) {
        if(i <= r) {
            z[i] = std::min(z[i - l], r - i + 1);
        }
        while(i + z[i] < n && pattern[z[i]] == pattern[i + z[i]]) {
            ++z[i];
        }
        if(i + z[i] >= r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

std::vector<TSize> StrongPrefixFunctionWithZ(const std::vector<TNumber>& pattern) {
    std::vector<TSize> z = ZFunction(pattern);
    TSize n = pattern.size();
    std::vector<TSize> prefix(n, 0);
    for(TSize j = n - 1; j >= 1; --j) {
        prefix[j + z[j] - 1] = z[j];
    }
    return prefix;
}
struct TReader {
    TReader() : num(0, 1, 1), end(false) {

    }
    bool read(TNumber& number) {
        if(end) {
            return false;
        }
        char c = getchar();
        bool notNumber = true;
        while(1) {
            if(c == EOF) {
                if(!notNumber) {
                    number = num;
                    num.number = 0;
                    notNumber = true;
                    end = true;
                    break;
                }
                return false;
            }
            if(c == '\n') {
                if(!notNumber) {
                    number = num;
                    num.number = 0;
                    notNumber = true;
                    ++num.row;
                    num.colomn = 1;
                    break;
                }
                ++num.row;
                num.colomn = 1;
            } else if(c == '\t' || c == ' ') {
                if(!notNumber) {
                    number = num;
                    num.number = 0;
                    notNumber = true;
                    ++num.colomn;
                    break;
                }
            } else {
                if(c >= '0' && c <= '9') {
                    num.number = num.number * 10 + (c - '0');
                }
                notNumber = false;
            }
            c = getchar();
        }
        return true;
    }
    TNumber num;
    bool end;
};



int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::vector<TNumber> pattern;
    TNumber num(0, 1, 1);
    char c = getchar();
    bool notNumber = true;
    while(1) {
        if(c == '\n') {
            if(!notNumber) {
                pattern.push_back(num);
                num.number = 0;
                notNumber = true;
            }
            break;
        } else if(c == '\t' || c == ' ') {
            if(!notNumber) {
                pattern.push_back(num);
                num.number = 0;
                notNumber = true;
            }
        } else {
            if(c >= '0' && c <= '9') {
                num.number = num.number * 10 + (c - '0');
            }
            notNumber = false;
        }
        c = getchar();
    }
    std::vector<TSize> pref = StrongPrefixFunctionWithZ(pattern);
    std::vector<TNumber> text(pattern.size());
    TReader reader;
    TSize i = 0;
    TSize j = 0;
    TSize m = pattern.size();
    bool notEndOfFile = reader.read(text[j]);
    while(notEndOfFile) {
        bool needToRead = false;
        if(pattern[j] == text[i] && j < m) {
            ++j;
            needToRead = true;
        }
        else if (j == 0) {
            needToRead = true;
        } else {
            j = pref[j - 1];
        }
        if(j == m) {
            std::cout << text[(i + 1) % m].row << ", " << text[(i + 1) % m].colomn << "\n";
            j = pref[j - 1];
        }

        if(needToRead) {
            i = (i + 1) % m;
            notEndOfFile = reader.read(text[i]);
        }
    }
    return 0;
}