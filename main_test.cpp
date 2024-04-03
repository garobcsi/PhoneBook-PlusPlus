#include "src/lib/memtrace.h"
#include "src/lib/gtest_lite.h"
#include "src/phonebook/string.h"

int main()
{
    //STRING CLASS TESTS
    {
        TEST(String, DefaultConstructorTest)
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
            ss >> s;
            EXPECT_EQ((size_t)5, s.size());
            EXPECT_STREQ("hello", s.c_str());
            ss >> s;
            EXPECT_EQ((size_t)5, s.size());
            EXPECT_STREQ("world", s.c_str());
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
    }

    return gtest_lite::Test::getTest().failed >= 1;
}