#ifndef PHONEBOOK_STRING_H
#define PHONEBOOK_STRING_H

class String
{
    char *str;
    size_t len;

public:
    explicit String(char c);

    explicit String(const char *p = "");

    String(const String &s);

    virtual ~String();

    size_t size() const;

    const char *c_str() const;

    String &operator=(const String &rhs);

    String operator+(const String &rhs) const;

    String operator+(char rhs) const;

    char &operator[](unsigned int index);

    const char &operator[](unsigned int index) const;

    friend std::ostream &operator<<(std::ostream &os, const String &s);

    friend std::istream &operator>>(std::istream &is, String &s);

    friend inline String operator+(char lhs, const String &rhs);
};

#endif // PHONEBOOK_STRING_H