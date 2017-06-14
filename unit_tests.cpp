#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <list>

namespace cnf{

class Clause
{
private:
    int getLFalseLiteral(int atom, bool toValue)
    {
        return toValue ? (-1*atom) : atom;
    }

    void eliminateFalseLiteral(int atom, bool toValue)
    {
        auto literal = getLFalseLiteral(atom,toValue);
        literals.remove(literal);
    }

public:

    Clause(std::list<int> c):literals({c}){}

    const size_t size()
    {
        return literals.size();
    }

    void setAtom(int atom, bool toValue)
    {
        eliminateFalseLiteral(atom,toValue);
    }

private:

    std::list<int> literals;
};

}

TEST_CASE("Clauses")

{
    auto clause = std::make_shared<cnf::Clause>(std::list<int>({1,-2,3}));
    SECTION("Initial Size")
    {
        REQUIRE(clause->size()==3);
    }
    SECTION("Atom Assigned")
    {
        SECTION("Atom not in clause")
        {
            clause->setAtom(4,false);
            REQUIRE(clause->size()==3);
        }
        SECTION("Atom assigned false while literal true in clause")
        {
            clause->setAtom(1,false);
            REQUIRE(clause->size()==2);
        }
        SECTION("Atom assigned true while literal false in clause")
        {
            clause->setAtom(2,true);
            REQUIRE(clause->size()==2);
        }
        SECTION("Atom assigned false while literal false in clause")
        {
            clause->setAtom(2,false);
            REQUIRE(clause->size()==3);
        }
        SECTION("Atom assigned true while literal true in clause")
        {
            clause->setAtom(1,true);
            REQUIRE(clause->size()==3);
        }

    }
}
