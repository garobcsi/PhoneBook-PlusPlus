#ifndef PHONEBOOK_CONTACTS_H
#define PHONEBOOK_CONTACTS_H

#include "../lib/memtrace.h"
#include "array.h"
#include "contact.h"

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

    Contacts &operator=(const Contacts &rhs);

    /**
     * @brief Betölti a kapcsolatokat egy fájlból.
     * 
     * @param fileName A betöltendő fájl elérési útja.
     */
    void loadFile(const String &fileName);

    /**
     * @brief Menti a kapcsolatokat egy fájlba.
     * 
     * @param fileName A mentendő fájl elérési útja.
     */
    void saveFile(const String &fileName);
};

#endif // PHONEBOOK_CONTACTS_H
