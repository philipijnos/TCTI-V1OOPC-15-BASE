#include "iostream"
#include "catch_with_main.hpp"
#include "vector.hpp"
#include <iomanip>

TEST_CASE("constructor, no parameters"){
	vector v();
	std::stringstream s;
	s << v;
	REQUIRE(s.str() == "(0,0)");
}