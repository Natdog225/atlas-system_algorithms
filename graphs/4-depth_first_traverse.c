#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graphs.h"


/**
 * dfs_recursive - Helper function for depth_first_traverse.
 * @vertex: The current vertex being visited.
 * @visited: An array to keep track of visited vertices.
 * @depth: The current depth of the traversal.
 * @action: The action function to call for each visited vertex.
 * @max_depth_ptr: Pointer to store the maximum depth found.
 */
static void dfs_recursive(const vertex_t *vertex, int *visited,
						  size_t depth, void (*action)(const vertex_t *v, size_t depth), size_t *max_depth_ptr)
{
	edge_t *edge;

	if (vertex == NULL || visited == NULL || action == NULL)
		return;

	visited[vertex->index] = 1; /* Mark as visited */
	action(vertex, depth);

	if (depth > *max_depth_ptr)
		*max_depth_ptr = depth;

	edge = vertex->edges;
	while (edge != NULL)
	{
		if (edge->dest != NULL && visited[edge->dest->index] == 0)
		{
			dfs_recursive(edge->dest, visited, depth + 1, action, max_depth_ptr);
		}
		edge = edge->next;
	}
}

/**
 * depth_first_traverse - Goes through a graph using the depth-first algorithm.
 * @graph: Pointer to the graph to traverse. The traversal must start from
 * the first vertex in the vertices list.
 * @action: Pointer to a function to be called for each visited vertex.
 * v -> A const pointer to the visited vertex.
 * depth -> The depth of v, from the starting vertex.
 * Return: The biggest vertex depth, or 0 on failure.
 */
size_t depth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth))
{
	int *visited = NULL;
	size_t max_depth = 0;
	size_t i;

	if (graph == NULL || action == NULL || graph->vertices == NULL)
		return (0);

	/* Allocate and initialize visited array */
	visited = malloc(sizeof(int) * graph->nb_vertices);
	if (visited == NULL)
		return (0);

	for (i = 0; i < graph->nb_vertices; i++)
		visited[i] = 0;

	dfs_recursive(graph->vertices, visited, 0, action, &max_depth);

	free(visited);
	return (max_depth);
}