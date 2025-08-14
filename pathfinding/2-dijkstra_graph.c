#include "pathfinding.h"
#include <string.h>
#include <limits.h>

/**
 * struct path_node_s - A node for a temporary path linked list
 * @vertex: Pointer to a graph vertex
 * @next: Pointer to the next node in the list
 */
typedef struct path_node_s
{
	vertex_t const *vertex;
	struct path_node_s *next;
} path_node_t;

/**
 * get_vertex_by_index - Retrieves a vertex from a graph by its index.
 * @graph: Pointer to the graph.
 * @index: The index of the vertex to find.
 *
 * Return: Pointer to the vertex, or NULL if not found.
 */
static vertex_t *get_vertex_by_index(const graph_t *graph, size_t index)
{
	vertex_t *v;

	if (!graph)
		return (NULL);
	v = graph->vertices;
	while (v)
	{
		if (v->index == index)
			return (v);
		v = v->next;
	}
	return (NULL);
}

/**
 * free_path_list - Frees a temporary path linked list.
 * @head: Pointer to the head of the list.
 */
static void free_path_list(path_node_t *head)
{
	path_node_t *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

/**
 * create_path_queue - Creates a queue containing the path from a linked list.
 * @head: Head of the path linked list (in correct order: start -> target).
 *
 * Return: A queue with the path, or NULL on failure.
 */
static queue_t *create_path_queue(path_node_t *head)
{
	queue_t *path = queue_create();
	path_node_t *curr = head;
	char *content_copy;

	if (!path)
		return (NULL);

	while (curr)
	{
		content_copy = strdup(curr->vertex->content);
		if (!content_copy)
		{
			queue_delete(path);
			return (NULL);
		}
		if (!queue_push_back(path, content_copy))
		{
			free(content_copy);
			queue_delete(path);
			return (NULL);
		}
		curr = curr->next;
	}
	return (path);
}

/**
 * dijkstra_graph - Searches for the shortest path from a start to a target
 * vertex in a graph using Dijkstra's algorithm.
 * @graph: Pointer to the graph to go through.
 * @start: Pointer to the starting vertex.
 * @target: Pointer to the target vertex.
 *
 * Return: A queue with the shortest path, or NULL on failure.
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
						vertex_t const *target)
{
	size_t nb_v, i, j, u_idx;
	int *dist, *visited, min_dist;
	vertex_t **pred, *u;
	edge_t *edge;
	queue_t *path = NULL;
	path_node_t *path_head = NULL, *new_node = NULL;
	vertex_t const *curr;

	if (!graph || !start || !target)
		return (NULL);
	nb_v = graph->nb_vertices;
	dist = calloc(nb_v, sizeof(*dist));
	visited = calloc(nb_v, sizeof(*visited));
	pred = calloc(nb_v, sizeof(*pred));
	if (!dist || !visited || !pred)
	{
		free(dist), free(visited), free(pred);
		return (NULL);
	}
	for (i = 0; i < nb_v; i++)
		dist[i] = INT_MAX;
	dist[start->index] = 0;
	for (i = 0; i < nb_v; i++)
	{
		min_dist = INT_MAX, u_idx = (size_t)-1;
		for (j = 0; j < nb_v; j++)
			if (!visited[j] && dist[j] < min_dist)
				min_dist = dist[j], u_idx = j;
		if (u_idx == (size_t)-1 || dist[u_idx] == INT_MAX)
			break;
		u = get_vertex_by_index(graph, u_idx);
		if (!u)
			break;
		visited[u_idx] = 1;
		printf("Checking %s, distance from %s is %d\n",
			   u->content, start->content, dist[u_idx]);
		if (u == target)
			break;
		for (edge = u->edges; edge; edge = edge->next)
			if (dist[u_idx] + edge->weight < dist[edge->dest->index])
			{
				dist[edge->dest->index] = dist[u_idx] + edge->weight;
				pred[edge->dest->index] = u;
			}
	}
	if (dist[target->index] != INT_MAX)
	{
		for (curr = target; curr; curr = pred[curr->index])
		{
			new_node = malloc(sizeof(*new_node));
			if (!new_node)
			{
				free_path_list(path_head), path_head = NULL;
				break;
			}
			new_node->vertex = curr, new_node->next = path_head;
			path_head = new_node;
		}
		if (path_head)
		{
			path = create_path_queue(path_head);
			free_path_list(path_head);
		}
	}
	free(dist), free(visited), free(pred);
	return (path);
}
