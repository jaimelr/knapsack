#include "sga.h"

/*
 * PROBLEMA:
 * Knapsack
 */

INDIVIDUO* AllocatePopulation(INDIVIDUO* population) {
  int i;

  population = (INDIVIDUO*)malloc(POPULATION_SIZE*sizeof(INDIVIDUO));
  if(population == NULL) {
    printf("ERROR 001: No se ha podido asignar memoria, intentalo con otra población.\n");
    return 0;
  }
  for (i = 0; i < POPULATION_SIZE; i++) {
    population[i].chromosom = (unsigned char*)malloc(GEN_NUM*BITS_PER_GEN*sizeof(unsigned char*));
    population[i].bitsPerGen = (unsigned int*)malloc(GEN_NUM*sizeof(unsigned int));
    if(population == NULL) {
      printf("ERROR 001: No se ha podido asignar memoria, intentalo con otra población.\n");
      return 0;
    }
  }

  return population;
}

void InitializePopulation(INDIVIDUO* population, OBJECTS* objects) {
  int i;
  int j;
  float randNum;
  int true = 1;
  float weight=0;

  for (i = 0; i < POPULATION_SIZE; i++) {
    while(true){
      for (j = 0; j < CHROMOSOM_SIZE; j++) {
        randNum = ((1.0*rand())/RAND_MAX);
        if(randNum < 0.5)
          population[i].chromosom[j] = 0;
        else
          population[i].chromosom[j] = 1;
      }
      for (j = 0; j < GEN_NUM; j++) {
        population[i].bitsPerGen[j] = BITS_PER_GEN;
      }
      weight = CheckWeight(population, i, objects);
      if(weight <= SNAPSACK_WEIGHT)
        true = 0; //da la salida al while
    }
    true = 1; //vuelve a ser condicion para q entre a while
  }
}

float CheckWeight(INDIVIDUO* population, int init, OBJECTS* objects) {

  int j;
  float weight = 0;

  for(j = 0; j < BITS_PER_GEN ; j++) {
    if(population[init].chromosom[j] == 1) {
    	weight = weight + objects[j].weight;
    }
  }

  return weight;
}

INDIVIDUO* CalculateFitness(INDIVIDUO* population, OBJECTS* objects, int idGbest) {
  int i;
  int j;
  float x;
  float y;
  float totalProfit;
  float totalWeight;

  totalProfit = 0;
  totalWeight = 0;

  for (i = 0; i < POPULATION_SIZE; i++) {
    for (j = 0, totalProfit = 0, totalWeight = 0; j < CHROMOSOM_SIZE; j++) {
      if(population[i].chromosom[j] == 1) {
        totalProfit += objects[j].profit;
        totalWeight += objects[j].weight;
      }
    }
    if(totalWeight > SNAPSACK_WEIGHT) {
      for(j = 0; j< CHROMOSOM_SIZE; j++)
      population[i].chromosom[j] = population[idGbest].chromosom[j];
      population[i].fitness = population[idGbest].fitness;//totalProfit - 5*(totalWeight - SNAPSACK_WEIGHT);
    }
    else {
      population[i].fitness = totalProfit;
    }
  }

  return population;
}


float* CalculateProbabilities(INDIVIDUO* population) {
  int i;
  float fitnessTotal;
  float* probabilities;
  float sum;

  sum = 0;

  probabilities = (float*)malloc(POPULATION_SIZE*sizeof(float));

  for (i = 0, fitnessTotal = 0; i < POPULATION_SIZE; i++) {
    fitnessTotal += population[i].fitness;
  }

  for (i = 0; i < POPULATION_SIZE; i++) {
    probabilities[i] = population[i].fitness/fitnessTotal;
    probabilities[i] *= 100;
  }

  return probabilities;
}

int* RouletteGame(INDIVIDUO* population) {
  int father;
  int i;
  int j;
  float* probabilities;
  int* fathers;

  probabilities = (float*)malloc(POPULATION_SIZE*sizeof(float));
  fathers = (int*)malloc(POPULATION_SIZE*sizeof(int));

  probabilities = CalculateProbabilities(population);

  for (i = 0; i < POPULATION_SIZE; i++) {
    father = PlayRoulette(probabilities);
    *(fathers + i) = father;
  }

  return fathers;
}

int PlayRoulette(float* probabilities) {
  int father;
  int i;
  float randNum;
  float incrementalRange;

  incrementalRange = 0;
  randNum = 100*((1.0*rand())/RAND_MAX);
  for (i = 0; i < POPULATION_SIZE; i++) {
    incrementalRange += probabilities[i];
    if(randNum < incrementalRange) {
      father = i;
      break;
    }
  }

  return father;
}

INDIVIDUO* Cross(INDIVIDUO* population, int* fathers) {
	int i;
  int j;
  int p1;
  int p2;
	float numRand;
	int Px;
	INDIVIDUO* GenerationNew;

	GenerationNew = AllocatePopulation(GenerationNew);

  for (i = 0; i < POPULATION_SIZE; i+=2) {
    Px = (CHROMOSOM_SIZE - 1)*((1.0*rand())/RAND_MAX) + 1; //calcula el punto de cruza de progenitores
    numRand = (1.0*rand())/RAND_MAX; //calcula el pc de progenitores
    p1 = *(fathers + i);
    p2 = *(fathers + i+1);
    if(numRand < PC) {
      for (j = 0; j < CHROMOSOM_SIZE; j++) {
        if(j < Px) {//si la interacion esta antes del punto de cruza
          GenerationNew[i].chromosom[j] = population[p1].chromosom[j];//hijo 1 toma el bit del padre 1 primera parte
          GenerationNew[i+1].chromosom[j] = population[p2].chromosom[j];//hijo 2 toma el bit del padre 2
        }
        else {
          GenerationNew[i].chromosom[j] = population[p2].chromosom[j];//hijo 1 toma el bit del padre 2 segunda parte
          GenerationNew[i+1].chromosom[j] = population[p1].chromosom[j];//hijo 2 toma el bit del padre 1
        }
      }
    }
    else {
      //si no se cruzan entonces los nuevos hijos son exactamente iguales a los padres
      for (j = 0; j <CHROMOSOM_SIZE ; j++) {
        GenerationNew[i].chromosom[j] = population[p1].chromosom[j];
        GenerationNew[i+1].chromosom[j] = population[p2].chromosom[j];
      }
    }
  }

  return GenerationNew;
}

void Mutation(INDIVIDUO* population) {
  int i;
  int j;
  int randNum;

  for (i = 0; i < POPULATION_SIZE; i++) {
    for (j = 0; j < CHROMOSOM_SIZE; j++) {
      randNum = rand() % 100 + 1;
      if(randNum == 1) {
        if(population[i].chromosom[j] == 0) {
          population[i].chromosom[j] = 1;
        }
        else {
          population[i].chromosom[j] = 0;
        }
      }
    }
  }
}

int SetupBest(INDIVIDUO* population, unsigned int idbest) {
	unsigned int i;
	float best;

	best = population[idbest].fitness;
	for(i=0; i < POPULATION_SIZE; i++)
	{
		if (population[i].fitness > best)
		{
			best = population[i].fitness;
      idbest = i;
		}
	}
  return idbest;
}

void FreeMemory(INDIVIDUO* population) {
  int i;

  for (i = 0; i < POPULATION_SIZE; i++) {
    free(population[i].chromosom);
    free(population[i].bitsPerGen);
  }
}

//______________________________________________Development
void PrintChromosom(unsigned char *chromosom) {
  int i;

  for (i = 0; i < CHROMOSOM_SIZE; i++) {
    if (i == 10) {
      printf("-- ");
    }
    printf("|%d| ", chromosom[i]);
  }
  printf("\n");
}

void PrintPopulation(INDIVIDUO* population) {
  int i;

  for (i = 0; i < POPULATION_SIZE; i++) {
    printf("Individuo [%d]: ", i);
    PrintChromosom(population[i].chromosom);
    printf("\n");
  }
}

void PrintFathers(INDIVIDUO father, char index) {
  printf("Father: %d \t", index);
  printf("\n");
}
