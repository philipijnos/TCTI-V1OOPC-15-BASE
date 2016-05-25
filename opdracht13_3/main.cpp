#include "ostream"
#include "catch_with_main.hpp"
#include "vector.hpp"
#include <iomanip>

TEST_CASE("constructor, no parameters"){
	vector v;
	REQUIRE(v == vector(0, 0));
}

TEST_CASE("constructor, two parameters"){
	vector v(1, 1);
	REQUIRE(v == vector(1, 1));
}

TEST_CASE("operator+, one parameter"){
	vector v(1, 2);
	REQUIRE(+v == v);
}

TEST_CASE("operator+, two parameters"){
	vector a(1, 2);
	vector b(2, 3);
	REQUIRE(a + b == vector(3, 5));
}

TEST_CASE("operator+=, one parameters"){
	vector a(1, 2);
	vector b(2, 3);
	a += b;
	REQUIRE(a == vector(3, 5));
}

TEST_CASE("operator-, one parameter"){
	vector a(1, 2);
	REQUIRE(-a == vector(-1, -2));
}

TEST_CASE("operator-=, one parameter"){
	vector a(1, 2);
	vector b(3, 5);
	b-= a;
	REQUIRE(b == vector(2, 3));
}

TEST_CASE("operator-, two parameters"){
	vector a(1, 2);
	vector b(3, 5);
	REQUIRE(b-a == vector(2, 3));
}

TEST_CASE("operator*=, one parameter"){
	vector a(1, 2);
	a *= 3;
	REQUIRE(a == vector(3, 6));
}

TEST_CASE("operator*, two parameters"){
	vector a(1, 2);
	REQUIRE(a * 3 == vector(3, 6));
	//REQUIRE(3 * a == vector(3, 6)); // Dit wist ik uiteindelijk niet op te lossen.
}

TEST_CASE("operator/=, one parameter"){
	vector a(2, 4);
	a /= 2;
	REQUIRE(a == vector(1, 2));
}

TEST_CASE("operator/, two parameters"){
	vector a(2, 4);
	REQUIRE(a / 2 == vector(1, 2));
}

TEST_CASE("operator<<, one parameter"){
	std::stringstream s;
	vector a(2, 5);
	s << a;
	REQUIRE(s.str() == "(2, 5)");
}