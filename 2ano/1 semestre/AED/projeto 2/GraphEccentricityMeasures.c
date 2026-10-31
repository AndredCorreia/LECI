//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphEccentricityMeasures
//

// Student Name :
// Student Number :
// Student Name :
// Student Number :

/*** COMPLETE THE GraphEccentricityMeasuresCompute FUNCTION ***/
/*** COMPLETE THE GraphGetCentralVertices FUNCTION ***/
/*** COMPLETE THE GraphEccentricityMeasuresPrint FUNCTION ***/

#include "GraphEccentricityMeasures.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "Graph.h"
#include "GraphAllPairsShortestDistances.h"

struct _GraphEccentricityMeasures {
  unsigned int*
      centralVertices;  // centralVertices[0] = number of central vertices
                        // array size is (number of central vertices + 1)
  int* eccentricity;    // the eccentricity value of each vertex
  Graph* graph;         // the graph
  int graphRadius;      // the graph radius
  int graphDiameter;    // the graph diameter
};

// Allocate memory
// Compute the vertex eccentricity values
// Compute graph radius and graph diameter
// Compute the set of central vertices
GraphEccentricityMeasures* GraphEccentricityMeasuresCompute(Graph* g) {
    assert(g != NULL);

    unsigned int numVertices = GraphGetNumVertices(g);
    GraphEccentricityMeasures* measures = malloc(sizeof(GraphEccentricityMeasures));
    measures->eccentricity = malloc(numVertices * sizeof(int));
    measures->graph = g;

    int** distances = GraphAllPairsShortestDistancesCompute(g);

    measures->graphRadius = INT_MAX;
    measures->graphDiameter = -1;

    for (unsigned int v = 0; v < numVertices; ++v) {
        int maxDistance = -1;
        for (unsigned int u = 0; u < numVertices; ++u) {
            if (distances[v][u] != -1 && distances[v][u] > maxDistance) {
                maxDistance = distances[v][u];
            }
        }
        measures->eccentricity[v] = maxDistance;

        if (maxDistance < measures->graphRadius) {
            measures->graphRadius = maxDistance;
        }
        if (maxDistance > measures->graphDiameter) {
            measures->graphDiameter = maxDistance;
        }
    }

    unsigned int centralCount = 0;
    for (unsigned int v = 0; v < numVertices; ++v) {
        if (measures->eccentricity[v] == measures->graphRadius) {
            centralCount++;
        }
    }
    measures->centralVertices = malloc((centralCount + 1) * sizeof(unsigned int));
    measures->centralVertices[0] = centralCount;
    centralCount = 1; 
    for (unsigned int v = 0; v < numVertices; ++v) {
        if (measures->eccentricity[v] == measures->graphRadius) {
            measures->centralVertices[centralCount++] = v;
        }
    }

    
    

    return measures;
}


void GraphEccentricityMeasuresDestroy(GraphEccentricityMeasures** p) {
  assert(*p != NULL);

  GraphEccentricityMeasures* aux = *p;

  free(aux->centralVertices);
  free(aux->eccentricity);

  free(*p);
  *p = NULL;
}

// Getting the computed measures

int GraphGetRadius(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  return p->graphRadius;
}

int GraphGetDiameter(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  return p->graphDiameter;
}

int GraphGetVertexEccentricity(const GraphEccentricityMeasures* p,
                               unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));
  assert(p->eccentricity != NULL);

  return p->eccentricity[v];
}

// Getting a copy of the set of central vertices
// centralVertices[0] = number of central vertices in the set
unsigned int* GraphGetCentralVertices(const GraphEccentricityMeasures* p) {
    assert(p != NULL);
    assert(p->centralVertices != NULL);

    unsigned int count = p->centralVertices[0];
    unsigned int* copy = malloc((count + 1) * sizeof(unsigned int));
    for (unsigned int i = 0; i <= count; ++i) {
        copy[i] = p->centralVertices[i];
    }
    return copy;
}


// Print the graph radius and diameter
// Print the vertex eccentricity values
// Print the set of central vertices
void GraphEccentricityMeasuresPrint(const GraphEccentricityMeasures* p) {
    assert(p != NULL);

    printf("Graph Radius: %d\n", p->graphRadius);
    printf("Graph Diameter: %d\n", p->graphDiameter);

    printf("Vertex Eccentricities:\n");
    unsigned int numVertices = GraphGetNumVertices(p->graph);
    for (unsigned int v = 0; v < numVertices; ++v) {
        printf("Vertex %u: %d\n", v, p->eccentricity[v]);
    }

    printf("Central Vertices: ");
    for (unsigned int i = 1; i <= p->centralVertices[0]; ++i) {
        printf("%u ", p->centralVertices[i]);
    }
    printf("\n");
}

