#include <vector>
#include <string>
#include "gtest/gtest.h"

int hello_gtest_add(const int a, const int b)
{
    return (a + b);
}

// EXPECT_* ʧ��ʱ��������������ִ��
// ASSERT_* ʧ��ʱ��ֱ���ڵ�ǰ�����з��أ���ǰ������ASSERT_*�������佫����ִ��.
TEST(Lessson1, section1)
{
    EXPECT_EQ(3, hello_gtest_add(0, 10));  
    EXPECT_EQ(6, hello_gtest_add(30, 18)); 
}

TEST(Lesson2, section1)
{
    std::vector<int> x;
    std::vector<int> y;

    for (int i=0; i<10; i++)
    {
        x.push_back(i);
        y.push_back(i);
    }
    x.push_back(10);
    y.push_back(20);

    for (size_t i=0; i<x.size(); ++i) 
    {
        EXPECT_EQ(x[i], y[i]) << "this is additional info i=" << i; // ʹ��<<��, ����ʱ��ʾ��ϸ��Ϣ
    }
}

/**
 * bool ���
 | Fatal assertion | Nonfatal assertion | Verifies |
 |-----------------+--------------------+----------|
 | ASSERT_TRUE     | EXPECT_TRUE        | true     |
 | ASSERT_FALSE    | EXPECT_FALSE       | false    |
 |-----------------+--------------------+----------|
 
 ��ֵ�� ���
 | Fatal assertion             | Nonfatal assertion          | Verifies           |
 |-----------------------------+-----------------------------+--------------------|
 | ASSERT_EQ(expected, actual) | EXPECT_EQ(expected, actual) | expected == actual |
 | ASSERT_NE(v1, v2)           | EXPECT_NE(v1, v2)           | v1 != v2           |
 | ASSERT_LT(v1, v2)           | EXPECT_LT(v1, v2)           | v1 < v2            |
 | ASSERT_LE(v1, v2)           | EXPECT_LE(v1, v2)           | v1 <= v2           |
 | ASSERT_GT(v1, v2)           | EXPECT_GT(v1, v2)           | v1 > v2            |
 | ASSERT_GE(v1, v2)           | EXPECT_GE(v1, v2)           | v1 >= v2           |
 |-----------------------------+-----------------------------+--------------------|

 �ַ��� ���
 | Fatal assertion          | Nonfatal assertion       | Verifies              |
 |--------------------------+--------------------------+-----------------------|
 | ASSERT_STREQ(s1, s2)     | EXPECT_STREQ(v1, v2)     | v1 == v2              |
 | ASSERT_STRNE(s1, s2)     | EXPECT_STREQ(v1, v2)     | v1 != v2              |
 | ASSERT_STRCASEEQ(s1, s2) | EXPECT_STRCASEEQ(v1, v2) | v1 == v2, ignore case |
 | ASSERT_STRCASENE(s1, s2) | EXPECT_STRCASENE(v1, v2) | v1 != v2, ignore case |
 |--------------------------+--------------------------+-----------------------|
 *STREQ*��*STRNE*ͬʱ֧��char*��wchar_t*���͵ģ�*STRCASEEQ*��*STRCASENE*ȴֻ����char*.

 **/
TEST(Lesson2, Section2)
{
    char* pszCoderZh = "CoderZh";
    wchar_t* wszCoderZh = L"CoderZh";
    std::string strCoderZh = "CoderZh";
    std::wstring wstrCoderZh = L"CoderZh";

    EXPECT_STREQ("CoderZh", pszCoderZh);
    EXPECT_STREQ(L"CoderZh", wszCoderZh);
    EXPECT_STRNE("CnBlogs", pszCoderZh);
    EXPECT_STRNE(L"CnBlogs", wszCoderZh);
    EXPECT_STRCASEEQ("coderzh", pszCoderZh);
    //EXPECT_STRCASEEQ(L"coderzh", wszCoderZh);    ��֧��
    EXPECT_STREQ("CoderZh", strCoderZh.c_str());
    EXPECT_STREQ(L"CoderZh", wstrCoderZh.c_str());
}

/** ��ʾ���سɹ���ʧ��
 | Fatal assertion | Nonfatal assertion |
 |-----------------+--------------------|
 | FAIL();         | ADD_FAILURE();     |
 |-----------------+--------------------|
 ֱ�ӷ��سɹ�: SUCCEED();
  */
TEST(Lesson2, section3)
{
    ADD_FAILURE() << "Sorry"; // None Fatal Asserton����������ִ�С�
    //FAIL(); // Fatal Assertion��������ִ�иð�����
    SUCCEED();
}

/** �쳣���
 | Fatal assertion                         | Nonfatal assertion | Verifies                                        |
 |-----------------------------------------+--------------------+-------------------------------------------------|
 | ASSERT_THROW(statement, exception_type) | EXPECT_THROW       | statement throws an exception of the given type |
 | ASSERT_ANY_THROW(statement)             | EXPECT_ANY_THROW   | statement throws an exception of any type       |
 | ASSERT_NO_THROW(statement)              | EXPECT_NO_THROW    | statement doesn't throw any exception           |
 |-----------------------------------------+--------------------+-------------------------------------------------|
 */
int lesson2_excption_test(int a, int b)
{
    if (a == 0 || b == 0)
    {
        throw "don't do that";
    }
    int c = a % b;
    if (c == 0)
        return b;
    return lesson2_excption_test(b, c);
}

TEST(Lesson2, section4)
{
    EXPECT_ANY_THROW(lesson2_excption_test(10, 0));
    EXPECT_THROW(lesson2_excption_test(0, 5), char*);
}

/** Predicate Assertions
 * ��ʹ��EXPECT_TRUE��ASSERT_TRUEʱ����ʱϣ���ܹ����������ϸ����Ϣ��
 * ������һ�������ķ���ֵTRUE����FALSEʱ��ϣ���ܹ��������Ĳ�����ʲô��
 * �Ա�ʧ�ܺ�ø��١�����ṩ�����µĶ��ԣ�
 | Fatal assertion             | Nonfatal assertion | Verifies                  |
 |-----------------------------+--------------------+---------------------------|
 | ASSERT_PRED1(pred1, v1)     | EXPECT_PRED1       | pred1(v1) return true     |
 | ASSERT_PRED2(pred2, v1, v2) | EXPECT_PRED2       | pred2(v1, v2) return true |
 | ...                         | ...                | ...                       |
 |-----------------------------+--------------------+---------------------------|
 Google��˵�ˣ�����ֻ�ṩ<=5�������ģ������Ҫ���Ը���Ĳ�����ֱ�Ӹ������ǡ����濴�����������ô�á� 
 */
bool MutuallyPrime(int m, int n)
{
    return lesson2_excption_test(m , n) > 1;
}

TEST(Lesson2, section5)
{
    int m = 5, n = 6;
    EXPECT_PRED2(MutuallyPrime, m, n);
}

/** ��������������������Ļ����������Զ��������ʽ��ͨ�����£�
 *
 | Fatal assertion                               | Nonfatal assertion                            | Verifies                               |
 |-----------------------------------------------+-----------------------------------------------+----------------------------------------|
 | ASSERT_PRED_FORMAT1(pred_format1, val1)       | EXPECT_PRED_FORMAT1(pred_format1, val1)       | pred_format1(val1) is successful       |
 | ASSERT_PRED_FORMAT2(pred_format2, val1, val2) | EXPECT_PRED_FORMAT2(pred_format2, val1, val2) | pred_format2(val1, val2) is successful |
 | ...                                           | ...                                           | ...                                    |
 |-----------------------------------------------+-----------------------------------------------+----------------------------------------|
 */
testing::AssertionResult AssertFoo(const char* m_expr, const char* n_expr, const char* k_expr, int m, int n, int k) {
    if (lesson2_excption_test(m, n) == k)
        return testing::AssertionSuccess();
    testing::Message msg;
    msg << m_expr << " �� " << n_expr << " �����Լ��Ӧ���ǣ�" << lesson2_excption_test(m, n) << " �����ǣ�" << k_expr;
    return testing::AssertionFailure(msg);
}

TEST(Lesson2, section6)
{
    EXPECT_PRED_FORMAT3(AssertFoo, 3, 6, 2);
}
