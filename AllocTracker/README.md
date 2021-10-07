# AllocTracker

A trivial memory allocation tracker.

## What

A system to track, create and remove memory allocations.

## Why

To avoid memory leaks, to provide centralized global allocation control and to free every possible memory allocation in case of an handled exception.

## How

*snip*

## Results

### Leak test w/ `malloc()`

```
==1131== Memcheck, a memory error detector
==1131== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1131== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==1131== Command: ./leakTest
==1131== 
Allocating 1024 bytes...
Allocating 2048 bytes...
Allocating 4096 bytes...
Allocating a 16 byte char array and storing a string into it...
This string is stored in the heap: "Hello!".
==1131== 
==1131== HEAP SUMMARY:
==1131==     in use at exit: 7,184 bytes in 4 blocks
==1131==   total heap usage: 5 allocs, 1 frees, 11,280 bytes allocated
==1131== 
==1131== 1,024 bytes in 1 blocks are definitely lost in loss record 2 of 4
==1131==    at 0x4C31B0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==1131==    by 0x108883: main (in /home/runner/cplus/AllocTracker/leakTest)
==1131== 
==1131== 2,048 bytes in 1 blocks are definitely lost in loss record 3 of 4
==1131==    at 0x4C31B0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==1131==    by 0x108899: main (in /home/runner/cplus/AllocTracker/leakTest)
==1131== 
==1131== 4,096 bytes in 1 blocks are definitely lost in loss record 4 of 4
==1131==    at 0x4C31B0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==1131==    by 0x1088AF: main (in /home/runner/cplus/AllocTracker/leakTest)
==1131== 
==1131== LEAK SUMMARY:
==1131==    definitely lost: 7,168 bytes in 3 blocks
==1131==    indirectly lost: 0 bytes in 0 blocks
==1131==      possibly lost: 0 bytes in 0 blocks
==1131==    still reachable: 16 bytes in 1 blocks
==1131==         suppressed: 0 bytes in 0 blocks
==1131== Reachable blocks (those to which a pointer was found) are not shown.
==1131== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==1131== 
==1131== For counts of detected and suppressed errors, rerun with: -v
==1131== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
```

### Leak test w/ `allocTrackerNew()`

```
==1139== Memcheck, a memory error detector
==1139== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1139== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==1139== Command: ./leakTest
==1139== 
Allocating 1024 bytes...
Allocating 2048 bytes...
Allocating 4096 bytes...
Allocating a 16 byte char array and storing a string into it...
This string is stored in the heap: "Hello!".
==1139== 
==1139== HEAP SUMMARY:
==1139==     in use at exit: 0 bytes in 0 blocks
==1139==   total heap usage: 9 allocs, 9 frees, 11,344 bytes allocated
==1139== 
==1139== All heap blocks were freed -- no leaks are possible
==1139== 
==1139== For counts of detected and suppressed errors, rerun with: -v
==1139== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```