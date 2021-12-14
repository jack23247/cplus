//
// Created by quartz on 14/12/21.
//

#ifndef __GRAPH_H
#define __GRAPH_H

#include "../AllocTracker/AllocTracker.h"
#include "stdbool.h"
#include "string.h"

/*enum Graph__EdgeDir {
    none,
    forward,   // a --> b
    backward,  // a <-- b
    both       // a <--> b
};*/

struct Graph__Vertex {
    char name[4];
    struct Graph__Vertex* next;
};

struct Graph__Edge {
    struct Graph__Vertex* src;
    struct Graph__Vertex* dest;
    float weight;
};

struct Graph__ {
    size_t vertices;
    struct Graph__Vertex* vertex_list;
    float** edge_matrix;
};

// typedef enum Graph__EdgeDir Graph__EdgeDir_t;

typedef struct Graph__Vertex Graph__Vertex_t;
typedef struct Graph__Edge Graph__Edge_t;

typedef struct Graph__ Graph__t;

Graph__t* Graph__New(const size_t vertices, Graph__Vertex_t* vertex_list);

Graph__Vertex_t* Graph__StringToVertexList(char* string, char sep,
                                           size_t* vertices);

int Graph__LookupVertex(const Graph__t* graph, const Graph__Vertex_t* vertex);

Graph__Edge_t* Graph__ReadEdge(Graph__t* graph, Graph__Vertex_t* src,
                               Graph__Vertex_t* dest);

void Graph__WriteEdge(Graph__t* graph, Graph__Vertex_t* src,
                      Graph__Vertex_t* dest);

void Graph__ExportEdges(Graph__t* graph, char sep);

void Graph__ImportEdges(const char sep);

#endif  // __GRAPH_H
