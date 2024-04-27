#include "./memtrace.h"
#include "contacts.h"
#include <iostream>
#include <fstream>

Contacts::Contacts() : Array<Contact>() {}
Contacts::Contacts(const Contacts &a) : Array<Contact>(a) {}
Contacts::Contacts(std::initializer_list<Contact> list) : Array<Contact>(list) {}

Contacts &Contacts::operator=(const Contacts &rhs)
{
    if (this != &rhs)
    {
        clear();
        for (const Contact &contact : rhs)
        {
            pushBack(contact);
        }
    }
    return *this;
}

void Contacts::loadFile(const String &fileName)
{
    clear();
    std::ifstream file(fileName.c_str());
    if (file.peek() == std::ifstream::traits_type::eof()) throw std::runtime_error("Contacts: File is empty!");
    if (!file.good()) throw std::runtime_error("Contacts: Unable to open file!");
    Contact c;
    while (file >> c)
    {
        pushBack(c);
    }
    file.close();
}

void Contacts::saveFile(const String &fileName)
{
    std::ofstream file(fileName.c_str());
    if (!file.good()) throw std::runtime_error("Contacts: Unable to open file!");
    for (size_t i = 0; i < size(); ++i)
    {
        if (i != 0)
            file << "\n";
        file << this->operator[](i);
    }
    file.close();
}

bool Contacts::fileExists(const String &file) {
    std::ifstream f(file.c_str());
    return f.good();
}