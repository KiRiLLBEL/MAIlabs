#include <cstddef>
#include <iostream>
#include <string.h>
using string = std::string;
template <class T>
class Array
{
public:
    // ������ ��������:
    //
    explicit Array(size_t size = 0, const T& value = T()) : _size(size) {
        _data = (T*)new char[_size * sizeof(T)];
        for (size_t i = 0; i < _size; ++i) {
            new(_data + i) T(value);
        }
    }
    Array() {
        _size = 0;
        _data = NULL;
    }
    //   ����������� ������, ������� �������
    //   Array ������� size, ����������� ����������
    //   value ���� T. �������� ��� � ���� T ����
    //   �����������, ������� ����� ������� ���
    //   ��� ����������, ���� �� ��� �� �����.
    //
    Array(const Array& A) : _size(A._size) {
        this->_data = (T*)new char[size * sizeof(T)];
        for (size_t i = 0; i < _size; ++i) {
            this->_data[i] = A._data[i];
        }
    }
    //   ����������� �����������, ������� �������
    //   ����� ���������. ��������, ��� ��� ����
    //   T ��������� �������� ������������.
    //
    ~Array() {
        for (size_t i = 0; i < _size; ++i) {
            (_data + i)->~T();
        }
        delete[](char*)_data;
    }
    //   ����������, ���� �� ��� ���������.
    //
    Array& operator=(const Array& A) {
        if (this != &A) {
            delete[](char*)_data;
            _size = A.size();
            _data = (T*)new char[_size * sizeof(T)];
            for (size_t i = 0; i < _size; ++i) {
                _data[i] = A._data[i];
            }
            return *this;
        }
        return *this;
    }
    //   �������� ������������.
    //
    size_t size() const {
        return _size;
    }
    //   ���������� ������ ������� (����������
    //                              ���������).
    //
    T& operator[](size_t index) {
        return _data[index];
    }
    const T& operator[](size_t index) const {
        return _data[index];
    }
    //   ��� ������ ��������� ������� �� �������.
    size_t _size;
    T* _data;
};
int main() {
    Array<int> A(6, 2);
    std::cout << A[5] << '\n';
    return 0;
}