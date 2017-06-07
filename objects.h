#ifndef _objects_h_
#define _objects_h_
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define NUM_GEN 24  //_________________ Es necesario cambiar cada prueba

typedef struct {
  float weight;
  float profit;
} OBJECTS;


//______________________________________________Mochila mochila

void PrintObjects(OBJECTS *x);
OBJECTS* GetObjects(char const *argv1, char const *argv2);
OBJECTS* NewObjects(int objects);
OBJECTS* ReadFiles(FILE *fpweight, FILE *fpprofit);




#endif
