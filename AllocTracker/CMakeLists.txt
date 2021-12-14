add_library(AllocTracker
        AllocTracker.c
        AllocTracker.h)

add_executable(AllocTrackerDemo
        Main.c)

target_link_libraries(AllocTrackerDemo AllocTracker)
