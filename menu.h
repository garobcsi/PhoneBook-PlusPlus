#ifndef PHONEBOOK_MENU_H
#define PHONEBOOK_MENU_H

#include <iostream>
#include <functional>
#include <exception>
#include "./memtrace.h"

class Menu
{
    std::function<int()> func = nullptr;

public:
    template <typename F>
    void Create(F function);
    int Render();

    static int Clear();
};

template <typename F>
void Menu::Create(F function)
{
    func = function;
}
#endif // PHONEBOOK_MENU_H
