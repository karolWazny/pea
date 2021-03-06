#ifndef PEA_MUTATION_H
#define PEA_MUTATION_H

#include <functional>
#include "Individual.h"

using Mutation = std::function<void(Individual&)>;

enum class MutationMethod{
    REVERSE,
    RANDOM
};

MutationMethod mutationMethodFrom(const std::string&);
MutationMethod mutationMethodFrom(std::istream&);
std::string toString(const MutationMethod& method);

std::istream& operator>>(std::istream&, MutationMethod&);
std::ostream& operator<<(std::ostream&, const MutationMethod&);

class MutationFactory{
public:
    Mutation createMutation(MutationMethod method);
};

#endif //PEA_MUTATION_H
