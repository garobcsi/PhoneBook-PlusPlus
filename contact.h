#ifndef PHONEBOOK_CONTACT_H
#define PHONEBOOK_CONTACT_H

#include "./memtrace.h"
#include "./string.h"
#include "./array.h"

/**
 * @class Contact
 * @brief Egy darab személnek a telefonszámát és adatait tárolja el.
 *
 * A Contact biztositani fogja hogy csakis jó értékek kerülhessenek a objectumba
 */
class Contact
{
    /**
     * @brief Vezetéknevet tároló string objectum
     *
     */
    String _firstName = "";
    /**
     * @brief Utónevet tároló string objectum
     *
     */
    String _lastName = "";
    /**
     * @brief Becenevet tároló string objectum
     *
     */
    String _nickname = "";
    /**
     * @brief Címet tároló string objectum
     * 
     */
    String _address = "";
    /**
     * @brief Munka telefonszámot tároló string objectum
     * 
     */
    String _workNumber = "";
    /**
     * @brief Személyes telefonszámot tároló string objectum
     * 
     */
    String _privateNumber = "";

public:
    /**
     * @brief Alapértelmezett konstruktor létrehoz egy üres kapcsolatot.
     */
    Contact();

    /**
     * @brief Másoló konstruktor, ami létrehoz egy új kapcsolatot az adott kapcsolat alapján.
     *
     * @param c A másolás alapjául szolgáló kapcsolat.
     */
    Contact(const Contact &c);

    /**
     * @brief Konstruktor, ami létrehoz egy kapcsolatot a megadott adatok alapján.
     *
     * @param firstName A keresztnév.
     * @param lastName A vezetéknév.
     * @param nickname A becenév.
     * @param address A cím.
     * @param workNumber A munkahelyi telefonszám.
     * @param privateNumber A magán telefonszám.
     */
    Contact(const String &firstName,
            const String &lastName,
            const String &nickname,
            const String &address,
            const String &workNumber,
            const String &privateNumber);

    /**
     * @brief Másoló értékadás operátor, ami másolja a jobb oldali kapcsolatot a bal oldalira.
     *
     * @param rhs A másolandó kapcsolat.
     * @return Az újra létrehozott kapcsolat referenciája.
     */
    Contact &operator=(const Contact &rhs);

    /**
     * @brief Visszaadja a keresztnevet.
     *
     * @return A keresztnév.
     */
    const String &getFirstName() const;

    /**
     * @brief Beállítja a keresztnevet.
     *
     * @param firstName Az új keresztnév.
     */
    void setFirstName(const String &firstName);

    /**
     * @brief Visszaadja a vezetéknevet.
     *
     * @return A vezetéknév.
     */
    const String &getLastName() const;

    /**
     * @brief Beállítja a vezetéknevet.
     *
     * @param lastName Az új vezetéknév.
     */
    void setLastName(const String &lastName);

    /**
     * @brief Visszaadja a becenévet.
     *
     * @return A becenév.
     */
    const String &getNickname() const;

    /**
     * @brief Beállítja a becenévet.
     *
     * @param nickname Az új becenév.
     */
    void setNickname(const String &nickname);

    /**
     * @brief Visszaadja a címet.
     *
     * @return A cím.
     */
    const String &getAddress() const;

    /**
     * @brief Beállítja a címet.
     *
     * @param address Az új cím.
     */
    void setAddress(const String &address);

    /**
     * @brief Visszaadja a munkahelyi telefonszámot.
     *
     * @return A munkahelyi telefonszám.
     */
    const String &getWorkNumber() const;

    /**
     * @brief Beállítja a munkahelyi telefonszámot.
     *
     * @param workNumber Az új munkahelyi telefonszám.
     * @throw std::invalid_argument Ha a megadott szám nem telefonszám formátumú.
     */
    void setWorkNumber(const String &workNumber);

    /**
     * @brief Visszaadja a magán telefonszámot.
     *
     * @return A magán telefonszám.
     */
    const String &getPrivateNumber() const;

    /**
     * @brief Beállítja a magán telefonszámot.
     *
     * @param privateNumber Az új magán telefonszám.
     * @throw std::invalid_argument Ha a megadott szám nem telefonszám formátumú.
     */
    void setPrivateNumber(const String &privateNumber);

    /**
     * @brief Ellenőrzi, hogy két kapcsolat egyenlő-e.
     *
     * Két kapcsolat akkor egyenlő, ha minden adattagjuk megegyezik.
     *
     * @param rhs Az összehasonlítandó kapcsolat.
     * @return Igaz, ha a két kapcsolat egyenlő, egyébként hamis.
     */
    bool operator==(const Contact &rhs) const;

    /**
     * @brief Ellenőrzi, hogy két kapcsolat nem egyenlő-e.
     *
     * Két kapcsolat akkor nem egyenlő, ha legalább egy adattagjuk eltér egymástól.
     *
     * @param rhs Az összehasonlítandó kapcsolat.
     * @return Igaz, ha a két kapcsolat nem egyenlő, egyébként hamis.
     */
    bool operator!=(const Contact &rhs) const;

    /**
     * @brief Kimenetként formázza a kapcsolatot. (csv formátumba)
     *
     * @param os A kimeneti stream.
     * @param c A formázandó kapcsolat.
     * @return A formázott kimeneti stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Contact &c);

    /**
     * @brief Bemenetként beolvassa a kapcsolatot. (csv formátumba)
     *
     * @param is A bemeneti stream.
     * @param c A beolvasandó kapcsolat.
     * @return A beolvasott bemeneti stream.
     */
    friend std::istream &operator>>(std::istream &is, Contact &c);

    /**
     * @brief Ellenőrzi, hogy a megadott string telefonszám-e.
     * https://regexper.com/#%5E%5C%2B%3F%28%3F%3A36%7C06%29%5B0-9%5D%7B7%2C%7D%24
     * Elfogadott formátum: +301236479 vagy 06301236479
     * @param str A vizsgálandó string.
     * @return Igaz, ha a string telefonszám, egyébként hamis.
     */
    static bool isPhoneNumber(const String &str);
};

#endif // PHONEBOOK_CONTACT_H
