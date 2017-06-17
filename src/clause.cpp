#include "clause.h"
#include <cstdlib>


cnf::Clause::Clause(std::list<int> c):literals({c})
{
    checkIfSatisfiedByLiteralAndNegation();
}

void cnf::Clause::checkIfSatisfiedByLiteralAndNegation()
{
    removeDuplicateLiterals();
    auto before = literals.size();
    literals.sort([](int first, int second){return std::abs(first) < std::abs(second);});
    literals.unique([](int first, int second){return std::abs(first) == std::abs(second);});
    auto after = literals.size();
    satisfied = before != after;
}

void cnf::Clause::removeDuplicateLiterals()
{
    literals.sort();
    literals.unique();
}

const size_t cnf::Clause::size()
{
    return literals.size();
}

const bool cnf::Clause::isEmpty()
{
    return size() == 0;
}

const bool cnf::Clause::isUnitClause()
{
    return size() == 1;
}

const bool cnf::Clause::isSatisfied()
{
    return satisfied;
}

void cnf::Clause::setAtom(int atom, bool toValue)
{
    eliminateFalseLiteral(atom, toValue);
    checkIfSatisfiedByAssignment(atom, toValue);
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

int cnf::Clause::translasteAtomAssignmentToLiteral(int atom, bool toValue)
{
    return toValue ? atom : (-1*atom);
}
