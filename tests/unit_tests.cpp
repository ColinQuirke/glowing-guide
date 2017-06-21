#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "clause.h"

TEST_CASE("Clauses")
{

    SECTION("Initialise")
    {
        cnf::Clause clause({1,-2,3});

        SECTION("Initial Size")
        {
            REQUIRE(clause.size()==3);
        }
        SECTION("Clause with active literals is not empty")
        {
            REQUIRE(!clause.isEmpty());
        }
        SECTION("Assign Atom")
        {
            SECTION("Setting an Atom not in clause has no effect")
            {
                clause.setAtom(4,false);
                REQUIRE(clause.size()==3);
            }
            SECTION("Atom assigned false eliminates true literal")
            {
                clause.setAtom(1,false);
                REQUIRE(clause.size()==2);
            }
            SECTION("Atom assigned true eliminates false literal")
            {
                clause.setAtom(2,true);
                REQUIRE(clause.size()==2);
            }
            SECTION("Atom assigned true satisfies clause")
            {
                clause.setAtom(1,true);
                REQUIRE(clause.isSatisfied());
            }        
            SECTION("Atom assigned false does not satisfy clause")
            {
                clause.setAtom(1,false);
                REQUIRE(!clause.isSatisfied());
            }
            SECTION("Atom assigned false satisfies the clause")
            {
                clause.setAtom(2,false);
                REQUIRE(clause.isSatisfied());
            }
        }
        SECTION("Unit Clauses")
        {

            cnf::Clause unitClause({1});
            REQUIRE(unitClause.isUnitClause());
            SECTION("Unit clause becomes unsatisfiable by atom assignment")
            {
                unitClause.setAtom(1,false);
                REQUIRE(unitClause.isEmpty());
            }
            SECTION("Unit clause satisfied by atom assignment")
            {
                unitClause.setAtom(1,true);
                REQUIRE(unitClause.isSatisfied());
            }
            SECTION("Clause with multiple literals is not a Unit Clause")
            {
                REQUIRE(!clause.isUnitClause());
                SECTION("but becomes unit through variable elimination")
                {
                    clause.setAtom(1,false);
                    clause.setAtom(2,true);
                    REQUIRE(clause.isUnitClause()); 
                }
            }
        }

        SECTION("Initial Size Trimed")
        {
            cnf::Clause trimmedClause({1,-2,3,-2,1});
            REQUIRE(trimmedClause.size()==3);
        }
        SECTION("Clause that contains a literal and its negation is trivially satisfied")
        {
            cnf::Clause trivialClause({1,-2,2});
            REQUIRE(trivialClause.isSatisfied());
        }

    }

}

/*TEST_CASE("Unit Propogate")
{
    SECTION()
    {

    }
}*/
