#include "src/lib/memtrace.h"
#include "src/lib/gtest_lite.h"
#include "src/phonebook/string.h"
#include "src/phonebook/array.h"

int main()
{
    /* STRING CLASS TESTS */
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

        TEST(String, OperatorLessThan) {
            String s1("apple");
            String s2("banana");

            EXPECT_TRUE(s1 < s2);
            EXPECT_FALSE(s2 < s1);
        }
        END

        TEST(String, OperatorEquals) {
            String s1("apple");
            String s2("apple");
            String s3("banana");

            EXPECT_TRUE(s1 == s2);
            EXPECT_FALSE(s1 == s3);
        }
        END

        TEST(String, MixedComparisons) {
            String s1("apple");
            String s2("banana");

            EXPECT_TRUE(s1 < s2);
            EXPECT_FALSE(s1 == s2);
        }
        END
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

        TEST(Array, ConstSize)
        {
            Array<int> arr;
            arr.pushBack(5);
            const Array<int> &constArr = arr;
            EXPECT_EQ((size_t)1, constArr.size());
        }
        END

        TEST(Array,ArrayInArray) {
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
           EXPECT_THROW(arr[0][0][0][0][0],std::out_of_range &);
        }
        END
    }

    return gtest_lite::Test::getTest().failed >= 1;
}