#ifndef GA
#define GA

typedef struct DNA{
    float* fDNA;
    unsigned fLength;
    BoolArray bDNA;
    unsigned bLength;
}DNA;

typedef struct Organism{
    void* org;
    float fit;
}Organism;

class GeneticAlgorithm{
public:
    GeneticAlgorithm(unsigned popSize, DNA dna, float (*fitness)(void*),
                     void* (*fromDNA)(DNA), bool (*termination)(float));
    void* evolve();
    void generation();
   
    //variables:
    
    //# of parents to an organism
    unsigned parents;
    
    // avg # of children
    unsigned children;
    // range of # of children;
    float childDistribution;
    
    // percent by which crossover favors organisms with higher fitness
    float geneFit;
    
    //probability of a randomized gene
    float geneMutation;
    //probability of a slightly changed gene
    float geneModification;
    float geneModSize;
    
    // percent of population that reproduces
    float parentPercentage;
    
    //parents can join the next generation
    bool parentsSurvive;
    //organisms can have multiple sex partners!
    bool multipleParentSets;
    
    
private:
    
    void** population;
    DNA maxVals;
    DNA* popDNA;
    int fLength, bLength;
    unsigned popSize;
    float (*fitness)(void*);
    void* (*fromDNA)(DNA);
    bool (*termination)(float);
};
    
    