#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <list>

namespace cnf{

class Clause
{
public:
    Clause(std::list<int> c):clause({c}){}

    const size_t size()
    {
        return clause.size();
    }

    void setVariable(int variable, bool toValue)
    {
        if(toValue)
            variable *= -1;
        clause.remove(variable);
    }

private:
    std::list<int> clause;
};

}

TEST_CASE("Clauses")

{
    auto clause = std::make_shared<cnf::Clause>(std::list<int>({1,-2,3}));
    SECTION("Initial Size")
    {
        REQUIRE(clause->size()==3);
    }
    SECTION("Literal Assigned")
    {
        SECTION("Literal not in clause")
        {
            clause->setVariable(4,false);
            REQUIRE(clause->size()==3);
        }
        SECTION("Literal assigned false while true in clause")
        {
            clause->setVariable(1,false);
            REQUIRE(clause->size()==2);
        }
        SECTION("Literal assigned true while false in clause")
        {
            clause->setVariable(2,true);
            REQUIRE(clause->size()==2);
        }
        SECTION("Literal assigned false while false in clause")
        {
            clause->setVariable(2,false);
            REQUIRE(clause->size()==3);
        }
        SECTION("Literal assigned true while true in clause")
        {
            clause->setVariable(1,true);
            REQUIRE(clause->size()==3);
        }

    }
}
