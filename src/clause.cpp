#include "clause.h"
#include <cstdlib>

int cnf::Clause::translasteAtomAssignmentToLiteral(int atom, bool toValue)
{
    return toValue ? atom : (-1*atom);
}

void cnf::Clause::eliminateFalseLiteral(int atom, bool toValue)
{
    auto literal = translasteAtomAssignmentToLiteral(atom, !toValue);
    literals.remove(literal);
}

void cnf::Clause::checkIfSatisfiedByAssignment(int atom, bool toValue)
{
    auto literal = translasteAtomAssignmentToLiteral(atom, toValue);
    satisfied = std::find(literals.begin(), literals.end(), literal) != literals.end();
}

cnf::Clause::Clause(std::list<int> c):literals({c})
{
    trim();
}

void cnf::Clause::trim()
{
    literals.sort([](int first, int second){return std::abs(first) < std::abs(second);});
    literals.unique();
    auto before = literals.size();
    literals.unique([](int first, int second){return std::abs(first) == std::abs(second);});
    satisfied = before != literals.size();
}

const size_t cnf::Clause::size()
{
    return literals.size();
}

void cnf::Clause::setAtom(int atom, bool toValue)
{
    eliminateFalseLiteral(atom, toValue);
    checkIfSatisfiedByAssignment(atom, toValue);
}

bool cnf::Clause::isEmpty()
{
    return size() == 0;
}

bool cnf::Clause::isUnitClause()
{
    return size() == 1;
}

bool cnf::Clause::isSatisfied()
{
    return satisfied;
}
