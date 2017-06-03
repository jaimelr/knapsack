#include "objects.h"
#include "sga.h"

/*
 * PROBLEMA:
 * Maximizar la función: f(x,y) = 50 - (x - 5)² - (y - 5)²
 * para 0 <= x <= 10 y 0 <= y <= 10
 */

int main(int argc, char const *argv[]) {
  INDIVIDUO *population;
  int* fathers;
  unsigned int  idGbest = 0;
  double error;
  float* probabilities;
  int limit;

  OBJECTS *objects;

  if(argc != 3){ printf("\n\n\tLos datos introducidos en la Shell son incorrectos.\n"); return 1; }

  objects = GetObjects(argv[1], argv[2]);

  srand(time(NULL));

  limit = 0;
  error = 11;
  population = AllocatePopulation(population);
  InitializePopulation(population, objects);
  CalculateFitness(population, objects);
  while (limit < 20000) {
    fathers = RouletteGame(population);
    population = Cross(population, fathers);
    Mutation(population);
    idGbest = SetupBest(population, idGbest);
    CalculateFitness(population, objects);
    limit++;
    error = SNAPSACK_WEIGHT - population[idGbest].fitness;
    printf("Generacion: %d\n", limit);
  }

  for (int i = 0; i < CHROMOSOM_SIZE; i++) {
    printf("Población ideal:\n");
    printf("[ %d ]\t", population[idGbest].chromosom[i]);

  }
  printf("Global best: %f\n", population[idGbest].fitness);
  FreeMemory(population);

  return 0;
}
