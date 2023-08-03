/* Created by Daniel Nappa (dnappa@student.unimelb.edu.au) 11/08/2022 */

/*--------------------------------------------------------------
..Project: Assignment 1
  data.c :
          = data source file containing implementations of functions for
          manipluting footpath structs, nodes and linked lists
----------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "data.h"


/* Reads csv from file stream and creates a linked list of pointers to footpaths
for each line in the csv */
list_t* readFile(FILE* inFile) {
  list_t* list =  newList();

  // create initial nodes and footpaths
  node_t* node = createNode();
  node_t* nextNode;

  // temporary string buffers used for getline
  char* buffer = malloc(sizeof(char) * INIT_SIZE);
  assert(buffer);
  size_t bufferSize = INIT_SIZE;

  getline(&buffer, &bufferSize, inFile); // skip header in csv


  while (getline(&buffer, &bufferSize, inFile) > 0) {
    removeNewline(buffer);

    // position counter along buffer string
    int pos = 0;
    int currPos = 0;

    // create footpath to be stored in the list
    footpath_t* _fp = createFootpath();
    node->fp = _fp;
    insertNode(list, node);
    nextNode = createNode();

    parseField(buffer, &_fp->footpath_id, &pos, &currPos, INT);
    parseField(buffer, _fp->address, &pos, &currPos, STRING);
    parseField(buffer, _fp->clue_sa, &pos, &currPos, STRING);
    parseField(buffer, _fp->asset_type, &pos, &currPos, STRING);
    parseField(buffer, &_fp->deltaz, &pos, &currPos, DOUBLE);
    parseField(buffer, &_fp->distance, &pos, &currPos, DOUBLE);
    parseField(buffer, &_fp->grade1in, &pos, &currPos, DOUBLE);
    parseField(buffer, &_fp->mcc_id, &pos, &currPos, INT);
    parseField(buffer, &_fp->mccid_int, &pos, &currPos, INT);
    parseField(buffer, &_fp->rlmax, &pos, &currPos, DOUBLE);
    parseField(buffer, &_fp->rlmin, &pos, &currPos, DOUBLE);
    parseField(buffer, _fp->segside, &pos, &currPos, STRING);
    parseField(buffer, &_fp->statusid, &pos, &currPos, INT);
    parseField(buffer, &_fp->streetid, &pos, &currPos, INT);
    parseField(buffer, &_fp->street_group, &pos, &currPos, INT);
    parseField(buffer, &_fp->start_lat, &pos, &currPos, DOUBLE);
    parseField(buffer, &_fp->start_lon, &pos, &currPos, DOUBLE);
    parseField(buffer, &_fp->end_lat, &pos, &currPos, DOUBLE);
    parseField(buffer, &_fp->end_lon, &pos, &currPos, DOUBLE);

    // shrink each malloc'd string down to actual string length
    _fp->address = realloc(_fp->address,
      (strlen(_fp->address) + 1)* sizeof(char));
    _fp->clue_sa = realloc(_fp->clue_sa,
      (strlen(_fp->clue_sa) + 1) * sizeof(char));
    _fp->asset_type = realloc(_fp->asset_type,
      (strlen(_fp->asset_type) + 1) * sizeof(char));
    _fp->segside = realloc(_fp->segside,
      (strlen(_fp->segside) + 1) * sizeof(char));
    assert(_fp->address);
    assert(_fp->clue_sa);
    assert(_fp->asset_type);
    assert(_fp->segside);

    node = nextNode;
  }
  free(buffer);
  return list;
}

void removeNewline(char* buffer) {
  buffer[strlen(buffer) - 1] = NULL_BYTE;
}

void parseField(char* buf, void* field, int* numRead, int* currPos, int type) {

  if (type == INT) {
    /* we need to read int fields as a double in case there are decimals
     then cast the double back to an int */
    double* val = (double*) field;
    if (sscanf(buf + *currPos, "%lf,%n", val, numRead) == 1) {
      int int_val = (int) *val;
      int* casted_val = (int*) field;
      *casted_val = int_val;
    }

    else {
      *val = 0;
      *numRead = 1;
    }
  }

  else if (type == STRING) {
    char* str = (char*) field;

    if (*(buf + *currPos) == QUOTE) {
      if (sscanf(buf + *currPos, "\"%[^\"]\",%n", str, numRead) == 1) {
      }

      else {
        str = NULL;
        *numRead = 1;
      }
    }

    // field does not contain quotation marks
    else {
      if (sscanf(buf + *currPos, "%[^,],%n", str, numRead) == 1) {
      }

      else {
        str = NULL;
        *numRead = 1;
      }
    }
  }

  // type is a double
  else {
    double* val = (double*) field;

    if (sscanf(buf + *currPos, "%lf,%n", val, numRead) == 1) {
    }
    else {
      *val = 0;
      *numRead = 1;
    }
  }
  *currPos += *numRead;
}

footpath_t* createFootpath() {
  footpath_t* new = NULL;
  new = calloc(1, sizeof(footpath_t));
  assert(new != NULL);

  new->segside = calloc((MAX_CHARS + 1), sizeof(char));
  new->asset_type = calloc((MAX_CHARS + 1), sizeof(char));
  new->clue_sa = calloc((MAX_CHARS + 1), sizeof(char));
  new->address = calloc((MAX_CHARS + 1), sizeof(char));
  assert(new->segside);
  assert(new->asset_type);
  assert(new->clue_sa);
  assert(new->address);

  return new;
}


node_t* createNode() {
  node_t* new = NULL;
  new = malloc(sizeof(node_t));
  assert(new != NULL);

  new->fp = NULL;
  new->next = NULL;
  return new;
}


list_t* newList() {
  list_t* new = NULL;
  new = malloc(sizeof(list_t));
  assert(new != NULL);

  new->head = NULL;
  return new;
}

node_array_t* createArray() {
  node_array_t* new = NULL;
  new = malloc(sizeof(node_array_t));
  assert(new != NULL);

  new->A = calloc(INIT_SIZE, sizeof(node_t*));
  new->n = 0;
  new->size = INIT_SIZE;
  return new;
}

void insertNode(list_t* list, node_t* node) {
  assert(list && node);
  node_t* curr;

  // is first node in list
  if (!list->head) {
    list->head = node;
    return;
  }

  curr = list->head;
  assert(curr);

  while (curr->next) {
    curr = curr->next;
  }
  curr->next = node;
}

void insertList(node_array_t* nodes, list_t* list) {
  assert(nodes && list);
  node_t* curr;

  // is empty list
  if (!list->head) {
    return;
  }

  curr = list->head;
  assert(curr);

  while (curr) {
    if (nodes->n == nodes->size) {
      nodes->size *= FACTOR;
      nodes->A = realloc(nodes->A, nodes->size * sizeof(node_array_t*));
    }
    nodes->A[nodes->n] = curr;
    nodes->n++;
    curr = curr->next;
  }

}


void freeList(list_t* list) {
  node_t* tmp;
  node_t* next;
  next = list->head;
  assert(next);

  while (next) {
    tmp = next;
    next = next->next;
    freeNode(tmp);
  }
  next = tmp = NULL;
  free(list);
}


void freeNode(node_t* node) {
  free(node->fp->address);
  free(node->fp->clue_sa);
  free(node->fp->asset_type);
  free(node->fp->segside);
  free(node->fp);
  free(node);
}

void freeNodeArray(node_array_t* nodes) {
  free(nodes->A);
  free(nodes);
}

void nodeSwap(node_t* n1, node_t* n2) {
  node_t tmp  = *n1;
  *n1 = *n2;
  *n2 = tmp;
}
