#ifndef PHONEBOOK_CONTACTS_H
#define PHONEBOOK_CONTACTS_H

#include "../lib/memtrace.h"
#include "array.h"
#include "contact.h"

class Contacts : public Array<Contact>
{

public:
    Contacts();
    Contacts(const Contacts &a);
    Contacts(std::initializer_list<Contact> list);

    void loadFile(const String &fileName);

    void saveFile(const String &fileName);
};

#endif // PHONEBOOK_CONTACTS_H
