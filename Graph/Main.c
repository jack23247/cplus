/* Main.c
* Entry point for the Graph demo.
*
* Copyright (c) 2021, Jacopo Maltagliati
* Released under the BSD 3-Clause License.
*/

#include "Graph.h"
#include "stdio.h"

int main(void) {
    Graph__Vertex_t* vlist;
    size_t vsize;
    Graph__t* g1;
    AllocTracker__Init();
    vlist = Graph__StringToVertexList("pippo,pluto,pap,11,g,7,", ',', &vsize);
    g1 = Graph__New(vsize, vlist);
    Graph__CompileEdgeMatrix("pippo,pluto,3.14;11,g,1;", ',', ';', g1);
    //printf("Test: %s\n", g1->name);
    AllocTracker__Exit(0);
}