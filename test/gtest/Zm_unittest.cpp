#include "Zm.hpp"
#include <string>
#include <gtest/gtest.h>

using namespace std;
using namespace ECC;

typedef mpz_class BigInt;
typedef Zm<BigInt> Ring;
typedef Ring::Element Elem;

/*class ZmTest : public ::testing::Test {
protected:
	Ring z10;
	Ring* Z10;
	ZmTest
};*/

namespace {
Ring z10(10);
Ring *Z10 = &z10;

TEST(ZmTest, contruct_and_output)
{
	EXPECT_EQ(10, Z10->get_mod());
	EXPECT_EQ(0, Z10->zero().get_val());
	Elem x(0, Z10), y(1, Z10), z(-1, Z10), w(11, Z10), u(1000, Z10);
	BigInt bigint;
	bigint = "123456789012345678901234456789123214";
	Elem B(bigint, Z10);
	EXPECT_EQ(0, x.get_val());
	EXPECT_EQ(1, y.get_val());
	EXPECT_EQ(9, z.get_val());
	EXPECT_EQ(1, w.get_val());
	EXPECT_EQ(0, u.get_val());
	EXPECT_EQ(4, B.get_val());
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
		Elem result = Elem(op1, Z10) op Elem(op2, Z10); \
		EXPECT_EQ(result.get_val(), ans); \
	}
TEST(ZmTest, plus)
{
	TestCase testCases[] = {
	//  op1  op2  ans
		"1", "1", "2",
		"2", "3", "5",
		"2", "9", "1",
		"31", "53", "4",
		"1", "-1", "0",
		"3", "-2", "1",
		"-2", "-2", "6",
		"3", "-7", "6"
	};
	TEST_OP(testCases, +);
}

TEST(ZmTest, minus)
{
	TestCase testCases[] = {
	//  op1  op2  ans
		"1", "1", "0",
		"3", "2", "1",
		"11", "3", "8",
		"42", "11", "1",
		"1", "5", "6",
		"-1", "2", "7",
		"3", "-8", "1",
		"-2", "-3", "1"
	};
	TEST_OP(testCases, -);
}

TEST(ZmTest, multiply)
{
	TestCase testCases[] = {
	//  op1  op2  ans
		"1", "1", "1",
		"2", "3", "6",
		"3", "5", "5",
		"2", "-2", "6",
		"32", "54", "8",
		"-23", "33", "1",
		"-4", "-4", "6"
	};
	TEST_OP(testCases, *);
}

}; // namespace
