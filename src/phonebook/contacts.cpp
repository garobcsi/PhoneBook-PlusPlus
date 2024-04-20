#include "../lib/memtrace.h"
#include "contacts.h"
#include <iostream>
#include <fstream>

Contacts::Contacts() : Array<Contact>() {}
Contacts::Contacts(const Contacts &a) : Array<Contact>(a) {}
Contacts::Contacts(std::initializer_list<Contact> list) : Array<Contact>(list) {}

void Contacts::loadFile(const String &fileName) {
    std::ifstream file(fileName.c_str());
    
    Contact c;
    while (file >> c) {
        pushBack(c);
    }
    file.close();
}

void Contacts::saveFile(const String &fileName) {
    std::ofstream file(fileName.c_str());
    for(const Contact &i : *this) {
        file << i;
    }
    file.close();
}
