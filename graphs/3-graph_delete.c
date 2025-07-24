#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * graph_delete - Completely deletes a graph.
 * @graph: Pointer to the graph to delete.
 */
void graph_delete(graph_t *graph)
{
	vertex_t *current_vertex;
	vertex_t *temp_vertex;
	edge_t *current_edge;
	edge_t *temp_edge;

	if (graph == NULL)
		return;

	current_vertex = graph->vertices;
	while (current_vertex != NULL)
	{
		current_edge = current_vertex->edges;
		while (current_edge != NULL)
		{
			temp_edge = current_edge;
			current_edge = current_edge->next;
			free(temp_edge);
		}
		free(current_vertex->content); /* Free the duplicated string */
		temp_vertex = current_vertex;
		current_vertex = current_vertex->next;
		free(temp_vertex);
	}

	free(graph);
}
