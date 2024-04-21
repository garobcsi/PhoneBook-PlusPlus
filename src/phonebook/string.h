#ifndef PHONEBOOK_STRING_H
#define PHONEBOOK_STRING_H

#include "../lib/memtrace.h"
#include <iostream>
#include "./array.h"

/**
 * @class String
 * @brief Egy karakterláncot képviselő osztály.
 *
 * A String osztály funkciót biztosít a karakterláncok kezeléséhez.
 */
class String
{
    /**
     * @brief Karakter láncot tároló pointer
     * 
     */
    char *str = nullptr;
    /**
     * @brief Karakter lánc hossza
     * 
     */
    size_t len = 0;

public:
    /**
     * @brief Konstruktor létrehoz egy új String objektumot egyetlen karakterrel.
     *
     * @param c Az inicializálni kívánt karakter.
     */
    explicit String(char c);

    /**
     * @brief Konstruktor létrehoz egy új String objektumot a megadott karaktertömbbel.
     *
     * @param p Karaktertömbre mutató pointer.
     */
    String(const char *p = "");

    /**
     * @brief Konstruktor létrehoz egy új String objektumot egy másik String objektum másolásával.
     *
     * @param s A másolandó String objektum.
     */
    String(const String &s);

    /**
     * @brief String osztály destruktora.
     */
    virtual ~String();

    /**
     * @brief Visszaadja a karakterlánc méretét.
     *
     * @return A karakterlánc hossza.
     */
    size_t size() const;

    /**
     * @brief Visszaadja a karakterláncot nullterminátorral ellátva.
     *
     * @return A karakterláncot tartalmazó pointer.
     */
    const char *c_str() const;

    /**
     * @brief A karakterláncot részkarakterláncok tömbjére osztja fel az elválasztó karakter alapján.
     *
     * @param c Az elválasztó karakter, amely alapján a karakterláncot fel kell osztani.
     * @return Az alsztringeket reprezentáló String objektumok tömbje.
     */
    Array<String> split(char c);

    /**
     * @brief Másoló értékadás operátor.
     *
     * @param rhs A másolandó String objektum.
     * @return A másolódott String objektum referenciája.
     */
    String &operator=(const String &rhs);

    /**
     * @brief Összefűzés operátor két String objektumhoz.
     *
     * @param rhs A jobboldali String objektum.
     * @return Az összefűzött String objektum.
     */
    String operator+(const String &rhs) const;

    /**
     * @brief Összefűzés operátor egy karakterhez.
     *
     * @param rhs A jobboldali karakter.
     * @return Az összefűzött String objektum.
     */
    String operator+(char rhs) const;

    /**
     * @brief Operátor a karakterlánc egy adott indexű karakterének módosítására.
     * @throw std::out_of_range Ha az index kívül esik a karakterlánc határain.
     *
     * @param index Az elérendő karakter indexe.
     * @return Referencia a megadott indexben lévő karakterre.
     */
    char &operator[](unsigned int index);

    /**
     * @brief Operátor a karakterlánc egy adott indexű karakterének elérésére (konstans verzió).
     * @throw std::out_of_range Ha az index kívül esik a karakterlánc határain.
     *
     * @param index Az elérendő karakter indexe.
     * @return Konstans referencia a megadott indexben lévő karakterre.
     */
    const char &operator[](unsigned int index) const;

    /**
     * @brief Az operátor két String objektum összehasonlítására.
     *
     * @param rhs Az összehasonlítandó String objektum.
     * @return Igaz, ha az aktuális objektum lexikografikusan kisebb, mint a másik, egyébként hamis.
     */
    bool operator<(const String &rhs) const;

    /**
     * @brief Az operátor ellenőrzi, hogy két String objektum egyenlő-e.
     *
     * @param rhs Az összehasonlítandó String objektum.
     * @return Igaz, ha a két String objektum megegyezik, egyébként hamis.
     */
    bool operator==(const String &rhs) const;

    /**
     * @brief Az operátor ellenőrzi, hogy két String objektum nem egyenlő-e.
     *
     * @param rhs Az összehasonlítandó String objektum.
     * @return Hamis, ha a két String objektum megegyezik, egyébként igaz.
     */
    bool operator!=(const String &rhs) const;

    /**
     * @brief Túlterhelt << operátor egy String objektum kiírására.
     *
     * @param os A kimeneti adatfolyam, amelybe írni kell.
     * @param s A kiírandó String objektum.
     * @return A kimeneti adatfolyam referenciája.
     */
    friend std::ostream &operator<<(std::ostream &os, const String &s);

    /**
     * @brief Túlterhelt >> operátor egy String objektum beolvasására.
     *
     * @param is A bemeneti adatfolyam.
     * @param s Az értéktároló String objektum.
     * @return A bemeneti adatfolyam referenciája.
     */
    friend std::istream &operator>>(std::istream &is, String &s);

    /**
     * @brief Túlterhelt + operátor egy karakter és egy String objektum összefűzésére.
     *
     * @param lhs A baloldali karakter.
     * @param rhs A jobboldali String objektum.
     * @return Az összefűzött String objektum.
     */
    friend String operator+(char lhs, const String &rhs);

    /**
     * @class Iterator
     * @brief Iterátor osztály a String osztályhoz.
     */
    class Iterator
    {
        /**
         * @brief A string egy karakterére mutató pointer
         * 
         */
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
         * @return Az iterátor referenciája.
         */
        Iterator &operator++();

        /**
         * @brief Előrelépés a következő karakterre (utólagos).
         *
         * @return Az iterátor eredeti példányának másolata.
         */
        Iterator operator++(int);

        /**
         * @brief Hátralépés a előző karakterre.
         *
         * @return Az iterátor referenciája.
         */
        Iterator &operator--();

        /**
         * @brief Hátralépés a előző karakterre (utólagos).
         *
         * @return Az iterátor eredeti példányának másolata.
         */
        Iterator operator--(int);

        /**
         * @brief Az iterátor által mutatott karakter elérése.
         *
         * @return A mutatott karakter.
         */
        char operator*() const;

        /**
         * @brief Az iterátorok összehasonlítása.
         *
         * @param other A másik iterátor.
         * @return Igaz, ha az iterátorok ugyanarra a karakterre mutatnak, egyébként hamis.
         */
        bool operator==(const Iterator &other) const;

        /**
         * @brief Az iterátorok összehasonlítása.
         *
         * @param other A másik iterátor.
         * @return Hamis, ha az iterátorok ugyanarra a karakterre mutatnak, egyébként igaz.
         */
        bool operator!=(const Iterator &other) const;
    };

    /**
     * @brief Iterátor a karakterlánc elejéhez.
     *
     * @return A karakterlánc első karakterére mutató iterátor.
     */
    Iterator begin() const;

    /**
     * @brief Iterátor a karakterlánc végéhez.
     *
     * @return A karakterlánc utáni területre mutató iterátor.
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