//
// Created by quartz on 14/12/21.
//

#include "Graph.h"
#include "stdio.h"

int main(void) {
    AllocTracker__Init();
    Graph__Vertex_t* vlist;
    size_t vsize;
    vlist = Graph__StringToVertexList("pippo,pluto,pap,11,g,7,", ',', &vsize);
    Graph__t* g1;
    g1 = Graph__New(vsize, vlist);
    //printf("Test: %s\n", g1->name);
    AllocTracker__Exit(0);
}