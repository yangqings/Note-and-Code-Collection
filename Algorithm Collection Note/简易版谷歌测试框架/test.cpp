#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
#include "testFramework.h"

using namespace std;



int myadd(int a, int b); 
int myminus(int a, int b); 

TEST(test, myadd){
	EXPECT_EQ(myadd(3,4), 7); // ==
	EXPECT_NE(myadd(3,4), 8); // !=
	EXPECT_GT(myadd(3,4), 6); // >
	EXPECT_GE(myadd(3,4), 6); // >=
	EXPECT_LT(myadd(3,4), 8); // <=
	EXPECT_LE(myadd(3,4), 6); // <   fault!
}

TEST(test, myminus){
	EXPECT_EQ(myminus(7,4), 3); // ==  
	EXPECT_NE(myminus(7,4), 4); // !=
	EXPECT_GT(myminus(7,4), 2); // >
	EXPECT_GE(myminus(7,4), 2); // >=
	EXPECT_LT(myminus(7,4), 1); // <= fault!
	EXPECT_LE(myminus(7,4), 1); // <  fault!
}

int myadd(int a, int b){
	return (a + b);
}

int myminus(int a, int b){
	return (a - b);
}

int main(void){
	printf(RED("hello world\n"));
	printf(GREEN("hello world\n"));
	printf(BLUE("hello world\n"));
	printf(YELLOW("hello world\n"));

    return RUN_ALL_TEST();
}