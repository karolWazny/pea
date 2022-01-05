#ifndef PEA_GENETICSOLVER_H
#define PEA_GENETICSOLVER_H


#include <utility>

#include "../TSPAbstractSolver.h"
#include "Individual.h"
#include "Mutation.h"
#include "../../utils/RealRandom.h"
#include "../../utils/Randomizer.h"

class GeneticSolver : public TSPAbstractSolver {
public:

    class Parameters {
    public:
        int tournamentPool{5};
        int population{30};
        int breed{30};
        int generations{200};
        double crossoverProbability{0.6};
        double mutationProbability{0.3};
        MutationMethod mutationMethod{MutationMethod::REVERSE};

        static Parameters from(const std::string&);
        static Parameters from(std::istream&);
        [[nodiscard]] std::string parse() const;
    };

    explicit GeneticSolver(Parameters);
    GeneticSolver();

    class Builder {
    public:
        Builder& withPopulation(int);
        Builder& withBreed(int);
        Builder& withCrossoverRate(double);
        Builder& withMutationRate(double);
        Builder& withMutationMethod(MutationMethod);
        Builder& withTournamentPool(int);
        Builder& withParameters(const Parameters&);
        GeneticSolver build();
    private:
        Parameters parameters;
    };

    TSPSolution solveFor(const TSPInputMatrix& input) override;

private:
    explicit GeneticSolver(Mutation mutation) : mutate(std::move(mutation)){};
    void prepareMembers();
    long long calculateCost(const Individual& individual);
    Individual chooseTournamentStyle();
    void applyMutationToBreed();
    void applyCrossoverToBreed();
    void createNewBreed();
    void assessPopulation();
    void setBreedAsParents();

    Individual produceChild(Individual&, Individual&, int, int);

    [[nodiscard]] TSPSolution buildSolutionFromBest() const;

    static RealRandom<double> random;
    static Randomizer intRandom;

    Parameters parameters;
    ffarray<Individual> population;
    ffarray<Individual> breed;
    LinkedList<Individual> crossoverBreed;
    const TSPInputMatrix* input{};
    Individual currentlyBest;

    Mutation mutate;
    void crossover(Individual&, Individual&);
};

#endif //PEA_GENETICSOLVER_H
