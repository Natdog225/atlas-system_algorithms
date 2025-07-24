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
 * add_single_edge - Helper function to add a unidirectional edge.
 * @src_v: The source vertex.
 * @dest_v: The destination vertex.
 * Return: 1 on success, 0 on failure.
 */
static int add_single_edge(vertex_t *src_v, vertex_t *dest_v)
{
	edge_t *new_edge;
	edge_t *current_edge;

	/* Check if edge already exists */
	current_edge = src_v->edges;
	while (current_edge != NULL)
	{
		if (current_edge->dest == dest_v)
			return (1); /* Edge already exists, consider it success */
		current_edge = current_edge->next;
	}

	new_edge = malloc(sizeof(edge_t));
	if (new_edge == NULL)
		return (0);

	new_edge->dest = dest_v;
	new_edge->next = NULL;

	if (src_v->edges == NULL)
	{
		src_v->edges = new_edge;
	}
	else
	{
		current_edge = src_v->edges;
		while (current_edge->next != NULL)
			current_edge = current_edge->next;
		current_edge->next = new_edge;
	}
	src_v->nb_edges++;
	return (1);
}

/**
 * graph_add_edge - Adds an edge between two vertices to an existing graph.
 * @graph: Pointer to the graph to add the edge to.
 * @src: The string identifying the vertex to make the connection from.
 * @dest: The string identifying the vertex to connect to.
 * @type: The type of edge (UNIDIRECTIONAL or BIDIRECTIONAL).
 * Return: 1 on success, or 0 on failure.
 */
int graph_add_edge(graph_t *graph, const char *src,
				   const char *dest, edge_type_t type)
{
	vertex_t *src_v, *dest_v;
	int success_src_to_dest = 0;
	int success_dest_to_src = 0;

	if (graph == NULL || src == NULL || dest == NULL)
		return (0);

	if (strcmp(src, dest) == 0) /* Cannot add an edge from a vertex to itself */
		return (0);

	src_v = find_vertex_by_content(graph, src);
	dest_v = find_vertex_by_content(graph, dest);

	if (src_v == NULL || dest_v == NULL)
		return (0); /* Source or destination vertex not found */

	success_src_to_dest = add_single_edge(src_v, dest_v);
	if (!success_src_to_dest)
		return (0); /* Failed to add first edge */

	if (type == BIDIRECTIONAL)
	{
		success_dest_to_src = add_single_edge(dest_v, src_v);
		if (!success_dest_to_src)
		{
			return (0);
		}
	}

	return (1);
}
