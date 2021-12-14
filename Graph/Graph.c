/* Graph.c
 * Implementation of a compact graph G(V,E) and of some algorithms.
 *
 * Copyright (c) 2021, Jacopo Maltagliati
 * Released under the BSD 3-Clause License.
 */

#include "Graph.h"

/**
 *
 * @param vertices
 * @param vertex_list
 * @return
 */
Graph__t* Graph__New(const size_t vertices, Graph__Vertex_t* vertex_list) {
    Graph__t* tmp = NULL;
    tmp = (Graph__t*)AllocTracker__New(sizeof(Graph__t));
    tmp->vertices = vertices;
    tmp->vertex_list = vertex_list;
    // Allocate a row of n pointers with <n=vertices>
    tmp->edge_matrix = AllocTracker__New(vertices * sizeof(float*));
    for (size_t i = 0; i < vertices; i++) {
        // Allocate n columns of n floats with <n=vertices>
        tmp->edge_matrix[i] = AllocTracker__New(vertices * sizeof(float));
        for (size_t j = 0; j < vertices; j++) {
            tmp->edge_matrix[i][j] = (float)0.0;
        }
    }
    return tmp;
}

Graph__Vertex_t* Graph__StringToVertexList(const char* string, const char sep,
                                           size_t* vertices) {
    Graph__Vertex_t* ret = NULL;
    Graph__Vertex_t* tmp = NULL;
    char* buf = NULL;
    char* name = NULL;
    tmp = (Graph__Vertex_t*)AllocTracker__New(sizeof(Graph__Vertex_t));
    *vertices = 1;
    tmp->next = NULL;
    ret = tmp;
    buf = (char*)AllocTracker__New(strlen(string) + 1);
    memcpy(buf, string, strlen(string) + 1);
    name = strtok(buf, &sep);
    while (name != NULL) {
        // memset(tmp->name,0,4); // xxx useful?
        strncpy(tmp->name, name, 4);
        name = strtok(NULL, &sep);
        if(name == NULL) continue;
        tmp->next =
            (Graph__Vertex_t*)AllocTracker__New(sizeof(Graph__Vertex_t));
        tmp->next->next = NULL;
        (*vertices)++;
        tmp = tmp->next;
    }
    AllocTracker__Destroy(buf);
    return ret;
}

void Graph__CompileEdgeMatrix(const char* string, char sep, char next,
                              Graph__t* graph) { // todo loop->strtok()
    size_t i = 0, j = 0;
    int a, b;
    size_t sect = 0;
    char tmp[4];
    char src[5];
    char dest[5];
    while (string[i] != '\0') {
        if (string[i] == next) {
            // if there's no trailing sep before next (e.g.) "a,b,1.0;"
            a = Graph__LookupVertexByName(graph, src);
            b = Graph__LookupVertexByName(graph, dest);
            if (a < 0 || b < 0) return;
            graph->edge_matrix[a][b] = strtof(tmp, NULL);
            // float x = strtof(tmp, NULL);
            sect = 0;
            j = 0;
            i++;
            continue;
        }
        if (string[i] == sep) {
            for (; j < 4; j++) tmp[j] = '\0';
            switch (sect) {
                case 0:
                    memcpy(src, tmp, 4);
                    src[4] = '\0';
                    break;
                case 1:
                    memcpy(dest, tmp, 4);
                    dest[4] = '\0';
                    break;
                case 2:
                    // if there's a trailing sep before next (e.g.) "a,b,1.0,;"
                    a = Graph__LookupVertexByName(graph, src);
                    b = Graph__LookupVertexByName(graph, dest);
                    if (a < 0 || b < 0) return;
                    graph->edge_matrix[a][b] = strtof(tmp, NULL);
                    break;
                default:
                    printf(
                        "Graph__CompileEdgeMatrix: panic, malformed string.\n");
                    AllocTracker__Exit(EXIT_FAILURE);
            }
            sect++;
            j = 0;
        } else if (j < 4) {
            tmp[j] = string[i];
            j++;
        }
        i++;
    }
}

int Graph__LookupVertexByName(const Graph__t* graph, const char* name) {
    if (graph == NULL || name == NULL) return -1;
    int count = 0;
    Graph__Vertex_t* cur = graph->vertex_list;
    if (cur == NULL) return -1;
    do {
        if (!strcmp(cur->name, name)) return count;
        count++;
        cur = cur->next;
    } while (cur != NULL);
    return -1;
}