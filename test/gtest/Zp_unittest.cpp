#include "Zp.hpp"
#include "Zm.hpp"
#include <string>
#include <gtest/gtest.h>

using namespace std;
using namespace ECC;

typedef mpz_class BigInt;
typedef Zp<BigInt> Field;
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

TEST(ZpTest, contruct_and_output)
{
	EXPECT_EQ(13, Z13->get_mod());
	EXPECT_EQ(0, Z13->zero().get_val());
	Elem x(0, Z13), y(1, Z13), z(-1, Z13), w(14, Z13), u(1000, Z13);
	BigInt bigint;
	bigint = "130000000000000000000000002";
	Elem B(bigint, Z13);
	EXPECT_EQ(0, x.get_val());
	EXPECT_EQ(1, y.get_val());
	EXPECT_EQ(12, z.get_val());
	EXPECT_EQ(1, w.get_val());
	EXPECT_EQ(1000%13, u.get_val());
	EXPECT_EQ(2, B.get_val());
}

struct TestCase{
	string op1, op2, ans;
};
#define TEST_OP(cases,op) \
	for (auto &it: (cases)) { \
		BigInt op1, op2, ans; \
		op1 = it.op1; \
		op2 = it.op2; \
		ans = it.ans; \
		Elem result(Elem(op1, Z13) op Elem(op2, Z13)); \
		EXPECT_EQ(result.get_val(), ans); \
	}
TEST(ZpTest, plus)
{
	TestCase testCases[] = {
	//  op1  op2  ans
		"1", "2", "3",
		"3", "4", "7",
		"9", "5", "1",
		"23", "63", "8",
		"2", "-3", "12",
		"-3", "4", "1",
		"-2", "-14", "10",
		"-4", "-4", "5"
	};
	TEST_OP(testCases,+);
}

TEST(ZpTest, minus)
{
	TestCase testCases[] = {
	//  op1  op2  ans
	};
	//TEST_OP(testCases, -);
}

TEST(ZpTest, multiply)
{
	TestCase testCases[] = {
	//  op1  op2  ans
	};
	//TEST_OP(testCases, *);
}

}; // namespace
