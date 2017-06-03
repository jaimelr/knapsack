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
  srand(time(NULL));

  limit = 0;
  error = 1;
  population = AllocatePopulation(population);
  InitializePopulation(population);
  GenDecodification(population);
  CalculateFitness(population);
  while (limit < 50) {
    fathers = RouletteGame(population);
    population = Cross(population, fathers);
    Mutation(population);
    idGbest = SetupBest(population, idGbest);
    GenDecodification(population);
    CalculateFitness(population);
    limit++;
    printf("Generacion: %d\n", limit);
  }
  
  printf("Global best: %f\n", population[idGbest].fitness);
  FreeMemory(population);

  return 0;
}
