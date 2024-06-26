#ifndef PHONEBOOK_ARRAY_H
#define PHONEBOOK_ARRAY_H

#include "./memtrace.h"
#include <cstring>
#include <algorithm>
#include <stdexcept>

/**
 * @class Array
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
    /**
     * @brief Mutató a tömbre.
     * 
     */
    T *arr = nullptr;
    /**
     * @brief A tömb mérete.
     * 
     */
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
     * @param list Az inicializáló lista, amely a tömbbe másolandó elemeket tartalmazza.
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
     * @throw std::out_of_range Tulindexelés esetén.
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
     * @brief Szűri a tömb elemeit az adott predikátum alapján.
     *
     * @tparam P A predikátum függvény típusa.
     * @param pred A predikátum függvény, amely meghatározza, hogy egy elem szerepeljen-e a szűrt tömbben.
     * @return Vissza adja a szürt elemek listáját.
     */
    template <typename P>
    Array<T> where(P pred);

    /**
     * @brief Megtalálja a keresett elem indexét.
     *
     * @tparam P A predikátum függvény típusa.
     * @param pred A predikátum függvény, amely meghatározza, hogy egy elem indexét a tömbben.
     * @return Vissza adja azt az indexet ahol a Pred igaz, ha nem találja meg az elemet akkor -1 et ad vissza.
     */
    template <typename P>
    int search(P pred);

    /**
     * @brief Törli a tömb tartalmát és felszabadítja az általa foglalt memóriaterületet.
     *
     * Ez a függvény eltávolítja az összes elemet a tömbből, és felszabadítja az általa foglalt memóriaterületet.
     * A tömb ezután üres lesz, és új elemeket lehet hozzáadni a memória újrahasznosításával.
     */
    void clear();

    /**
     * @brief Tömb értékadása.
     *
     * @param rhs A másolandó tömb.
     * @return Az új tömb.
     */
    Array &operator=(const Array &rhs);

    /**
     * @brief A tömb egy elemének elérése az index operátor használatával.
     * @throw std::out_of_range Tulindexelés esetén.
     * @param index Az elérendő elem indexe.
     * @return Referencia az elért elemre.
     */
    T &operator[](size_t index);

    /**
     * @brief A tömb egy állandó elemének elérése az index operátor használatával.
     * @throw std::out_of_range Tulindexelés esetén.
     * @param index Az elérendő elem indexe.
     * @return Konstans referencia az elért elemre.
     */
    const T &operator[](size_t index) const;

    /**
     * @brief A tömb osztály iterátora.
     *
     * Egy iterátort használunk a tömb elemeinek bejárására.
     * Különféle operátorokat biztosít a növeléséhez, csökkentéséhez és az iterátorok összehasonlításához.
     */
    class Iterator
    {
        /**
         * @brief Tömb egyik elemére mutató pointer
         * 
         */
        T *ptr;

    public:
        /**
         * @brief Egy iterátort készít egy adott mutatóval.
         *
         * @param p A tömb egy elemére mutató mutató.
         */
        Iterator(T *p);

        /**
         * @return Hivatkozás arra az elemre, amelyre az iterátor mutat.
         */
        T &operator*() const;

        /**
         * @brief Növeli az iterátort, hogy a tömb következő elemére mutasson.
         *
         * @return Hivatkozás a növekményes iterátorra.
         */
        Iterator &operator++();

        /**
         * @brief Növeli az iterátort, hogy a tömb következő elemére mutasson.
         *
         * @return Az iterátor másolata a növelés előtt.
         */
        Iterator operator++(int);

        /**
         * @brief Csökkenti az iterátort, hogy a tömb előző elemére mutasson.
         *
         * @return Hivatkozás a csökkentett iterátorra.
         */
        Iterator &operator--();

        /**
         * @brief Csökkenti az iterátort, hogy a tömb előző elemére mutasson.
         *
         * @return Az iterátor másolata a csökkentés előtt.
         */
        Iterator operator--(int);

        /**
         * @brief Összehasonlítja az iterátort egy másik iterátorral az egyenlőség érdekében.
         *
         * @param other Az iterátor, amellyel összehasonlítani lehet.
         * @return true, ha az iterátorok egyenlőek, hamis ellenkező esetben.
         */
        bool operator==(const Iterator &other) const;

        /**
         * @brief Összehasonlítja az iterátort egy másik iterátorral az egyenlőtlenség szempontjából.
         *
         * @param other Az iterátor, amellyel összehasonlítani lehet.
         * @return true, ha az iterátorok nem egyenlőek, hamis ellenkező esetben.
         */
        bool operator!=(const Iterator &other) const;
    };

    /**
     * @brief Egy iterátor osztály a tömb elemei iterációhoz.
     *
     * Tömb elejétöl kezdve iterál.
     *
     * @return Az iterátor, amely a tömb elejére mutat.
     */
    Iterator begin() const;

    /**
     * @brief Egy iterátor osztály a tömb elemei iterációhoz.
     *
     * Tömb itelálásnál végét jelzi.
     *
     * @return Az iterátor, amely a tömb végére mutat.
     */
    Iterator end() const;

    /**
     * @brief Egy iterátor osztály a tömb elemei iterációhoz.
     *
     * Tömb végétöl kezdve iterál.
     *
     * @return Az iterátor, amely a tömb végére mutat.
     */
    Iterator rbegin() const;

    /**
     * @brief Egy iterátor osztály a tömb elemei iterációhoz.
     *
     * Tömb itelálásnál elejének a végét jelzi.
     *
     * @return Az iterátor, amely a tömb elejére mutat.
     */
    Iterator rend() const;
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
template <typename P>
Array<T> Array<T>::where(P pred)
{
    Array<T> tmp = *this;
    for (size_t i = 0; i < tmp.size(); ++i)
    {
        if (!pred(tmp.operator[](i)))
        {
            tmp.removeEl(i);
            i--;
        }
    }
    return tmp;
}

template<typename T>
template<typename P>
int Array<T>::search(P pred) {
    for (size_t i = 0; i < size(); ++i)
        if (pred(this->operator[](i)))
            return (int)i;
    return -1;
}

template <typename T>
void Array<T>::clear()
{
    delete[] arr;
    arr = nullptr;
    len = 0;
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

template <typename T>
Array<T>::Iterator::Iterator(T *p) : ptr(p) {}

template <typename T>
T &Array<T>::Iterator::operator*() const
{
    return *ptr;
}

template <typename T>
typename Array<T>::Iterator &Array<T>::Iterator::operator++()
{
    ++ptr;
    return *this;
}

template <typename T>
typename Array<T>::Iterator Array<T>::Iterator::operator++(int)
{
    Iterator tmp = *this;
    ++ptr;
    return tmp;
}

template <typename T>
typename Array<T>::Iterator &Array<T>::Iterator::operator--()
{
    --ptr;
    return *this;
}

template <typename T>
typename Array<T>::Iterator Array<T>::Iterator::operator--(int)
{
    Iterator tmp = *this;
    --ptr;
    return tmp;
}

template <typename T>
bool Array<T>::Iterator::operator==(const Array::Iterator &other) const
{
    return ptr == other.ptr;
}

template <typename T>
bool Array<T>::Iterator::operator!=(const Array::Iterator &other) const
{
    return ptr != other.ptr;
}

template <typename T>
typename Array<T>::Iterator Array<T>::begin() const
{
    return Iterator(arr);
}

template <typename T>
typename Array<T>::Iterator Array<T>::end() const
{
    return Iterator(arr + len);
}

template <typename T>
typename Array<T>::Iterator Array<T>::rbegin() const
{
    return Iterator(arr + len - 1);
}

template <typename T>
typename Array<T>::Iterator Array<T>::rend() const
{
    return Iterator(arr - 1);
}

#endif // PHONEBOOK_ARRAY_H
