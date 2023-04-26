#pragma once
#include <cstring>
#include <iostream>
using namespace std;
class TString {
private:
    char* str;
    size_t size;
    friend TString operator+(const TString& lhs, const TString& rhs);
    friend std::ostream& operator<<(std::ostream& os, const TString& obj);
    friend std::istream& operator>>(std::istream& in, TString& obj);
    friend bool operator<(const TString& lhs, const TString& rhs);
    friend bool operator>(const TString& lhs, const TString& rhs);
    friend bool operator==(const TString& lhs, const TString& rhs);
    friend bool operator!=(const TString& lhs, const TString& rhs);
public:
    TString();
    TString(const char* cStr);
    TString(const TString& rhs);
    TString(TString&& rhs);
    ~TString();
    char& operator[](size_t index);
    const char& operator[](size_t index) const;
    TString& operator=(const TString& rhs);
    size_t Size() const;
    TString ToLower();
    const char* CStr() const;
};

TString::TString(): str(new char[1]) {
    str[0] = '\0';
}

TString::TString(const char* cStr) {
    if(cStr == nullptr) {
        str = new char[1];
        str[0] = '\0';
    } else {
        size = strlen(cStr);
        str = new char[size + 1];
        for(int i = 0; i < size; ++i) {
            str[i] = cStr[i];
        }
        str[size] = '\0';
    }
}

TString::TString(const TString& rhs) {
    size = rhs.size;
    str = new char[rhs.size + 1];
    strcpy(str, rhs.str);
    str[size] = '\0';
}

TString::TString(TString&& rhs) {
    str = rhs.str;
    rhs.str = nullptr;
}

TString::~TString() {
    delete[] str;
}

char& TString::operator[](size_t index) {
    return str[index];
}
const char& TString::operator[](size_t index) const {
    return str[index];
}

size_t TString::Size() const {
    return this->size;
}

TString TString::ToLower() {
    TString tmp;
    tmp = *this;
    for(int i = 0; i < tmp.Size(); ++i) {
        if(tmp[i] >= 'A' && tmp[i] <= 'Z') {
            tmp[i] += ('a' - 'A');
        }
    }
    return tmp;
}

TString& TString::operator=(const TString& rhs) {
    if(this == &rhs) {
        return *this;
    }
    delete[] str;
    str = new char[rhs.Size() + 1];
    strcpy(str, rhs.CStr());
    size = rhs.Size();
    return *this;
}

TString operator+(const TString& lhs, const TString& rhs) {
    char* newStr = new char[lhs.Size() + rhs.Size() + 1];
    strcpy(newStr, lhs.str);
    strcat(newStr, rhs.str);
    newStr[lhs.Size() + rhs.Size() + 1] = '\0';
    TString tmp(newStr);
    delete[] newStr;
    return tmp;
}

std::ostream& operator<<(std::ostream& os, const TString& obj) {
    os << obj.str;
    return os;
}

std::istream& operator>>(std::istream& in, TString& obj) {
    char buf[257] = "\0";
    in >> buf;
    obj = TString(buf);
    return in;
}

bool operator==(const TString& lhs, const TString& rhs) {
    if(lhs.Size() != rhs.Size()) {
        return false;
    }
    for(int i = 0; i < min(lhs.Size(), rhs.Size()); ++i) {
        if(lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const TString& lhs, const TString& rhs) {
    return !(lhs == rhs);
}

bool operator<(const TString& lhs, const TString& rhs) {
    for(int i = 0; i < min(lhs.Size(), rhs.Size()); ++i) {
        if(lhs[i] < rhs[i]) {
            return true;
        }
        if(lhs[i] > rhs[i]) {
            return false;
        }
    }
    return (lhs.Size() < rhs.Size()) ? true : false;
}

bool operator>(const TString& lhs, const TString& rhs) {
    return (lhs == rhs) ? false : !(lhs < rhs);
}

const char* TString::CStr() const {
    return this->str;
}