/* Created by Daniel Nappa (dnappa@student.unimelb.edu.au) 11/08/2022 */

/*--------------------------------------------------------------
..Project: Assignment 1
  data.h :
          = data header for nodes, linked list and footpath structs
----------------------------------------------------------------*/

#ifndef _DATA_H
#define _DATA_H

#define INIT_SIZE 2
#define FACTOR 2
#define MAX_CHARS 128
#define MAX_LENGTH 512
#define QUOTE '\"'
#define NULL_BYTE '\0'
#define TRUE 1
#define FALSE 0
#define INT 0
#define STRING 1
#define DOUBLE 2


typedef struct footpath footpath_t;
typedef struct node node_t;
typedef struct list list_t;
typedef struct node_array node_array_t;

struct footpath {
  int footpath_id;
  char* address;
  char* clue_sa;
  char* asset_type;
  double deltaz;
  double distance;
  double grade1in;
  int mcc_id;
  int mccid_int;
  double rlmax;
  double rlmin;
  char* segside;
  int statusid;
  int streetid;
  int street_group;
  double start_lat;
  double start_lon;
  double end_lat;
  double end_lon;
};

struct node {
  footpath_t* fp;
  node_t* next;
};

struct list {
  node_t* head;
};

struct node_array {
  node_t** A;
  int n;
  int size;
};

/* Reads csv from file stream and creates a linked list of pointers to footpaths
for each line in the csv */
list_t* readFile(FILE* inFile);

/* Removes newline from buffer string */
void removeNewline(char* buffer);

/* Parses csv string and stores value in footpath according to given type */
void parseField(char* buf, void* field, int* numRead, int* currPos, int type);

/* Creates an empty footpath node */
footpath_t* createFootpath();

/* Creates an empty node */
node_t* createNode();

/* Creates an empty list */
list_t* newList();

/* Creates an empty nodes array struct */
node_array_t* createArray();

/* Inserts node into list */
void insertNode(list_t* list, node_t* node);

/* Inserts all node pointers from list into node array struct */
void insertList(node_array_t* nodes, list_t* list);

/* Frees a list given its pointer */
void freeList(list_t* list);

/* Frees a node */
void freeNode(node_t* node);

/* Frees a node array struct */
void freeNodeArray(node_array_t* nodes);

/* Swap function that swaps node pointers for sortArray */
void nodeSwap(node_t* n1, node_t* n2);

#endif
