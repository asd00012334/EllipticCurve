#include "Integer.hpp"
#include <string>
#include "gtest/gtest.h"
#define ONE_BIG_INT_N "123456789123456789123456787"
#define ONE_BIG_INT   "123456789123456789123456788"
#define ONE_BIG_INT_P "123456789123456789123456789"
#define EXPECT_THROW_STR(stat,err) try{stat;}catch(const char* e){EXPECT_STREQ(e, err); }

class BigIntTest : public ::testing::Test {
protected:
	ECC::BigInt n0, n1, n_big, n_m1;
	BigIntTest(): 
		n0("0"),
		n1("1"),
		n_big(ONE_BIG_INT),
		n_m1("-1")
		{ }

};

using namespace std;
namespace {
TEST_F(BigIntTest, contruct_and_output){
	EXPECT_EQ("0", string(ECC::BigInt("0")));
	EXPECT_EQ("1", string(ECC::BigInt("1")));
	EXPECT_EQ(ONE_BIG_INT, string(ECC::BigInt(ONE_BIG_INT)));
	EXPECT_EQ("-1", string(ECC::BigInt("-1")));


	EXPECT_EQ("1", string(ECC::BigInt("0001")));

	EXPECT_EQ("0", string(ECC::BigInt(0x0)));
	EXPECT_EQ("1", string(ECC::BigInt(0x1)));
	EXPECT_EQ("23456789", string(ECC::BigInt(0x23456789)));
	EXPECT_EQ("-1", string(ECC::BigInt(-0x1)));

	EXPECT_THROW_STR(ECC::BigInt(""), "empty input");
	EXPECT_THROW_STR(ECC::BigInt("-"), "invalid input");
	EXPECT_THROW_STR(ECC::BigInt("x"), "hex to digit error");
	EXPECT_THROW_STR(ECC::BigInt("123x123"), "hex to digit error");
	EXPECT_THROW_STR(ECC::BigInt("-123x123"), "hex to digit error");
	
}

struct TestCase{
	string op1, op2, res;
};

TEST_F(BigIntTest, plus_and_minus){
	TestCase plus_test_cases[] = {
	//   op1 + op2 = res
		{"0", "0", "0"},
		{"1", "1", "2"},
		{"0", "1", "1"},
		{"1", "0", "1"},
		{"-1", "-1", "-2"},
		{"-1", "0", "-1"},
		{"0", "-1", "-1"},
		{"1", "-1", "0"},
		{"-1", "1", "0"},
		{"123456789123456789123456789", "123456789123456789123456789", "2468acf122468acf122468acf12"},
		{"123456789123456789123456789", "0", "123456789123456789123456789"},
		{"123456789123456789123456789", "1", "12345678912345678912345678a"},
		
		{"123456789123456789123456789", "-1", "123456789123456789123456788"},
		{"-1", "123456789123456789123456789", "123456789123456789123456788"},

		{"-123456789123456789123456789", "1", "-123456789123456789123456788"},
		{"1", "-123456789123456789123456789", "-123456789123456789123456788"},
		
		{"-123456789123456789123456789", "-1", "-12345678912345678912345678a"},

	};

	for(auto & it: plus_test_cases)
		EXPECT_EQ(it.res, string(ECC::BigInt(it.op1) + ECC::BigInt(it.op2)));
}
TEST_F(BigIntTest, multiply){
}

} // namespace

