/* Created by Daniel Nappa (dnappa@student.unimelb.edu.au) 18/08/2022 */

/*--------------------------------------------------------------
..Project: Assignment 1
  search.c :
          = source file containing implementations for search, index
          construction and sort operations on the dictionary
----------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include <string.h>
#include "search.h"
#include "data.h"


int stdoutSearchAddress(list_t* list, char* address) {
  node_t* curr;
  int numFound = 0;
  curr = list->head;
  assert(curr);

  while (curr) {
    if (!strcmp(curr->fp->address, address)) {
      numFound++;
    }
    curr = curr->next;
  }

  return numFound;
}

void outFileSearchAddress(FILE* outFile, list_t* list, char* address) {
  node_t* curr;
  curr = list->head;
  assert(curr);

  fprintf(outFile, "%s\n", address);
  while (curr) {
    if (!strcmp(curr->fp->address, address)) {
      printFootpath(outFile, curr->fp);
    }
    curr = curr->next;
  }
}

void printFootpath(FILE* outFile, footpath_t* fp) {
  assert(fp);
  fprintf(outFile, "--> footpath_id: %d ||\
 address: %s || clue_sa: %s ||\
 asset_type: %s || deltaz: %.2f ||\
 distance: %.2f || grade1in: %.1f ||\
 mcc_id: %d || mccid_int: %d ||\
 rlmax: %.2f || rlmin: %.2f ||\
 segside: %s || statusid: %d ||\
 streetid: %d || street_group: %d ||\
 start_lat: %f || start_lon: %f || end_lat: %f || end_lon: %f ||\n",
   fp->footpath_id,
   fp->address,
   fp->clue_sa,
   fp->asset_type,
   fp->deltaz,
   fp->distance,
   fp->grade1in,
   fp->mcc_id,
   fp->mccid_int,
   fp->rlmax,
   fp->rlmin,
   fp->segside,
   fp->statusid,
   fp->streetid,
   fp->street_group,
   fp->start_lat,
   fp->start_lon,
   fp->end_lat,
   fp->end_lon);
}

void sortArray(node_array_t* nodes) {

  // Insertion sort implementation for node array
  int j;
  for (int i = 1; i < nodes->n; i++) {
    j = i - 1;
    while (j >= 0 && nodes->A[j + 1]->fp->grade1in
                       < nodes->A[j]->fp->grade1in) {
      nodeSwap(nodes->A[j + 1], nodes->A[j]);
      j--;
    }
  }
}

void searchKey(FILE* outFile, node_array_t* nodes, char* key) {
  double val = atof(key);
  int lo = 0;
  int pos = 0; // position in node array of closest match
  int hi = nodes->n - 1;
  int mid;

  // Binary search implementation
  while (hi - lo > 1) {
      mid = lo + ((hi - lo) / 2);
      if (nodes->A[mid]->fp->grade1in < val) {
          lo = mid;
      }
      else {
          hi = mid;
      }
  }
  if (val - nodes->A[lo]->fp->grade1in <= nodes->A[hi]->fp->grade1in - val) {
      pos = lo;
  }
  else {
    pos = hi;
  }

  printf("%s --> %.1f\n", key, nodes->A[pos]->fp->grade1in);
  fprintf(outFile, "%s\n", key);
  printFootpath(outFile, nodes->A[pos]->fp);

}

