/* allocTracker.h
 * Definitions for AllocTracker. 
 *
 * Copyright (c) 2021, Jacopo Maltagliati
 * Released under the BSD 3-Clause License.
 */

#ifndef __ALLOC_TRACKER_H
#define __ALLOC_TRACKER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct allocTrackerRecord {
  void* memoryArea;
  struct allocTrackerRecord* nextRecord;
}; 

typedef struct allocTrackerRecord allocTrackerRecord_t;

static allocTrackerRecord_t* allocationTable;

void allocTrackerCreate();
void allocTrackerDestroy();
void allocTrackerExit(int status);

void* allocTrackerNew(size_t size);
void allocTrackerDel(void* memoryArea);

#endif