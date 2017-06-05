#ifndef _sga_h_
#define _sga_h_
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "objects.h"

/*
 * PROBLEMA:
 * Knapsack
 */

#define GEN_NUM         1
#define BITS_PER_GEN    24
#define POPULATION_SIZE 50
#define CHROMOSOM_SIZE  GEN_NUM*BITS_PER_GEN
#define RANGE_MAX       6404180
#define RANGE_MIN       0
#define RANGE           RANGE_MAX-RANGE_MIN
#define PC              0.8
#define SNAPSACK_WEIGHT 6404180.0
#define KNAPSACK_BEST   13549094

typedef struct {
  unsigned char *chromosom;    // Valor binario
  unsigned int  *bitsPerGen;   // Vector de bits por gen en el cromosoma
  float         fitness;
} INDIVIDUO;

INDIVIDUO* AllocatePopulation(INDIVIDUO* population);
void InitializePopulation(INDIVIDUO* population, OBJECTS* objects);
float checkweight(INDIVIDUO* population, int init, OBJECTS* objects);
void GenDecodification(INDIVIDUO* population);
void CalculateFitness(INDIVIDUO* population, OBJECTS* objects);
float* CalculateProbabilities(INDIVIDUO* population);
int* RouletteGame(INDIVIDUO* population);
int PlayRoulette(float* probabilities);
INDIVIDUO* Cross(INDIVIDUO* population, int* fathers);
void Mutation(INDIVIDUO* population);
int SetupBest(INDIVIDUO* population, unsigned int idGbest);

void FreeMemory(INDIVIDUO* population);

// ______________________________________________Development
void PrintChromosom(unsigned char *chromosom);
void PrintPopulation(INDIVIDUO* population);
void PrintFathers(INDIVIDUO father, char index);

#endif
