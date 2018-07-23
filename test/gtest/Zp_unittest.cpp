#include "Zm.hpp"
#include <string>
#include <gtest/gtest.h>

using namespace std;
using namespace ECC;

typedef mpz_class BigInt;
typedef Zm<BigInt> Field;
typedef Field::Element Elem;

/*class ZmTest : public ::testing::Test {
protected:
	Field z13;
	Field* Z13;
	ZmTest
};*/

namespace {
Field z13(13);
Field *Z13 = &z13;

TEST(ZmTest, contruct_and_output)
{
	EXPECT_EQ(13, Z13->get_mod());
	EXPECT_EQ(0, Z13->zero().get_val());
	Elem x(0, Z13), y(1, Z13), z(-1, Z13), w(14, Z13), u(1000, Z13);
	BigInt bigint;
	bigint = "130000000000000000000000000"
	Elem B(bigint, Z13);
	EXPECT_EQ(0, x.get_val());
	EXPECT_EQ(1, y.get_val());
	EXPECT_EQ(12, z.get_val());
	EXPECT_EQ(1, w.get_val());
	EXPECT_EQ(1000%13, u.get_val());
	EXPECT_EQ(0, B.get_val());
}

struct TestCase{
	string op1, op2, ans;
};
#define TEST_OP(cases, op) \
	for (auto &it: (cases)) { \
		BigInt op1, op2, ans; \
		op1 = it.op1; \
		op2 = it.op2; \
		ans = it.ans; \
		Elem result = Elem(op1, Z13) op Elem(op2, Z13); \
		EXPECT_EQ(result.get_val(), ans); \
	}
TEST(ZmTest, plus)
{
	TestCase testCases[] = {
	//  op1  op2  ans
	};
	TEST_OP(testCases, +);
}

TEST(ZmTest, minus)
{
	TestCase testCases[] = {
	//  op1  op2  ans
	};
	TEST_OP(testCases, -);
}

TEST(ZmTest, multiply)
{
	TestCase testCases[] = {
	//  op1  op2  ans
	};
	TEST_OP(testCases, *);
}

}; // namespace
