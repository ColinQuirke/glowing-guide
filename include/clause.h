#pragma once

#include <list>

namespace cnf{

class Clause
{
private:
    int translasteAtomAssignmentToLiteral(int atom, bool toValue);

    void eliminateFalseLiteral(int atom, bool toValue);

    void checkIfSatisfiedByAssignment(int atom, bool toValue);

public:

    Clause(std::list<int> c);

    void trim();

    const size_t size();

    void setAtom(int atom, bool toValue);

    bool isEmpty();

    bool isUnitClause();

    bool isSatisfied();

private:

    std::list<int> literals;
    bool satisfied = false;
};

}
