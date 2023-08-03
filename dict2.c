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
  node_array_t* A;
  char* key;
  size_t lenKey = INIT_SIZE;
  key = calloc(INIT_SIZE, sizeof(char));
  assert(key);



  inFile = fopen(argv[2], "r");
  assert(inFile);
  outFile = fopen(argv[3], "w");
  assert(outFile);
  data = readFile(inFile);
  assert(data);
  A = createArray();
  insertList(A, data);
  sortArray(A);

  while (getline(&key, &lenKey, stdin) > 0) {
    removeNewline(key);
    searchKey(outFile, A, key);
  }





  freeList(data);
  freeNodeArray(A);
  free(key);
  fclose(inFile);
  fclose(outFile);


  return 0;
}
