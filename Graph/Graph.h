/* Graph.c
* Definitions for a compact graph G(V,E) and of some algorithms.
*
* Copyright (c) 2021, Jacopo Maltagliati
* Released under the BSD 3-Clause License.
 */


#ifndef __GRAPH_H
#define __GRAPH_H

#include "../AllocTracker/AllocTracker.h"
#include "stdbool.h"
#include "string.h"
#include "stdio.h"

/*enum Graph__EdgeDir {
    none,
    forward,   // a --> b
    backward,  // a <-- b
    both       // a <--> b
};*/

struct Graph__Vertex {
    char name[5];
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

Graph__Vertex_t* Graph__StringToVertexList(const char* string, const char sep,
                                           size_t* vertices);

int Graph__LookupVertexByName(const Graph__t* graph, const char* name);

inline int Graph__LookupVertex(const Graph__t* graph, const Graph__Vertex_t* vertex) {
    return Graph__LookupVertexByName(graph, vertex->name);
}

void Graph__CompileEdgeMatrix(const char* string, char sep, char next,
                              Graph__t* graph);

bool Graph__VertexCover(Graph__t* graph, char* test_set);

/*
Graph__Edge_t* Graph__ReadEdge(Graph__t* graph, Graph__Vertex_t* src,
                               Graph__Vertex_t* dest);

void Graph__WriteEdge(Graph__t* graph, Graph__Vertex_t* src,
                      Graph__Vertex_t* dest);

void Graph__ExportEdges(Graph__t* graph, char sep);

void Graph__ImportEdges(const char sep);
*/
#endif  // __GRAPH_H
