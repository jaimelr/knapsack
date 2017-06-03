#ifndef _sga_h_
#define _sga_h_
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

/*
 * PROBLEMA:
 * Maximizar la función: f(x,y) = 50 - (x - 5)² - (y - 5)²
 * para 0 <= x <= 10 y 0 <= y <= 10
 */

#define GEN_NUM         1
#define BITS_PER_GEN    10
#define POPULATION_SIZE 6
#define CHROMOSOM_SIZE  GEN_NUM*BITS_PER_GEN
#define RANGE_MAX       165
#define RANGE_MIN       0
#define RANGE           RANGE_MAX-RANGE_MIN
#define PC              0.8

typedef struct {
  unsigned char *chromosom;    // Valor binario
  float         *values;       // Valores decimal de los genes
  unsigned int  *bitsPerGen;   // Vector de bits por gen en el cromosoma
  float         fitness;
} INDIVIDUO;

INDIVIDUO* AllocatePopulation(INDIVIDUO* population);
void InitializePopulation(INDIVIDUO* population);
void GenDecodification(INDIVIDUO* population);
void CalculateFitness(INDIVIDUO* population);
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
void PrintValues(INDIVIDUO* population);
void PrintFathers(INDIVIDUO father, char index);

#endif
