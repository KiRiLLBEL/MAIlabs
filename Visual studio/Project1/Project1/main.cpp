#include <cstddef>
#include <iostream>
#include <string.h>
using string = std::string;
template <class T>
class Array
{
public:
    // Список операций:
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
    //   конструктор класса, который создает
    //   Array размера size, заполненный значениями
    //   value типа T. Считайте что у типа T есть
    //   конструктор, который можно вызвать без
    //   без параметров, либо он ему не нужен.
    //
    Array(const Array& A) : _size(A._size) {
        this->_data = (T*)new char[size * sizeof(T)];
        for (size_t i = 0; i < _size; ++i) {
            this->_data[i] = A._data[i];
        }
    }
    //   конструктор копирования, который создает
    //   копию параметра. Считайте, что для типа
    //   T определен оператор присваивания.
    //
    ~Array() {
        for (size_t i = 0; i < _size; ++i) {
            (_data + i)->~T();
        }
        delete[](char*)_data;
    }
    //   деструктор, если он вам необходим.
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
    //   оператор присваивания.
    //
    size_t size() const {
        return _size;
    }
    //   возвращает размер массива (количество
    //                              элементов).
    //
    T& operator[](size_t index) {
        return _data[index];
    }
    const T& operator[](size_t index) const {
        return _data[index];
    }
    //   две версии оператора доступа по индексу.
    size_t _size;
    T* _data;
};
int main() {
    Array<int> A(6, 2);
    std::cout << A[5] << '\n';
    return 0;
}