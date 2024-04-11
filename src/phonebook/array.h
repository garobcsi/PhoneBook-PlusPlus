#ifndef PHONEBOOK_ARRAY_H
#define PHONEBOOK_ARRAY_H

#include "../lib/memtrace.h"
#include <cstring>
#include <algorithm>
#include <stdexcept>

/**
 * @brief Dinamikus tömb osztálysablon.
 *
 * Ez az osztály dinamikus tömb megvalósítást biztosít különféle műveletekkel.
 * Lehetővé teszi elemek hozzáadását, eltávolítását és elemek predikátum alapján történő rendezését.
 * A tömb az alsó index operátor segítségével érhető el.
 *
 * @tparam T A tömbben tárolt elemek típusa.
 */
template <typename T>
class Array
{
    // Mutató a tömbre.
    T *arr = nullptr;
    // A tömb mérete.
    size_t len = 0;

public:
    /**
     * @brief Default konstruktor.
     */
    Array();

    /**
     * @brief Másoló konstruktor.
     *
     * @param a A másolandó tömb.
     */
    Array(const Array &a);

    /**
     * @brief Egy Array objektumot hoz létre a megadott inicializáló lista elemeivel.
     *
     * Ez a konstruktor inicializál egy Array objektumot a megadott inicializáló lista elemeivel.
     *
     * @param lista Az inicializáló lista, amely a tömbbe másolandó elemeket tartalmazza.
     */
    Array(std::initializer_list<T> list);

    /**
     * @brief Destructor.
     */
    virtual ~Array();

    /**
     * @brief Tömb méretének lekérdezése.
     *
     * @return A tömb mérete.
     */
    size_t size() const;

    /**
     * @brief Hozzáad egy elemet a tömbhöz.
     *
     * @param el Az elem, amelyet hozzá kell adni.
     */
    void pushBack(const T &el);

    /**
     * @brief Eltávolít egy elemet a tömbből az index helyén.
     *
     * @param index Az eltávolítandó elem indexe.
     */
    void removeEl(size_t index);

    /**
     * @brief Rendezés a tömb elemeinek egy predikátum alapján.
     *
     * @tparam P A rendezéshez használt predikátum típusa.
     * @param pred A rendezéshez használt predikátum.
     */
    template <typename P>
    void orderBy(P pred);

    /**
     * @brief Tömb értékadása.
     *
     * @param rhs A másolandó tömb.
     * @return Az új tömb.
     */
    Array &operator=(const Array &rhs);

    /**
     * @brief A tömb egy elemének elérése az index operátor használatával.
     *
     * @param index Az elérendő elem indexe.
     * @return Referencia az elért elemre.
     */
    T &operator[](size_t index);

    /**
     * @brief A tömb egy állandó elemének elérése az index operátor használatával.
     *
     * @param index Az elérendő elem indexe.
     * @return Konstans referencia az elért elemre.
     */
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
Array<T>::Array(std::initializer_list<T> list)
{
    len = list.size();
    arr = new T[len];
    std::copy(list.begin(), list.end(), arr);
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
