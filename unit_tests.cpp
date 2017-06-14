#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

class CNFClause
{
public:
	CNFClause(std::vector<int> c):clause({c}){}

	size_t size()
	{
		return clause.size();
	}
private:
	std::vector<int> clause;
};

TEST_CASE("Clauses")

{
	auto clause = std::make_shared<CNFClause>(std::vector<int>({1,-2,3}));
	SECTION("Size")
	{
		REQUIRE(clause->size()==3);
	}
}