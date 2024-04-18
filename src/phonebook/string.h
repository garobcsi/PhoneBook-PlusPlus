#ifndef PHONEBOOK_STRING_H
#define PHONEBOOK_STRING_H

#include "../lib/memtrace.h"
#include <iostream>

/**
 * @class String
 * @brief Egy karakterláncot képviselő osztály.
 *
 * A String osztály funkciót biztosít a karakterláncok kezeléséhez.
 */
class String
{
    // Karakter láncot tároló pointer
    char *str = nullptr;
    // Karakter lánc hossza
    size_t len = 0;

public:
    /**
     * @brief Új String objektumot hoz létre a megadott karakterrel.
     *
     * @param c A egy karakter, amellyel inicializálja a karakterláncot.
     */
    explicit String(char c);

    /**
     * @brief Új String objektumot hoz létre a megadott pointerel.
     *
     * Ez a konstruktor egy új String objektumot hoz létre a megadott karaktertömbbel.
     *
     * @param p Karaktertömbre mutató pointer.
     */
    String(const char *p = "");

    /**
     * @brief Új String objektumot hoz létre egy másik String objektum másolásával.
     *
     * @param s A másolandó String objektum.
     */
    String(const String &s);

    /**
     * @brief Destructor a String osztályhoz.
     */
    virtual ~String();

    /**
     * @brief A karakterlánc méretét adja vissza.
     *
     * Ez a függvény a karakterláncban lévő karakterek számát adja vissza.
     *
     * @return A karakterlánc mérete.
     */
    size_t size() const;

    /**
     * @brief A objektum által tárolt karakterláncot adja vissza.
     *
     * @return Vissza adja a karakterláncot.
     */
    const char *c_str() const;

    /**
     * @brief Másoló értékadás operátor.
     *
     * @param rhs Jobb oldali másolandó objektum.
     */
    String &operator=(const String &rhs);

    /**
     * @brief Összefűzés operátor.
     *
     * @param rhs Jobb oldali objektum.
     */
    String operator+(const String &rhs) const;

    /**
     * @brief Összefűzés operátor 1 karakter.
     *
     * @param rhs Jobb oldali karakter.
     */
    String operator+(char rhs) const;

    /**
     * @brief Operátor a karakterlánc karaktereinek eléréséhez.
     * @throw std::out_of_range Tulindexelés esetén.
     * @param index Az elérendő karakter indexe.
     * @return Referencia a megadott indexben lévő karakterre.
     */
    char &operator[](unsigned int index);

    /**
     * @brief Operátor konstans karakterlánc karaktereinek eléréséhez.
     * @throw std::out_of_range Tulindexelés esetén.
     * @param index Az elérendő karakter indexe.
     * @return Konstans referencia a megadott indexben lévő karakterre.
     */
    const char &operator[](unsigned int index) const;

    /**
     * @brief Operátor két String objektum összehasonlítása.
     *
     * Ez a függvény összehasonlítja az aktuális String objektumot az "rhs" String objektummal
     * és igaz értéket ad vissza, ha az aktuális objektum lexikográfiailag kisebb, mint "rhs",
     * és egyébként hamis.
     *
     * @param rhs Az összehasonlítandó String objektum.
     * @return Igaz, ha az aktuális objektum kisebb, mint `rhs`, ellenkező esetben false.
     */
    bool operator<(const String &rhs) const;

    /**
     * @brief Ellenőrzi, hogy az aktuális karakterlánc egyenlő-e az adott karakterlánccal.
     *
     * @param rhs Az összehasonlítandó karakterlánc.
     * @return Igaz, ha a karakterláncok egyenlőek, hamis egyébként.
     */
    bool operator==(const String &rhs) const;

    /**
     * @brief Túlterheli a << operátort, hogy lehetővé tegye egy String objektum nyomtatását a kimeneti adatfolyamba.
     *
     * @param os A kimeneti adatfolyam, amelybe írni kell.
     * @param s A nyomtatandó String objektum.
     * @return std::ostream& Referencia a kimeneti adatfolyamra a String objektum kinyomtatása után.
     */
    friend std::ostream &operator<<(std::ostream &os, const String &s);

    /**
     * @brief Túlterhelt bemeneti adatfolyam-kivonási operátor a String osztályhoz.
     *
     * Ez a funkció lehetővé teszi, hogy kinyerjen egy String objektumot egy bemeneti adatfolyamból.
     * 
     * Ha std::noskipws állapotban van a bemeneti adatfolyam, akkor a funkció beolvassa az egész string et whitespace el.
     *
     * @param is A bemeneti adatfolyam.
     * @param s A String objektum az érték tárolására.
     * @return std::istream& referencia.
     */
    friend std::istream &operator>>(std::istream &is, String &s);

    /**
     * @brief Túlterhelt operátor+ egy karakter és egy String objektum összefűzéséhez.
     *
     * @param lhs A hozzáadandó karakter.
     * @param rhs Az összefűzendő String objektum.
     * @return Az összefűzés eredményeként létrejövő új String objektum.
     */
    friend String operator+(char lhs, const String &rhs);

    /**
     * @class Iterator
     * @brief Iterátor osztály a String osztályhoz.
     */
    class Iterator
    {
        char *ptr;

    public:
        /**
         * @brief Konstruktor az iterátorhoz.
         *
         * @param p A string egy elemére mutató mutató.
         */
        Iterator(char *p);

        /**
         * @brief Előrelépés a következő karakterre.
         *
         * @return Iterator& Referencia az iterátorra.
         */
        Iterator &operator++();

        /**
         * @brief Előrelépés a következő karakterre (utólagos).
         *
         * @return Iterator& Referencia az iterátorra.
         */
        Iterator operator++(int);

        /**
         * @brief Hátralépés a elöző karakterre.
         *
         * @return Iterator& Referencia az iterátorra.
         */
        Iterator &operator--();

        /**
         * @brief Hátralépés a elöző karakterre (utólagos).
         *
         * @return Iterator& Referencia az iterátorra.
         */
        Iterator operator--(int);

        /**
         * @brief Az iterátor által mutatott karakter elérése.
         *
         * @return char A mutatott karakter.
         */
        char operator*() const;

        /**
         * @brief Az iterátorok összehasonlítása.
         *
         * @param other A másik iterátor, amivel összehasonlítjuk.
         * @return bool Igaz, ha az iterátorok ugyanarra a karakterre mutatnak, egyébként hamis.
         */
        bool operator==(const Iterator &other) const;

        /**
         * @brief Az iterátorok összehasonlítása.
         *
         * @param other A másik iterátor, amivel összehasonlítjuk.
         * @return bool Hamis, ha az iterátorok ugyanarra a karakterre mutatnak, egyébként igaz.
         */
        bool operator!=(const Iterator &other) const;
    };

    /**
     * @brief Iterátor a karakterlánc elejéhez.
     *
     * @return Pointer az első karakterre.
     */
    Iterator begin() const;

    /**
     * @brief Iterátor a karakterlánc végéhez.
     *
     * @return Pointer a karakterlánc utáni területre.
     */
    Iterator end() const;

    /**
     * @brief Fordított iterátor a karakterlánc végéhez.
     *
     * @return Fordított iterátor a karakterlánc végéhez.
     */
    Iterator rbegin() const;

    /**
     * @brief Fordított iterátor a karakterlánc elejéhez.
     *
     * @return Fordított iterátor a karakterlánc elejéhez.
     */
    Iterator rend() const;
};

#endif // PHONEBOOK_STRING_H