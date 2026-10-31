//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphTransitiveClosure - Transitive Closure of a directed graph
//

// Student Name :
// Student Number :
// Student Name :
// Student Number :

/*** COMPLETE THE GraphComputeTransitiveClosure FUNCTION ***/

#include "GraphTransitiveClosure.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"

// Compute the transitive closure of a directed graph
// Return the computed transitive closure as a directed graph
// Use the Bellman-Ford algorithm
Graph *GraphComputeTransitiveClosure(Graph *g)
{
  assert(g != NULL);
  assert(GraphIsDigraph(g));
  assert(GraphIsWeighted(g) == 0);

  // COMPLETE THE CODE

  // basicamente este algoritmo é para ver se para cada par de vertices(x,y) existe um caminho entre eles

  Graph *TransitiveClosureGraph = GraphCreate(GraphGetNumVertices(g), GraphIsDigraph(g), GraphIsWeighted(g));

  for (int u = 0; u < GraphGetNumVertices(g); u++)
  {

    GraphBellmanFordAlg *resultReturned = GraphBellmanFordAlgExecute(g,
                                                                     u); // resultReturned vai ser distance e predecessor

    for (unsigned int v = 0; v < GraphGetNumVertices(g); v++)
    {
      if (GraphBellmanFordAlgDistance(resultReturned, v) == INT_MAX)
      {
        //adicionar apenas o vertice
      }else{
        GraphAddEdge(TransitiveClosureGraph, u, v);
      }
    }

    GraphBellmanFordAlgDestroy(&resultReturned);
  }
  return TransitiveClosureGraph;
}
