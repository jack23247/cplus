/* Main.c
 * Entry point for the AllocTracker demo.
 *
 * Copyright (c) 2021, Jacopo Maltagliati
 * Released under the BSD 3-Clause License.
 */

// todo doxygen

#include "AllocTracker.h"
#include "stdio.h"
#include "string.h"

#define USE_ALLOC_TRACKER // todo remove

int main() {
#ifdef USE_ALLOC_TRACKER
    AllocTracker__Init();
    int* tmp = NULL;

    for (int i = 0; i < 16; i++) {
        printf("Allocating %d bytes...\n", 16 * i);
        if (i == 7) {
            tmp = (int*)AllocTracker__New(16 * i);
            printf("Saving location %p to temporary storage.\n", tmp);
        }
        AllocTracker__New(16 * i);
    }

    printf("Deallocating record at %p...\t", tmp);
    if (!AllocTracker__Destroy(tmp)) {
        printf("Success.\n");
    } else {
        printf("Failure. (Unexpected!)\n");
    }

    printf("Allocating a large chunk of memory...\n");
    AllocTracker__New(10000000);

    // XXX This operation might be problematic in case malloc() allocates at a
    //  previously free()d location.
    printf("Deallocating non-existing record at %p...\t", tmp);
    if (!AllocTracker__Destroy(tmp)) {
        printf("Success. (Unexpected!)\n");
    } else {
        printf("Failure.\n");
    }

    printf("Allocating a 16 byte char array and storing a string into it...\n");
    char* heap_string = (char*)AllocTracker__New(16);
    strcpy(heap_string, "Hello!\0");
    printf("This string is stored in the heap: \"%s\".\n", heap_string);

    // AllocTracker handles cleanup
    AllocTracker__Exit(EXIT_SUCCESS);
#else // todo remove
    printf("Allocating 1024 bytes...\n");
    malloc(1024);
    printf("Allocating 2048 bytes...\n");
    malloc(2048);
    printf("Allocating 4096 bytes...\n");
    malloc(4096);
    printf("Allocating a 16 byte char array and storing a string into it...\n");
    char* heap_string = (char*)malloc(16);
    strcpy(heap_string, "Hello!\0");
    printf("This string is stored in the heap: \"%s\".\n", heap_string);
    // Here we should manually free() everything
    exit(EXIT_SUCCESS);
#endif
    return 0;
}
