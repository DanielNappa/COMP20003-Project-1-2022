/**
* Created by Daniel Nappa (dnappa@student.unimelb.edu.au) 11/08/2022
*/

/*--------------------------------------------------------------
..Project: Assignment 1
  dict1.c :
          = source file for main program
----------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "data.h"
#include "search.h"

int main(int argc, char** argv) {
  FILE* inFile;
  FILE* outFile;
  list_t* data;
  char* address;
  size_t lenAddress = INIT_SIZE;
  int numFound;

  inFile = fopen(argv[2], "r");
  assert(inFile);
  outFile = fopen(argv[3], "w");
  assert(outFile);
  data = readFile(inFile);
  assert(data);
  address = calloc(INIT_SIZE, sizeof(char));
  assert(address);  
  numFound = 0;

  while (getline(&address, &lenAddress, stdin) > 0) {
    removeNewline(address);
    numFound = stdoutSearchAddress(data, address);
    outFileSearchAddress(outFile, data, address);
    if (numFound) {
      printf("%s --> %d\n", address, numFound);
    }
    else {
      printf("%s --> NOTFOUND\n", address);
    }

  }

  free(address);
  freeList(data);
  fclose(inFile);
  fclose(outFile);


  return 0;
}
