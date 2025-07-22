#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * find_vertex_by_content - Helper function to find a vertex by its content.
 * @graph: Pointer to the graph.
 * @str: The content string to search for.
 * Return: Pointer to the vertex if found, NULL otherwise.
 */
static vertex_t *find_vertex_by_content(graph_t *graph, const char *str)
{
	vertex_t *current_vertex;

	if (graph == NULL || str == NULL)
		return (NULL);

	current_vertex = graph->vertices;
	while (current_vertex != NULL)
	{
		if (strcmp(current_vertex->content, str) == 0)
			return (current_vertex);
		current_vertex = current_vertex->next;
	}
	return (NULL);
}

/**
 * graph_add_vertex - Adds a vertex to an existing graph.
 * @graph: Pointer to the graph to add the vertex to.
 * @str: The string to store in the new vertex.
 * Return: Pointer to the created vertex, or NULL on failure.
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new_vertex;
	vertex_t *current_vertex;

	if (graph == NULL || str == NULL)
		return (NULL);

	/* Check if a vertex with the same content already exists */
	if (find_vertex_by_content(graph, str) != NULL)
		return (NULL);

	new_vertex = malloc(sizeof(vertex_t));
	if (new_vertex == NULL)
		return (NULL);

	new_vertex->content = strdup(str);
	if (new_vertex->content == NULL)
	{
		free(new_vertex);
		return (NULL);
	}

	new_vertex->nb_edges = 0;
	new_vertex->edges = NULL;
	new_vertex->next = NULL;

	/* Add the new vertex to the end of the adjacency list */
	if (graph->vertices == NULL)
	{
		graph->vertices = new_vertex;
	}
	else
	{
		current_vertex = graph->vertices;
		while (current_vertex->next != NULL)
			current_vertex = current_vertex->next;
		current_vertex->next = new_vertex;
	}
	new_vertex->index = graph->nb_vertices;
	graph->nb_vertices++;
	return (new_vertex);
}
