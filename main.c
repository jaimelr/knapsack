#include "objects.h"
#include "sga.h"

/*
 * PROBLEMA:
 * Knapsack
 */

int main(int argc, char const *argv[]) {
  INDIVIDUO *population;
  int* fathers;
  unsigned int  idGbest = 0;
  double error;
  float* probabilities;
  int limit;

  OBJECTS *objects;

  srand(time(NULL));
  if(argc != 3){ printf("\n\n\tLos datos introducidos en la Shell son incorrectos.\n"); return 1; }

  objects = GetObjects(argv[1], argv[2]);

  limit = 0;
  error = 11;
  population = AllocatePopulation(population);
  InitializePopulation(population, objects);
  population = CalculateFitness(population, objects, idGbest);
  while (limit < 20000 && error > 1) {
    fathers = RouletteGame(population);
    population = Cross(population, fathers);
    Mutation(population);
    population = CalculateFitness(population, objects, idGbest);
    idGbest = SetupBest(population, idGbest);
    limit++;
    error = KNAPSACK_BEST - population[idGbest].fitness;
  }
  printf("Error: %f\n", error);
  printf("Generacion: %d\n", limit);

  printf("Población ideal:\n");
  for (int i = 0; i < CHROMOSOM_SIZE; i++) {
    printf("[ %d ] ", population[idGbest].chromosom[i]);
  }
  printf("\n");
  printf("Global best: %f\n", population[idGbest].fitness);
  FreeMemory(population);

  return 0;
}
