#include "objects.h"

OBJECTS* GetObjects(char const *argv1, char const *argv2) {
  FILE *fpA=NULL, *fpB=NULL;
	OBJECTS *objects;
	const char *weight=NULL, *profit=NULL;

	weight = argv1;
	profit = argv2;
	//Abrir archivos
  fpA=fopen(weight,"rt");
  fpB=fopen(profit,"rt");

  if(fpA==NULL || fpB==NULL){ printf("\n\n\tNo se pudo abrir algun archivo.\n"); return NULL; }
  //Leer archivos
  objects = ReadFiles(fpA, fpB);
  fclose(fpA);
  fclose(fpB);
  if(objects == NULL){ printf("\n\n\tNo se guardaron correctamente los datos.\n"); }

  PrintObjects(objects);

  return objects;
}


void PrintObjects(OBJECTS *x) {
  unsigned int i;

  for (i = 0; i < NUM_GEN; i++) {
    //printf("Weight[%d] = %f", i, x[i].weight);
    //printf("\tProfit[%d] = %f\n", i, x[i].profit);
  }

}

OBJECTS* NewObjects(int objects) {
	OBJECTS *x;

	x = (OBJECTS*)malloc(objects*sizeof(OBJECTS));
	if(x == NULL) return NULL;

	return x;
}

OBJECTS* ReadFiles(FILE *fpweight, FILE *fpprofit) {
	char buff[100];
	int weightObjects, profitObjects, i = 0;
	OBJECTS *X=NULL;

	fgets(buff,100,fpweight);
	weightObjects=atoi(buff);
  fgets(buff,100,fpprofit);
	profitObjects=atoi(buff);
	//fgets(buff,100,fp);
	//colu=atoi(buff);
	//n=reng*colu;

	if(weightObjects != profitObjects) return NULL;
  if(weightObjects < 1) return NULL;

	X = NewObjects(weightObjects);

	while(!feof(fpweight) && !feof(fpprofit) && i < weightObjects)
	{
		fgets(buff,100,fpweight);
		X[i].weight = atof(buff);
    fgets(buff,100,fpprofit);
		X[i].profit = atof(buff);
		i++;
	}

	if(i < weightObjects) {
    free(X);
    return NULL;
  }

	return X;
}
