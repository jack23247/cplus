/* AllocTracker.h
 * Reference definitions for AllocTracker.
 *
 * Copyright (c) 2021, Jacopo Maltagliati
 * Released under the BSD 3-Clause License.
 */

#ifndef __ALLOCTRACKER_H
#define __ALLOCTRACKER_H

#include <stdlib.h>

#define AT_OK 0
#define AT_NOT_FOUND 1

struct AllocTracker__Record {
  void* heapRegion;
  struct AllocTracker__Record* nextRecord;
};

/* // todo btree version
struct AllocTracker__LRRecord { // Left -> Smaller, Right -> Bigger
    void* heapRegion;
    size_t regionSize;
    struct AllocTracker__LRRecord* nextRecordL;
    struct AllocTracker__LRRecord* nextRecordR;
};
*/

typedef struct AllocTracker__Record AllocTracker__Record_t;

static AllocTracker__Record_t* AllocTracker__globTable;

void AllocTracker__Init();
void AllocTracker__Cleanup();
void AllocTracker__Exit(int status);

void* AllocTracker__New(size_t size);
int AllocTracker__Destroy(void* memoryArea);

#endif  // __ALLOCTRACKER_H