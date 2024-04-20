#include "../lib/memtrace.h"
#include "contacts.h"
#include <iostream>
#include <fstream>

Contacts::Contacts() : Array<Contact>() {}
Contacts::Contacts(const Contacts &a) : Array<Contact>(a) {}
Contacts::Contacts(std::initializer_list<Contact> list) : Array<Contact>(list) {}

Contacts &Contacts::operator=(const Contacts &rhs) {
    if (this != &rhs) {
        clear();
        for (const Contact &contact : rhs) {
            pushBack(contact);
        }
    }
    return *this;
}

void Contacts::loadFile(const String &fileName) {
    clear();
    std::ifstream file(fileName.c_str());
    
    Contact c;
    while (file >> c) {
        pushBack(c);
    }
    file.close();
}

void Contacts::saveFile(const String &fileName) {
    std::ofstream file(fileName.c_str());
    for (size_t i = 0; i < size(); ++i) {
        if (i != 0) file << "\n";
        file << this->operator[](i);
    }
    file.close();
}