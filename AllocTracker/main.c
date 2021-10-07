/* main.c
 * Entry point for the AllocTracker demo. 
 *
 * Copyright (c) 2021, Jacopo Maltagliati
 * Released under the BSD 3-Clause License.
 */

#include "allocTracker.h"

/*
static inline void nullptrCatcher(const void* pointer) {
  if (!pointer) {
    printf("The program generated a null pointer exception.\t Exiting...\n");
    allocTrackerExit(EXIT_FAILURE);
  }
  return;
}
*/

int main() {
#ifdef USE_ALLOC_TRACKER
  allocTrackerCreate();
  printf("Allocating 1024 bytes...\n");
  allocTrackerNew(1024);
  printf("Allocating 2048 bytes...\n");
  allocTrackerNew(2048);
  printf("Allocating 4096 bytes...\n");
  allocTrackerNew(4096);
  printf("Allocating a 16 byte char array and storing a string into it...\n");
  char* heapString = (char *) allocTrackerNew(16);
  strcpy(heapString, "Hello!\0");
  printf("This string is stored in the heap: \"%s\".\n", heapString);
  // AllocTracker handles cleanup
  allocTrackerExit(EXIT_SUCCESS);
#else
  printf("Allocating 1024 bytes...\n");
  malloc(1024);
  printf("Allocating 2048 bytes...\n");
  malloc(2048);
  printf("Allocating 4096 bytes...\n");
  malloc(4096);
  printf("Allocating a 16 byte char array and storing a string into it...\n");
  char* heapString = (char *) malloc(16);
  strcpy(heapString, "Hello!\0");
  printf("This string is stored in the heap: \"%s\".\n", heapString);
  // Here we should manually free() everything
  exit(EXIT_SUCCESS);
#endif
  return 0;
}
