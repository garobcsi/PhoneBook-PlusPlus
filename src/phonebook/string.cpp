#include <iostream>
#include <cstring>

#include "../lib/memtrace.h"
#include "./string.h"

String::String(char c) : str(new char[2]), len(1)
{
    str[0] = c;
    str[1] = '\0';
}

String::String(const char *p) : str(new char[strlen(p) + 1]), len(strlen(p))
{
    strcpy(str, p);
}

String::String(const String &s) : str(new char[s.len + 1]), len(s.len)
{
    strcpy(str, s.str);
}

String::~String()
{
    delete[] str;
}

size_t String::size() const
{
    return len;
}

const char *String::c_str() const
{
    return str;
}

String &String::operator=(const String &rhs)
{
    if (this != &rhs)
    {
        delete[] str;
        len = rhs.len;
        str = new char[len + 1];
        strcpy(str, rhs.str);
    }
    return *this;
}

String String::operator+(const String &rhs) const
{
    String temp;
    temp.len = len + rhs.len;
    delete[] temp.str;
    temp.str = new char[temp.len + 1];
    strcpy(temp.str, str);
    strcat(temp.str, rhs.str);

    return temp;
}

String String::operator+(char rhs) const
{
    return *this + String(rhs);
}

char &String::operator[](unsigned int index)
{
    if (index >= len)
        throw std::out_of_range("String: out of range");
    return str[index];
}

const char &String::operator[](unsigned int index) const
{
    if (index >= len)
        throw std::out_of_range("String: out of range");
    return str[index];
}

bool String::operator<(const String& rhs) const {
    return std::strcmp(str, rhs.str) < 0;
}

bool String::operator==(const String& rhs) const {
    return std::strcmp(str, rhs.str) == 0;
}

std::ostream &operator<<(std::ostream &os, const String &s)
{
    os << s.c_str();
    return os;
}

std::istream &operator>>(std::istream &is, String &s)
{
    unsigned char ch;
    s = String("");
    std::ios_base::fmtflags fl = is.flags();
    is.setf(std::ios_base::skipws);
    while (is >> ch)
    {
        is.unsetf(std::ios_base::skipws);
        if (isspace(ch))
        {
            is.putback(ch);
            break;
        }
        else
            s = s + ch;
    }
    is.setf(fl);
    return is;
}

String operator+(char lhs, const String &rhs)
{
    return String(lhs) + rhs;
}
