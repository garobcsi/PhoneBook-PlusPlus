#ifndef PHONEBOOK_ARRAY_H
#define PHONEBOOK_ARRAY_H

#include <cstring>
#include <algorithm>

template <typename T>
class Array
{
    T *arr = nullptr;
    size_t len = 0;

public:
    Array();
    Array(const Array &a);
    virtual ~Array();

    size_t size() const;

    void pushBack(const T &el);
    void removeEl(size_t index);
    template <typename P>
    void orderBy(P pred);

    Array &operator=(const Array &rhs);
    T &operator[](size_t index);
    const T &operator[](size_t index) const;
};

template <typename T>
Array<T>::Array() : arr(nullptr), len(0) {}

template <typename T>
Array<T>::Array(const Array &a)
{
    len = a.len;
    arr = new T[len];
    std::copy(a.arr, a.arr + len, arr);
}

template <typename T>
Array<T>::~Array()
{
    delete[] arr;
}

template <typename T>
size_t Array<T>::size() const
{
    return len;
}

template <typename T>
void Array<T>::pushBack(const T &el)
{
    T *newArr = new T[len + 1];
    std::copy(arr, arr + len, newArr);
    newArr[len] = el;
    delete[] arr;
    arr = newArr;
    len++;
}

template <typename T>
void Array<T>::removeEl(size_t index)
{
    if (index >= len)
        throw std::out_of_range("Array: out of range");
    T *newArr = new T[len - 1];
    std::copy(arr, arr + index, newArr);
    std::copy(arr + index + 1, arr + len, newArr + index);
    len--;
    delete[] arr;
    arr = newArr;
}

template <typename T>
template <typename P>
void Array<T>::orderBy(P pred)
{
    std::sort(arr, arr + len, pred);
}

template <typename T>
Array<T> &Array<T>::operator=(const Array &rhs)
{
    if (this != &rhs)
    {
        delete[] arr;
        len = rhs.len;
        arr = new T[len];
        std::copy(rhs.arr, rhs.arr + len, arr);
    }
    return *this;
}

template <typename T>
T &Array<T>::operator[](size_t index)
{
    if (index >= len)
    {
        throw std::out_of_range("Array: out of range");
    }
    return arr[index];
}

template <typename T>
const T &Array<T>::operator[](size_t index) const
{
    if (index >= len)
    {
        throw std::out_of_range("Array: out of range");
    }
    return arr[index];
}

#endif // PHONEBOOK_ARRAY_H
