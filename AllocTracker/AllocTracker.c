/* AllocTracker.c
 * Reference implementation of AllocTracker.
 *
 * Copyright (c) 2021, Jacopo Maltagliati
 * Released under the BSD 3-Clause License.
 */

#include "AllocTracker.h"

void AllocTracker__Init() { AllocTracker__globTable = NULL; } // xxx paranoid?

void AllocTracker__Cleanup() {
    AllocTracker__Record_t* old;
    while (AllocTracker__globTable != NULL) {
        old = AllocTracker__globTable;
        free(old->heap_region);
        AllocTracker__globTable = old->next_record;
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
        AllocTracker__globTable->next_record = NULL;
    } else {  // There's something else in the Allocation Table
        tmp = AllocTracker__globTable;
        AllocTracker__globTable =
            (AllocTracker__Record_t*)malloc(sizeof(AllocTracker__Record_t));
        AllocTracker__globTable->next_record = tmp;
    }
    AllocTracker__globTable->heap_region = malloc(size);
    return (AllocTracker__globTable->heap_region);
}

int AllocTracker__Destroy(void* memory_area) {
    AllocTracker__Record_t* cur = AllocTracker__globTable;
    while (cur->next_record != NULL) {
        if (cur->next_record->heap_region != memory_area) {
            cur = cur->next_record;
            continue;
        } else {
            free(cur->next_record->heap_region);
            AllocTracker__Record_t* tmp = cur->next_record->next_record;
            free(cur->next_record);
            cur->next_record = tmp;
            return AT_OK;
        }
    }
    return AT_NOT_FOUND;
};