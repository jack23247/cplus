add_library(Graph
        Graph.c
        Graph.h)

target_link_libraries(Graph AllocTracker)

add_executable(GraphDemo
        Main.c)

target_link_libraries(GraphDemo Graph)