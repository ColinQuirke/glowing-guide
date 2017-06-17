#pragma once

#include <list>

namespace cnf{

class Clause
{
private:


public:

    Clause(std::list<int> c);

    const size_t size();
    const bool isEmpty();
    const bool isUnitClause();
    const bool isSatisfied();

    void setAtom(int atom, bool toValue);

private:

    void removeDuplicateLiterals();
    void checkIfSatisfiedByLiteralAndNegation();
    int translasteAtomAssignmentToLiteral(int atom, bool toValue);
    void eliminateFalseLiteral(int atom, bool toValue);
    void checkIfSatisfiedByAssignment(int atom, bool toValue);

    std::list<int> literals;
    bool satisfied = false;
};

}
