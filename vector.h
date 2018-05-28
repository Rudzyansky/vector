#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <cstdlib>
#include <malloc.h>
#include <cstring>

template<typename T>
class vector {
    size_t rsize;
    size_t _size;
    T *_data;

    void check_index(size_t index);

    void delete_array();

    T *init_array(size_t size);

public:
    explicit vector();

    explicit vector(size_t size);

    ~vector();

    size_t size();

    T *data();

    T &operator[](size_t index);

    void push_back(const T &value);

    void insert(size_t index, const T &value);

    void clear();

    T &pop_back();

    vector<T> &operator=(const vector<T> &v);

    void assign(size_t count, const T &value);

    T &front();

    T &back();

    bool empty();

    void swap(vector<T> &v);
};

template<typename T>
vector<T>::vector() : _size(0), rsize(10), _data((T *) calloc(10, sizeof(T))) {
    if (_data == nullptr) throw std::bad_alloc();
}

template<typename T>
vector<T>::vector(size_t size) : _size(0), rsize(size), _data((T *) calloc(size, sizeof(T))) {
    if (_data == nullptr) throw std::bad_alloc();
}

template<typename T>
vector<T>::~vector() {
    delete_array();
}

template<typename T>
size_t vector<T>::size() {
    return _size;
}

template<typename T>
T *vector<T>::data() {
    return _data;
}

template<typename T>
T &vector<T>::operator[](size_t index) {
    check_index(index);
    return _data[index];
}

template<typename T>
void vector<T>::check_index(size_t index) {
    if (index > _size - 1) throw std::out_of_range("invalid index");
}

template<typename T>
void vector<T>::push_back(const T &value) {
    if (_size >= rsize) {
        size_t nsize = rsize + 10;
        auto *tmp = (T *) realloc(_data, sizeof(T) * nsize);
        if (tmp == nullptr) throw std::bad_alloc();
        rsize = nsize;
        _data = tmp;
    }
    _data[_size++] = value;
}

template<typename T>
void vector<T>::insert(size_t index, const T &value) {
    if (index == _size) {
        push_back(value);
        return;
    }
    check_index(index);
    T *tmp = init_array(_size >= rsize ? rsize + 10 : rsize);
    for (size_t i = 0; i < index; ++i) tmp[i] = _data[i];
    tmp[index] = value;
    for (size_t i = index; i < _size; ++i) tmp[i + 1] = _data[i];
    delete_array();
    _data = tmp;
    ++_size;
}

template<typename T>
void vector<T>::delete_array() {
    T *ptr = _data;
    for (size_t i = 0; i < _size; ++i, ++ptr) (*ptr).~T();
    free(_data);
}

template<typename T>
void vector<T>::clear() {
    T *ptr = init_array(10);
    delete_array();
    _data = ptr;
    _size = 0;
}

template<typename T>
T &vector<T>::pop_back() {
    return _data[--_size];
}

template<typename T>
T &vector<T>::front() {
    return *_data;
}

template<typename T>
T &vector<T>::back() {
    return _data[_size - 1];
}

template<typename T>
bool vector<T>::empty() {
    return !(bool) _size;
}

template<typename T>
void vector<T>::assign(size_t count, const T &value) {
    T *ptr = init_array(count);
    delete_array();
    _size = rsize = count;
    _data = ptr;
    for (size_t i = 0; i < _size; ++i, ++ptr) *ptr = value;
}

template<typename T>
vector<T> &vector<T>::operator=(const vector<T> &v) {
    T *ptr = init_array(v._size);
    delete_array();
    _data = ptr;
    _size = rsize = v._size;
    std::memcpy(_data, v._data, _size * sizeof(T));
    return *this;
}

template<typename T>
void vector<T>::swap(vector<T> &v) {
    T *ptr;
    ptr = _data, _data = v._data, v._data = ptr;
    _size ^= v._size ^= _size ^= v._size;
    rsize ^= v.rsize ^= rsize ^= v.rsize;
}

template<typename T>
T *vector<T>::init_array(size_t size) {
    auto ptr = (T *) calloc(size, sizeof(T));
    if (ptr == nullptr) throw std::bad_alloc();
    return ptr;
}

#endif //VECTOR_VECTOR_H
