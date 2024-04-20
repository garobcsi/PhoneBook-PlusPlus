#ifndef PHONEBOOK_CONTACT_H
#define PHONEBOOK_CONTACT_H

#include "../lib/memtrace.h"
#include "./string.h"
#include "./array.h"

class Contact
{
    String _firstName = "";
    String _lastName = "";
    String _nickname = "";
    String _address = "";
    String _workNumber = "";
    String _privateNumber = "";

    bool isPhoneNumber(const String &str) const;

public:
    Contact();
    Contact(const Contact &c);
    Contact(const String &firstName,
            const String &lastName,
            const String &nickname,
            const String &address,
            const String &workNumber,
            const String &privateNumber);

    Contact &operator=(const Contact &rhs);

    const String &getFirstName() const;
    void setFirstName(const String &firstName);
    const String &getLastName() const;
    void setLastName(const String &lastName);
    const String &getNickname() const;
    void setNickname(const String &nickname);
    const String &getAddress() const;
    void setAddress(const String &address);
    const String &getWorkNumber() const;
    void setWorkNumber(const String &workNumber);
    const String &getPrivateNumber() const;
    void setPrivateNumber(const String &privateNumber);

    friend std::ostream &operator<<(std::ostream &os, const Contact &c);
    friend std::istream &operator>>(std::istream &is, Contact &c);
};

#endif // PHONEBOOK_CONTACT_H
