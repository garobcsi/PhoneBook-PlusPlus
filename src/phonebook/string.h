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
     *
     * @param index Az elérendő karakter indexe.
     * @return Referencia a megadott indexben lévő karakterre.
     */
    char &operator[](unsigned int index);

    /**
     * @brief Operátor konstans karakterlánc karaktereinek eléréséhez.
     *
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
};

#endif // PHONEBOOK_STRING_H