/* Created by Daniel Nappa (dnappa@student.unimelb.edu.au) 18/08/2022 */

/*--------------------------------------------------------------
..Project: Assignment 1
  search.h :
          = header for prototypes for search, index
          construction and sort operations on the dictionary
----------------------------------------------------------------*/
#include <float.h>
#include "data.h"

#ifndef _SEARCH_H
#define _SEARCH_H

/* Simple linear search that searches the list for matching addresses
and returns number of times the address was found */
int stdoutSearchAddress(list_t* list, char* address);

/* Simple linear search that searches the list for matching addresses
and prints matching footpaths to outFile filestream */
void outFileSearchAddress(FILE* outFile, list_t* list, char* address);

/* Prints formatted details about footpath to filestream */
void printFootpath(FILE* outFile, footpath_t* fp);

/* Sorts node array in ascending order */
void sortArray(node_array_t* nodes);

/* Searches node array for given grade1in value, if not found returns closest
value, with the closest matching footpath being output to outFile filestream */
void searchKey(FILE* outFile, node_array_t* nodes, char* key);

#endif
