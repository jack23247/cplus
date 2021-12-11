/* AllocTracker.c
 * Reference implementation of AllocTracker.
 *
 * Copyright (c) 2021, Jacopo Maltagliati
 * Released under the BSD 3-Clause License.
 */

#include "AllocTracker.h"

void AllocTracker__Init() { AllocTracker__globTable = NULL; }

void AllocTracker__Cleanup() {
    AllocTracker__Record_t* old;
    while (AllocTracker__globTable != NULL) {
        old = AllocTracker__globTable;
        free(old->heapRegion);
        AllocTracker__globTable = old->nextRecord;
        free(old);
    }
}

void AllocTracker__Exit(int status) {
    AllocTracker__Cleanup();
    exit(status);
}

void* AllocTracker__New(size_t size) {
    AllocTracker__Record_t* tmp;
    if (AllocTracker__globTable == NULL) {  // The Allocation Table's empty
        AllocTracker__globTable =
            (AllocTracker__Record_t*)malloc(sizeof(AllocTracker__Record_t));
        AllocTracker__globTable->nextRecord = NULL;
    } else {  // There's something else in the Allocation Table
        tmp = AllocTracker__globTable;
        AllocTracker__globTable =
            (AllocTracker__Record_t*)malloc(sizeof(AllocTracker__Record_t));
        AllocTracker__globTable->nextRecord = tmp;
    }
    AllocTracker__globTable->heapRegion = malloc(size);
    return (AllocTracker__globTable->heapRegion);
}

int AllocTracker__Destroy(void* heapRegion) {
    AllocTracker__Record_t* cur = AllocTracker__globTable;
    while (cur->nextRecord != NULL) {
        if (cur->nextRecord->heapRegion != heapRegion) {
            cur = cur->nextRecord;
            continue;
        } else {
            free(cur->nextRecord->heapRegion);
            AllocTracker__Record_t* tmp = cur->nextRecord->nextRecord;
            free(cur->nextRecord);
            cur->nextRecord = tmp;
            return AT_OK;
        }
    }
    return AT_NOT_FOUND;
};