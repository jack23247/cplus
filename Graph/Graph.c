//
// Created by quartz on 14/12/21.
//

#include "Graph.h"

Graph__t* Graph__New(const size_t vertices, Graph__Vertex_t* vertex_list) {
    Graph__t* tmp = (Graph__t*)AllocTracker__New(sizeof(Graph__t));
    tmp->vertices = vertices;
    // Allocate a row of n pointers with <n=vertices>
    tmp->edge_matrix = AllocTracker__New(vertices * sizeof(float*));
    for (size_t i = 0; i < vertices; i++) {
        // Allocate n columns of n floats with <n=vertices>
        tmp->edge_matrix[i] = AllocTracker__New(vertices * sizeof(float));
        for (size_t j = 0; j < vertices; j++) {
            tmp->edge_matrix[i][j] = 0.0;
        }
    }
    return tmp;
}

Graph__Vertex_t* Graph__StringToVertexList(char* string, char sep, size_t* vertices) {
    size_t i = 0;
    size_t j = 0;
    Graph__Vertex_t* ret;
    Graph__Vertex_t* tmp =
        (Graph__Vertex_t*)AllocTracker__New(sizeof(Graph__Vertex_t));
    *vertices = 0;
    ret = tmp;
    while (string[i] != '\0') {
        if (string[i] == sep) {
            for (; j < 4; j++) tmp->name[j] = '\0';
            j = 0;
            tmp->next =
                (Graph__Vertex_t*)AllocTracker__New(sizeof(Graph__Vertex_t));
            tmp = tmp->next;
            (*vertices)++;
        } else if (j < 4) {
            tmp->name[j] = string[i];
            j++;
        }
        i++;
    }
    return ret;
}

int Graph__LookupVertex(const Graph__t* graph, const Graph__Vertex_t* vertex) {
    int count = 0;
    Graph__Vertex_t* cur = graph->vertex_list;
    if (cur == NULL) return -1;
    do {
        if (strcmp(cur->name, vertex->name)) return count;
        count++;
        cur = cur->next;
    } while (cur != NULL);
    return -1;
}

Graph__Edge_t* Graph__ReadEdge(Graph__t* graph, Graph__Vertex_t* src,
                               Graph__Vertex_t* dest) {}

void Graph__WriteEdge(Graph__t* graph, Graph__Vertex_t* src,
                      Graph__Vertex_t* dest);

void Graph__ExportEdges(Graph__t* graph, char sep);

void Graph__ImportEdges(const char sep);
