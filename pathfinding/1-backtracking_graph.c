#include "pathfinding.h"
#include <string.h>

/**
 * backtrack_graph_recursive - Recursive helper to find a path in a graph
 * @curr: Current vertex
 * @target: Target vertex
 * @visited: Array marking visited vertices by their index
 * @path: Queue to store the path
 * Return: 1 if a path is found, otherwise 0
 */
static int backtrack_graph_recursive(vertex_t const *curr,
									 vertex_t const *target, char *visited, queue_t *path)
{
	edge_t *edge;

	if (!curr || visited[curr->index])
		return (0);

	printf("Checking %s\n", curr->content);
	visited[curr->index] = 1;

	if (curr == target)
	{
		queue_push_back(path, strdup(curr->content));
		return (1);
	}

	for (edge = curr->edges; edge; edge = edge->next)
	{
		if (backtrack_graph_recursive(edge->dest, target, visited, path))
		{
			queue_push_front(path, strdup(curr->content));
			return (1);
		}
	}
	return (0);
}

/**
 * backtracking_graph - Searches for the first path from a start to a target
 * @graph: Pointer to the graph to go through
 * @start: Pointer to the starting vertex
 * @target: Pointer to the target vertex
 * Return: A queue of city names from start to target, or NULL on failure
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
							vertex_t const *target)
{
	queue_t *path;
	char *visited;

	if (!graph || !start || !target)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);

	visited = calloc(graph->nb_vertices, sizeof(char));
	if (!visited)
	{
		free(path);
		return (NULL);
	}

	if (!backtrack_graph_recursive(start, target, visited, path))
	{
		queue_delete(path);
		path = NULL;
	}

	free(visited);
	return (path);
}
