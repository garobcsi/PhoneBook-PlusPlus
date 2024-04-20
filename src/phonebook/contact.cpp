#include "../lib/memtrace.h"
#include "contact.h"

#include <regex>

Contact::Contact() : _firstName(""), _lastName(""), _nickname(""), _address(""), _workNumber(""), _privateNumber("") {}

Contact::Contact(const Contact &c)
{
    setFirstName(c.getFirstName());
    setLastName(c.getLastName());
    setNickname(c.getNickname());
    setAddress(c.getAddress());
    setWorkNumber(c.getWorkNumber());
    setPrivateNumber(c.getPrivateNumber());
}

Contact::Contact(const String &firstName, const String &lastName, const String &nickname, const String &address,
                 const String &workNumber, const String &privateNumber)
{
    setFirstName(firstName);
    setLastName(lastName);
    setNickname(nickname);
    setAddress(address);
    setWorkNumber(workNumber);
    setPrivateNumber(privateNumber);
}

Contact &Contact::operator=(const Contact &rhs)
{
    if (this != &rhs)
    {
        setFirstName(rhs.getFirstName());
        setLastName(rhs.getLastName());
        setNickname(rhs.getNickname());
        setAddress(rhs.getAddress());
        setWorkNumber(rhs.getWorkNumber());
        setPrivateNumber(rhs.getPrivateNumber());
    }
    return *this;
}

const String &Contact::getFirstName() const
{
    return _firstName;
}

const String &Contact::getLastName() const
{
    return _lastName;
}

const String &Contact::getNickname() const
{
    return _nickname;
}

const String &Contact::getAddress() const
{
    return _address;
}

const String &Contact::getWorkNumber() const
{
    return _workNumber;
}

const String &Contact::getPrivateNumber() const
{
    return _privateNumber;
}

void Contact::setFirstName(const String &firstName)
{
    _firstName = firstName;
}

void Contact::setLastName(const String &lastName)
{
    _lastName = lastName;
}

void Contact::setNickname(const String &nickname)
{
    _nickname = nickname;
}

void Contact::setAddress(const String &address)
{
    _address = address;
}

void Contact::setWorkNumber(const String &workNumber)
{
    if (isPhoneNumber(workNumber) || workNumber.size() == 0)
        _workNumber = workNumber;
    else
        throw std::invalid_argument("Contact: not a phone number");
}

void Contact::setPrivateNumber(const String &privateNumber)
{
    if (isPhoneNumber(privateNumber) || privateNumber.size() == 0)
        _privateNumber = privateNumber;
    else
        throw std::invalid_argument("Contact: not a phone number");
}

bool Contact::operator==(const Contact &rhs) const {
    return (_firstName == rhs._firstName &&
            _lastName == rhs._lastName &&
            _nickname == rhs._nickname &&
            _address == rhs._address &&
            _workNumber == rhs._workNumber &&
            _privateNumber == rhs._privateNumber);
}

bool Contact::operator!=(const Contact &rhs) const {
    return !(*this == rhs);
}

std::ostream &operator<<(std::ostream &os, const Contact &c)
{
    os << c.getFirstName().c_str() << ";" << c.getLastName().c_str() << ";" << c.getNickname().c_str() << ";" << c.getAddress().c_str() << ";" << c.getWorkNumber().c_str() << ";" << c.getPrivateNumber().c_str();
    return os;
}

std::istream &operator>>(std::istream &is, Contact &c)
{
    String s;
    is >> std::noskipws;
    is >> s;
    if (s[0] == '\377')
    { /*(char) EOF -1*/
        is.setstate(std::ios::eofbit);
        return is;
    }
    if (is.eof())
    {
        is.clear();
        is.putback(EOF);
    }
    Array<String> arr = s.split(';');
    if (arr.size() != 6)
        return is;
    c.setFirstName(arr[0]);
    c.setLastName(arr[1]);
    c.setNickname(arr[2]);
    c.setAddress(arr[3]);
    c.setWorkNumber(arr[4]);
    c.setPrivateNumber(arr[5]);
    return is;
}

bool Contact::isPhoneNumber(const String &str)
{
    /*
     * https://regexper.com/#%5E%5C%2B%3F%28%3F%3A36%7C06%29%5B0-9%5D%7B7%2C%7D%24
     * Elfogadott formátum: +301236479 vagy 06301236479
     */
    std::regex phonePattern("^\\+?(?:36|06)[0-9]{7,}$");

    return std::regex_match(str.c_str(), phonePattern);
}