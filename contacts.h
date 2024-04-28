#ifndef PHONEBOOK_CONTACTS_H
#define PHONEBOOK_CONTACTS_H

#include "./memtrace.h"
#include "array.h"
#include "contact.h"

/**
 * @class Contacts
 * @brief Eltárolja az felhasználónak az összes ismeröseinek a telefonszámát
 *
 * Biztositani fog a CSV formátumú filek beolvasására és irására,
 * adatok elérése, adatok modositása, adatok törlésére, és létrehozásra is.
 */
class Contacts : public Array<Contact>
{

public:
    /**
     * @brief Alapértelmezett konstruktor létrehoz egy üres kapcsolatok listát.
     */
    Contacts();

    /**
     * @brief Másoló konstruktor, ami létrehoz egy új kapcsolatok listát az adott listából.
     *
     * @param a A másolandó kapcsolatok lista.
     */
    Contacts(const Contacts &a);

    /**
     * @brief Konstruktor, ami létrehoz egy kapcsolatok listát az initializer_list-ből.
     *
     * @param list Az initializer_list, amiből létrehozzuk a kapcsolatok listáját.
     */
    Contacts(std::initializer_list<Contact> list);

    /**
     * @brief Másoló értékadás operátor
     *
     * @param rhs Constans jobb oldali másolandó objectum
     * @return Contacts& Másolt referenciát ad vissza.
     */
    Contacts &operator=(const Contacts &rhs);

    /**
     * @brief Betölti a kapcsolatokat egy fájlból.
     *
     * @throw std::runtime_error a file nem nyitható meg vagy ha a file az üres
     * @param fileName A betöltendő fájl neve.
     */
    void loadFile(const String &fileName);

    /**
     * @brief Menti a kapcsolatokat egy fájlba.
     *
     * @throw std::runtime_error a file nem nyitható meg
     * @param fileName A mentendő fájl neve.
     */
    void saveFile(const String &fileName);

    /**
     * @brief Megnézi hogy a file létezik e.
     *
     * @param file Fájl neve
     * @return Igazat ad ha a file létezik, egylbként hamisat.
     */
    static bool fileExists(const String &file);

    /**
     * @brief Megnézi hogy a file üres e.
     *
     * @param file Fájl neve
     * @return Igazat ad ha a file üres, egylbként hamis;
     */
    static bool fileEmpty(const String &file);
};

#endif // PHONEBOOK_CONTACTS_H
