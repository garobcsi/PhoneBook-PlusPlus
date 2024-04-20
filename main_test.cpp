#include "src/lib/memtrace.h"
#include "src/lib/gtest_lite.h"
#include "src/phonebook/string.h"
#include "src/phonebook/array.h"
#include "src/phonebook/contact.h"
#include "src/phonebook/contacts.h"

int main()
{
    /* STRING CLASS TESTS */
    {
        TEST(String, DefaultConstructorTest)
        {
            String s;
            EXPECT_STREQ("", s.c_str());
            EXPECT_EQ((size_t)0, s.size());
        }
        END

        TEST(String, CharConstructorTest)
        {
            String s('a');
            EXPECT_EQ((size_t)1, s.size());
            EXPECT_STREQ("a", s.c_str());
        }
        END

        TEST(String, CharArrayConstructorTest)
        {
            String s("hello");
            EXPECT_EQ((size_t)5, s.size());
            EXPECT_STREQ("hello", s.c_str());
        }
        END

        TEST(String, CopyConstructorTest)
        {
            String s1("hello");
            const String &s2(s1);
            EXPECT_EQ((size_t)5, s2.size());
            EXPECT_STREQ("hello", s2.c_str());
        }
        END

        TEST(String, CopyConstructorTest)
        {
            String s1("hello");
            String s2(s1);

            EXPECT_EQ((size_t)5, s2.size());
            EXPECT_STREQ("hello", s2.c_str());

            s1[0] = 'H';
            EXPECT_STREQ("Hello", s1.c_str());
            EXPECT_STREQ("hello", s2.c_str());
        }
        END

        TEST(String, SizeTest)
        {
            String s("hello");
            EXPECT_EQ((size_t)5, s.size());
        }
        END
        TEST(String, CStrTest)
        {
            String s("hello");
            EXPECT_STREQ("hello", s.c_str());
        }
        END

        TEST(String, AssignmentOperatorTest)
        {
            String s1("hello");
            String s2;
            s2 = s1;
            EXPECT_EQ((size_t)5, s2.size());
            EXPECT_STREQ("hello", s2.c_str());
        }
        END

        TEST(String, PlusOperatorStringTest)
        {
            String s1("hello");
            String s2(" world");
            String result = s1 + s2;
            EXPECT_EQ((size_t)11, result.size());
            EXPECT_STREQ("hello world", result.c_str());
        }
        END

        TEST(String, PlusOperatorCharTest)
        {
            String s("hello");
            char c = '!';
            String result = s + c;
            EXPECT_EQ((size_t)6, result.size());
            EXPECT_STREQ("hello!", result.c_str());
        }
        END

        TEST(String, IndexOperatorTest)
        {
            String s("hello");
            EXPECT_EQ('h', s[0]);
            EXPECT_EQ('o', s[4]);

            EXPECT_THROW(s[5], std::out_of_range &);
        }
        END

        TEST(String, ConstIndexOperatorTest)
        {
            const String s("hello");
            EXPECT_EQ('h', s[0]);
            EXPECT_EQ('o', s[4]);

            EXPECT_THROW(s[5], std::out_of_range &);
        }
        END

        TEST(String, OutputOperatorTest)
        {
            String s("hello");
            std::stringstream ss;
            ss << s;
            EXPECT_STREQ("hello", ss.str().c_str());
        }
        END

        TEST(String, InputOperatorTest)
        {
            String s;
            std::stringstream ss("hello");
            ss >> s;
            EXPECT_EQ((size_t)5, s.size());
            EXPECT_STREQ("hello", s.c_str());
        }
        END

        TEST(String, InputOperatorTestWithSpaces)
        {
            String s;
            std::stringstream ss("hello                 world");
            ss >> std::noskipws;
            ss >> std::skipws;
            ss >> s;
            EXPECT_EQ((size_t)5, s.size());
            EXPECT_STREQ("hello", s.c_str());
            ss >> s;
            EXPECT_EQ((size_t)5, s.size());
            EXPECT_STREQ("world", s.c_str());
        }
        END

        TEST(String, InputTestWhitespaces(std::noskipws))
        {
            String s;
            std::stringstream ss("hello                 world");
            ss >> std::noskipws;
            ss >> s;
            EXPECT_EQ((size_t)27, s.size());
            EXPECT_STREQ("hello                 world", s.c_str());
        }
        END
        TEST(String, InputTestWhitespaces(std::noskipws) 2)
        {
            String s;
            std::stringstream ss("hello                 world\nnew line");
            ss >> std::noskipws;
            ss >> s;
            EXPECT_EQ((size_t)27, s.size());
            EXPECT_STREQ("hello                 world", s.c_str());
            ss >> s;
            EXPECT_EQ((size_t)8, s.size());
            EXPECT_STREQ("new line", s.c_str());
            Array<String> arr = s.split(' ');
            EXPECT_STREQ("new", arr[0].c_str());
            EXPECT_STREQ("line", arr[1].c_str());
        }
        END

        TEST(String, PlusOperatorCharLeftTest)
        {
            char c = '!';
            String s("hello");
            String result = c + s;
            EXPECT_EQ((size_t)6, result.size());
            EXPECT_STREQ("!hello", result.c_str());
        }
        END

        TEST(String, OperatorLessThan)
        {
            String s1("apple");
            String s2("banana");

            EXPECT_TRUE(s1 < s2);
            EXPECT_FALSE(s2 < s1);
        }
        END

        TEST(String, OperatorEquals)
        {
            String s1("apple");
            String s2("apple");
            String s3("banana");

            EXPECT_TRUE(s1 == s2);
            EXPECT_FALSE(s1 == s3);
        }
        END

        TEST(String, MixedComparisons)
        {
            String s1("apple");
            String s2("banana");

            EXPECT_TRUE(s1 < s2);
            EXPECT_FALSE(s1 == s2);
        }
        END

        TEST(String, Split)
        {
            String str = ";a;b;hello world;";
            Array<String> arr = str.split(';');

            EXPECT_STREQ("", arr[0].c_str());
            EXPECT_STREQ("a", arr[1].c_str());
            EXPECT_STREQ("b", arr[2].c_str());
            EXPECT_STREQ("hello world", arr[3].c_str());
            EXPECT_STREQ("", arr[4].c_str());
            EXPECT_THROW(arr[5], std::out_of_range &);
        }
        END

        TEST(String, Split2)
        {
            String str = "a;b;hello world";
            Array<String> arr = str.split(';');

            EXPECT_STREQ("a", arr[0].c_str());
            EXPECT_STREQ("b", arr[1].c_str());
            EXPECT_STREQ("hello world", arr[2].c_str());
            EXPECT_THROW(arr[3], std::out_of_range &);
        }
        END

        /*STRING ITERATOR CLASS TESTS*/
        {
            TEST(StringIteratorTest, BeginAndEnd)
            {
                String s("hello");
                String::Iterator it = s.begin();
                EXPECT_EQ('h', *it);

                it = s.end();
                EXPECT_NE('o', *it);
            }
            END

            TEST(StringIteratorTest, ReverseBegin)
            {
                String s("hello");
                String::Iterator it = s.rbegin();
                EXPECT_EQ('o', *it);
            }
            END

            TEST(StringIteratorTest, IncrementAndDecrement)
            {
                String s("hello");
                String::Iterator it = s.begin();

                ++it;
                EXPECT_EQ('e', *it);

                --it;
                EXPECT_EQ('h', *it);
            }
            END

            TEST(StringIteratorTest, EqualityAndInequality)
            {
                String s("hello");
                String::Iterator it1 = s.begin();
                String::Iterator it2 = s.begin();
                String::Iterator it3 = s.end();

                EXPECT_TRUE(it1 == it2);
                EXPECT_FALSE(it1 != it2);

                EXPECT_FALSE(it1 == it3);
                EXPECT_TRUE(it1 != it3);
            }
            END

            TEST(StringIteratorTest, ForLoop1)
            {
                String s = "hello world";
                int count = 0;
                for (char i : s)
                {
                    EXPECT_EQ(s[count], i);
                    count++;
                }
            }
            END

            TEST(StringIteratorTest, ForLoop2)
            {
                String s = "hello world";
                int count = 0;
                for (auto i = s.begin(); i != s.end(); i++)
                {
                    EXPECT_EQ(s[count], *i);
                    count++;
                }
            }
            END

            TEST(StringIteratorTest, ForLoop3)
            {
                String s = "hello world";
                int count = (int)s.size();
                for (auto i = s.rbegin(); i != s.rend(); i--)
                {
                    EXPECT_EQ(s[count - 1], *i);
                    count--;
                }
            }
            END
        }
    }

    /* ARRAY CLASS TESTS */
    {
        TEST(Array, ConstructorAndSize)
        {
            Array<int> arr;
            EXPECT_EQ((size_t)0, arr.size());
        }
        END

        TEST(Array, PushBack)
        {
            Array<int> arr;
            arr.pushBack(5);
            EXPECT_EQ((size_t)1, arr.size());
            EXPECT_EQ(5, arr[0]);
        }
        END

        TEST(Array, RemoveEl)
        {
            Array<int> arr;
            arr.pushBack(5);
            arr.pushBack(10);
            arr.removeEl(0);
            EXPECT_EQ((size_t)1, arr.size());
            EXPECT_EQ(10, arr[0]);
        }
        END

        TEST(Array, OrderBy)
        {
            Array<int> arr;
            arr.pushBack(5);
            arr.pushBack(3);
            arr.pushBack(8);
            arr.orderBy(std::less<int>());
            EXPECT_EQ(3, arr[0]);
            EXPECT_EQ(5, arr[1]);
            EXPECT_EQ(8, arr[2]);
        }
        END

        TEST(Array, AssignmentOperator)
        {
            Array<int> arr1;
            arr1.pushBack(5);
            Array<int> arr2;
            arr2 = arr1;
            EXPECT_EQ((size_t)1, arr2.size());
            EXPECT_EQ(5, arr2[0]);
        }
        END

        TEST(Array, SubscriptOperator)
        {
            Array<int> arr;
            arr.pushBack(5);
            arr.pushBack(10);
            EXPECT_EQ(5, arr[0]);
            EXPECT_EQ(10, arr[1]);
        }
        END

        TEST(Array, ConstCorrectness)
        {
            const Array<int> arr;
            EXPECT_EQ((size_t)0, arr.size());
        }
        END

        TEST(Array, ConstSubscriptOperator)
        {
            Array<int> arr;
            arr.pushBack(5);
            const Array<int> &constArr = arr;
            EXPECT_EQ(5, constArr[0]);
        }
        END

        TEST(Array, CopyConstruct)
        {
            Array<int> arr;
            arr.pushBack(5);
            const Array<int> constArr(arr);
            EXPECT_EQ(5, constArr[0]);
        }
        END

        TEST(Array, ConstSize)
        {
            Array<int> arr;
            arr.pushBack(5);
            const Array<int> &constArr = arr;
            EXPECT_EQ((size_t)1, constArr.size());
        }
        END

        TEST(Array, ArrayInArray)
        {
            Array<Array<Array<Array<Array<String>>>>> arr;
            arr.pushBack(Array<Array<Array<Array<String>>>>());
            arr[0].pushBack(Array<Array<Array<String>>>());
            arr[0][0].pushBack(Array<Array<String>>());
            arr[0][0][0].pushBack(Array<String>());
            arr[0][0][0][0].pushBack(String("world"));
            arr[0][0][0][0].pushBack(String("Hello"));
            EXPECT_STREQ("world", arr[0][0][0][0][0].c_str());
            EXPECT_STREQ("Hello", arr[0][0][0][0][1].c_str());
            arr[0][0][0][0].orderBy(std::less<String>());
            EXPECT_STREQ("Hello", arr[0][0][0][0][0].c_str());
            EXPECT_STREQ("world", arr[0][0][0][0][1].c_str());
            arr.removeEl(0);
            EXPECT_THROW(arr[0][0][0][0][0], std::out_of_range &);
        }
        END

        TEST(Array, ArrayInArrayInArrayInArrayInArrayInArrayInArray)
        {
            Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<String>>>>>>>>>>>>>>>>>> arr;
            arr.pushBack(Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<String>>>>>>>>>>>>>>>>>());
            arr[0].pushBack(Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<String>>>>>>>>>>>>>>>>());
            arr[0][0].pushBack(Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<String>>>>>>>>>>>>>>>());
            arr[0][0][0].pushBack(Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<String>>>>>>>>>>>>>>());
            arr[0][0][0][0].pushBack(Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<String>>>>>>>>>>>>>());
            arr[0][0][0][0][0].pushBack(Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<String>>>>>>>>>>>>());
            arr[0][0][0][0][0][0].pushBack(Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<String>>>>>>>>>>>());
            arr[0][0][0][0][0][0][0].pushBack(Array<Array<Array<Array<Array<Array<Array<Array<Array<Array<String>>>>>>>>>>());
            arr[0][0][0][0][0][0][0][0].pushBack(Array<Array<Array<Array<Array<Array<Array<Array<Array<String>>>>>>>>>());
            arr[0][0][0][0][0][0][0][0][0].pushBack(Array<Array<Array<Array<Array<Array<Array<Array<String>>>>>>>>());
            arr[0][0][0][0][0][0][0][0][0][0].pushBack(Array<Array<Array<Array<Array<Array<Array<String>>>>>>>());
            arr[0][0][0][0][0][0][0][0][0][0][0].pushBack(Array<Array<Array<Array<Array<Array<String>>>>>>());
            arr[0][0][0][0][0][0][0][0][0][0][0][0].pushBack(Array<Array<Array<Array<Array<String>>>>>());
            arr[0][0][0][0][0][0][0][0][0][0][0][0][0].pushBack(Array<Array<Array<Array<String>>>>());
            arr[0][0][0][0][0][0][0][0][0][0][0][0][0][0].pushBack(Array<Array<Array<String>>>());
            arr[0][0][0][0][0][0][0][0][0][0][0][0][0][0][0].pushBack(Array<Array<String>>());
            arr[0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0].pushBack(Array<String>());
            arr[0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0].pushBack(String("HELLO WORLD !"));
            EXPECT_STREQ("HELLO WORLD !", arr[0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0].c_str());
            arr.removeEl(0);
            EXPECT_THROW(arr[0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0][0], std::out_of_range &);
        }
        END

        TEST(Array, initializer_list<int>)
        {
            Array<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
            for (int i = 0; i < (int)arr.size(); ++i)
            {
                EXPECT_EQ(i + 1, arr[i]);
            }
        }
        END

        TEST(Array, initializer_list<String>)
        {
            Array<String> arr = {"a", "b", "c", "d", "e", "f", "g", "h"};
            EXPECT_STREQ("a", arr[0].c_str());
            EXPECT_STREQ("b", arr[1].c_str());
            EXPECT_STREQ("c", arr[2].c_str());
            EXPECT_STREQ("d", arr[3].c_str());
            EXPECT_STREQ("e", arr[4].c_str());
            EXPECT_STREQ("f", arr[5].c_str());
            EXPECT_STREQ("g", arr[6].c_str());
            EXPECT_STREQ("h", arr[7].c_str());
            arr.removeEl(0);
            EXPECT_THROW(arr[7].c_str(), std::out_of_range &);
            EXPECT_STREQ("b", arr[0].c_str());
            EXPECT_STREQ("h", arr[6].c_str());
        }
        END

        TEST(Array, where)
        {
            Array<String> arr = {"ab", "ac", "ad", "d", "e", "af", "g", "h"};
            Array<String> arr_where = arr.where([](String el)
                                                { return el[0] == 'a'; });
            EXPECT_STREQ("ab", arr_where[0].c_str());
            EXPECT_STREQ("ac", arr_where[1].c_str());
            EXPECT_STREQ("ad", arr_where[2].c_str());
            EXPECT_STREQ("af", arr_where[3].c_str());
            EXPECT_THROW(arr_where[4].c_str(), std::out_of_range &);

            EXPECT_STREQ("ab", arr[0].c_str());
            EXPECT_STREQ("ac", arr[1].c_str());
            EXPECT_STREQ("ad", arr[2].c_str());
            EXPECT_STREQ("d", arr[3].c_str());
            EXPECT_STREQ("e", arr[4].c_str());
            EXPECT_STREQ("af", arr[5].c_str());
            EXPECT_STREQ("g", arr[6].c_str());
            EXPECT_STREQ("h", arr[7].c_str());
            EXPECT_THROW(arr[8].c_str(), std::out_of_range &);
        }
        END

        /*ARRAY ITERATOR CLASS TESTS*/
        {
            TEST(ArrayIteratorTest, IteratorTest)
            {

                Array<int> arr = {1, 2, 3};

                Array<int>::Iterator it = arr.begin();
                EXPECT_EQ(1, *it);

                ++it;
                EXPECT_EQ(2, *it);

                it++;
                EXPECT_EQ(3, *it);

                ++it;
                EXPECT_TRUE(it == arr.end());

                const Array<int> &constArr = arr;
                Array<int>::Iterator cit = constArr.begin();
                EXPECT_EQ(1, *cit);

                ++cit;
                EXPECT_EQ(2, *cit);

                cit++;
                EXPECT_EQ(3, *cit);

                ++cit;
                EXPECT_TRUE(cit == constArr.end());
            }
            END

            TEST(ArrayIteratorTest, ForLoop1)
            {
                Array<int> arr = {1, 2, 3};
                int count = 0;
                for (auto i : arr)
                {
                    count++;
                    EXPECT_EQ(count, i);
                }
            }
            END

            TEST(ArrayIteratorTest, ForLoop2)
            {
                Array<int> arr = {1, 2, 3};
                int count = 0;
                for (auto i = arr.begin(); i != arr.end(); i++)
                {
                    count++;
                    EXPECT_EQ(count, *i);
                }
            }
            END

            TEST(ArrayIteratorTest, ForLoop3)
            {
                Array<int> arr = {1, 2, 3};
                int count = 3;
                for (auto i = arr.rbegin(); i != arr.rend(); i--)
                {
                    EXPECT_EQ(count, *i);
                    count--;
                }
            }
            END

            TEST(Array, clear)
            {
                Array<int> arr = {1, 2, 4, 5, 6};
                arr.clear();
                EXPECT_EQ((size_t)0, arr.size());
                EXPECT_THROW(arr[0], std::out_of_range &);
            }
            END
        }
    }

    /*CONTACT CLASS TESTS*/
    {
        TEST(ContactTest, DefaultConstructor)
        {
            Contact contact;
            EXPECT_STREQ("", contact.getFirstName().c_str());
            EXPECT_STREQ("", contact.getLastName().c_str());
            EXPECT_STREQ("", contact.getNickname().c_str());
            EXPECT_STREQ("", contact.getAddress().c_str());
            EXPECT_STREQ("", contact.getWorkNumber().c_str());
            EXPECT_STREQ("", contact.getPrivateNumber().c_str());
        }
        END

        TEST(ContactTest, ParameterizedConstructor)
        {
            Contact contact("John", "Doe", "JD", "123 Main St", "+363452345", "06707654321");
            EXPECT_STREQ("John", contact.getFirstName().c_str());
            EXPECT_STREQ("Doe", contact.getLastName().c_str());
            EXPECT_STREQ("JD", contact.getNickname().c_str());
            EXPECT_STREQ("123 Main St", contact.getAddress().c_str());
            EXPECT_STREQ("+363452345", contact.getWorkNumber().c_str());
            EXPECT_STREQ("06707654321", contact.getPrivateNumber().c_str());
        }
        END

        TEST(ContactTest, CopyConstructor)
        {
            Contact contact1("John", "Doe", "JD", "123 Main St", "+363452345", "06707654321");
            const Contact &contact2(contact1);
            EXPECT_EQ(contact1.getFirstName(), contact2.getFirstName());
            EXPECT_EQ(contact1.getLastName(), contact2.getLastName());
            EXPECT_EQ(contact1.getNickname(), contact2.getNickname());
            EXPECT_EQ(contact1.getAddress(), contact2.getAddress());
            EXPECT_EQ(contact1.getWorkNumber(), contact2.getWorkNumber());
            EXPECT_EQ(contact1.getPrivateNumber(), contact2.getPrivateNumber());
        }
        END

        TEST(ContactTest, AssignmentOperator)
        {
            Contact contact1("John", "Doe", "JD", "123 Main St", "+361234567890", "069876543210");
            Contact contact2;
            contact2 = contact1;
            EXPECT_EQ(contact1.getFirstName(), contact2.getFirstName());
            EXPECT_EQ(contact1.getLastName(), contact2.getLastName());
            EXPECT_EQ(contact1.getNickname(), contact2.getNickname());
            EXPECT_EQ(contact1.getAddress(), contact2.getAddress());
            EXPECT_EQ(contact1.getWorkNumber(), contact2.getWorkNumber());
            EXPECT_EQ(contact1.getPrivateNumber(), contact2.getPrivateNumber());
        }
        END

        TEST(ContactTest, SetFunctions)
        {
            Contact contact;
            contact.setFirstName("John");
            contact.setLastName("Doe");
            contact.setNickname("JD");
            contact.setAddress("123 Main St");
            contact.setWorkNumber("+361234567890");
            contact.setPrivateNumber("069876543210");

            EXPECT_STREQ("John", contact.getFirstName().c_str());
            EXPECT_STREQ("Doe", contact.getLastName().c_str());
            EXPECT_STREQ("JD", contact.getNickname().c_str());
            EXPECT_STREQ("123 Main St", contact.getAddress().c_str());
            EXPECT_STREQ("+361234567890", contact.getWorkNumber().c_str());
            EXPECT_STREQ("069876543210", contact.getPrivateNumber().c_str());
        }
        END

        TEST(ContactTest, IsPhoneNumber)
        {
            Contact contact;
            EXPECT_NO_THROW(contact.setPrivateNumber("+361234567890"));
            EXPECT_NO_THROW(contact.setPrivateNumber("06301234567"));
            EXPECT_THROW(contact.setPrivateNumber("123456789"), std::invalid_argument &);
            EXPECT_THROW(contact.setPrivateNumber("12345678901"), std::invalid_argument &);
            EXPECT_THROW(contact.setPrivateNumber("12345678A9"), std::invalid_argument &);
        }
        END

        TEST(ContactTest, StreamInsertionOperator)
        {
            Contact contact("John", "Doe", "JD", "123 Main St", "+361234567890", "069876543210");
            std::stringstream ss;
            ss << contact;
            EXPECT_STREQ("John;Doe;JD;123 Main St;+361234567890;069876543210", ss.str().c_str());
        }
        END

        TEST(ContactTest, StreamExtractionOperator)
        {
            Contact contact;
            std::stringstream ss("John;Doe;JD;123 Main St;+361234567890;069876543210");
            ss >> contact;
            EXPECT_STREQ("John", contact.getFirstName().c_str());
            EXPECT_STREQ("Doe", contact.getLastName().c_str());
            EXPECT_STREQ("JD", contact.getNickname().c_str());
            EXPECT_STREQ("123 Main St", contact.getAddress().c_str());
            EXPECT_STREQ("+361234567890", contact.getWorkNumber().c_str());
            EXPECT_STREQ("069876543210", contact.getPrivateNumber().c_str());
        }
        END
    }

    /*CONTACTS CLASS TESTS*/
    {
        TEST(ContactsTest, DefaultConstructor)
        {
            Contacts contacts;
            EXPECT_EQ((size_t)0, contacts.size());
        }
        END

        TEST(ContactsTest, ParameterizedConstructor)
        {
            Contact contact1("John", "Doe", "JD", "123 Main St", "+361234567890", "069876543210");
            Contact contact2("Alice", "Smith", "AS", "456 Elm St", "+361234567890", "069876543210");

            Contacts contacts = {contact1, contact2};

            EXPECT_EQ((size_t)2, contacts.size());
        }
        END

        TEST(ContactsTest, FileIO)
        {

            const String file = "test_file.csv";
            Contact c1 = {"Alice", "Smith", "AS", "456 Elm St", "+361234567890", "069876543210"};
            Contact c2 = {"John", "Doe", "JD", "123 Main St", "+361234567890", "069876543210"};
            Contacts co = {c1, c2};
            co.saveFile(file);

            Contacts con;
            con.loadFile(file);

            EXPECT_EQ(c1, con[0]);
            EXPECT_EQ(c2, con[1]);
            EXPECT_THROW(con[2], std::out_of_range &);
        }
        END
    }

    return gtest_lite::Test::getTest().failed >= 1;
}