#ifndef PHONEBOOK_MENU_H
#define PHONEBOOK_MENU_H

#include <iostream>
#include <functional>
#include <exception>
#include "./memtrace.h"

/**
 * @class Menu
 * @brief Menü osztály.
 * 
 * A Menu osztály egy menüt reprezentál, amely egy megadott függvényt hajt végre.
 */
class Menu
{
    /**
     * @brief A menü által végrehajtandó függvény.
     */
    std::function<int()> func = nullptr;

public:
    /**
     * @brief Konstruktor létrehoz egy új Menu objektumot.
     * 
     * @tparam F A függvény típusa.
     * @param function A menü által végrehajtandó függvény.
     */
    template <typename F>
    void Create(F function);

    /**
     * @brief Menü kirajzolása.
     * 
     * @return A menü által végrehajtott függvény visszatérési értéke. Ha hivásan fut le a fügvény akkor 1 a visszatérési érték, egyébként 0.
     */
    int Render();

    /**
     * @brief Kijező törlése.
     * 
     * @return Hibakód visszaadása.
     */
    static int Clear();
};

template <typename F>
void Menu::Create(F function)
{
    func = function;
}
#endif // PHONEBOOK_MENU_H
