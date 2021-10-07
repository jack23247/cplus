/* allocTracker.h
 * Source code for AllocTracker. 
 *
 * Copyright (c) 2021, Jacopo Maltagliati
 * Released under the BSD 3-Clause License.
 */

#include "allocTracker.h"

void allocTrackerCreate() {
  allocationTable = NULL;
  return;
}

void allocTrackerDestroy() {
  // TODO use allocTrackerDel()
  allocTrackerRecord_t* old;
  while(allocationTable != NULL) {
    old=allocationTable;
    free(old->memoryArea);
    allocationTable=old->nextRecord;
    free(old);
  } 
  return;
}

void allocTrackerExit(int status) {
  allocTrackerDestroy();
  exit(status);
}

void* allocTrackerNew(size_t size) {
  allocTrackerRecord_t* tmp;
  if (allocationTable == NULL) { // The Allocation Table's empty
    allocationTable = 
        (allocTrackerRecord_t*)malloc(sizeof(allocTrackerRecord_t));
    allocationTable->nextRecord = NULL;
  } else { // There's something else in the Allocation Table
    tmp = allocationTable;
    allocationTable =
      (allocTrackerRecord_t*)malloc(sizeof(allocTrackerRecord_t));
    allocationTable->nextRecord = tmp;
  }
  allocationTable->memoryArea = malloc(size);
  return (allocationTable->memoryArea);
}

// TODO Implement void allocTrackerDel(void* memoryArea);