#include <stdlib.h>
#include <string.h> /* For memset */
#include "graphs.h"

/**
 * struct queue_node_s - Node for the queue used in BFS.
 * @vertex: Pointer to the vertex.
 * @depth: Depth of the vertex.
 * @next: Pointer to the next node in the queue.
 */
typedef struct queue_node_s
{
	const vertex_t *vertex;
	size_t depth;
	struct queue_node_s *next;
} queue_node_t;

/**
 * enqueue - Adds a node to the end of the queue.
 * @head: Pointer to the head of the queue.
 * @tail: Pointer to the tail of the queue.
 * @vertex: The vertex to enqueue.
 * @depth: The depth of the vertex.
 * Return: 1 on success, 0 on failure.
 */
static int enqueue(queue_node_t **head, queue_node_t **tail,
				   const vertex_t *vertex, size_t depth)
{
	queue_node_t *new_node;

	new_node = malloc(sizeof(queue_node_t));
	if (new_node == NULL)
		return (0);

	new_node->vertex = vertex;
	new_node->depth = depth;
	new_node->next = NULL;

	if (*tail == NULL)
	{
		*head = new_node;
		*tail = new_node;
	}
	else
	{
		(*tail)->next = new_node;
		*tail = new_node;
	}
	return (1);
}

/**
 * dequeue - Removes and returns the front node from the queue.
 * @head: Pointer to the head of the queue.
 * @tail: Pointer to the tail of the queue.
 * Return: Pointer to the dequeued node, or NULL if queue is empty.
 */
static queue_node_t *dequeue(queue_node_t **head, queue_node_t **tail)
{
	queue_node_t *temp;

	if (*head == NULL)
		return (NULL);

	temp = *head;
	*head = (*head)->next;
	if (*head == NULL) /* If queue becomes empty */
		*tail = NULL;

	return (temp);
}

/**
 * breadth_first_traverse - Goes through a graph using the breadth-first algorithm.
 * @graph: Pointer to the graph to traverse. The traversal must start from
 * the first vertex in the vertices list.
 * @action: Pointer to a function to be called for each visited vertex.
 * v -> A const pointer to the visited vertex.
 * depth -> The depth of v, from the starting vertex.
 * Return: The biggest vertex depth, or 0 on failure.
 */
size_t breadth_first_traverse(const graph_t *graph, void (*action)(const vertex_t *v, size_t depth))
{
	int *visited = NULL;
	queue_node_t *head = NULL;
	queue_node_t *tail = NULL;
	queue_node_t *current_q_node;
	size_t max_depth = 0;
	size_t i;
	edge_t *edge;

	if (graph == NULL || action == NULL || graph->vertices == NULL)
		return (0);

	/* Allocate and initialize visited array */
	visited = malloc(sizeof(int) * graph->nb_vertices);
	if (visited == NULL)
		return (0);
	for (i = 0; i < graph->nb_vertices; i++)
		visited[i] = 0;

	/* Enqueue the starting vertex (first in the list) */
	if (!enqueue(&head, &tail, graph->vertices, 0))
	{
		free(visited);
		return (0); /* Enqueue failed */
	}
	visited[graph->vertices->index] = 1;

	while (head != NULL)
	{
		current_q_node = dequeue(&head, &tail);
		if (current_q_node == NULL)
			break; /* Should not happen if head is not NULL */

		action(current_q_node->vertex, current_q_node->depth);

		if (current_q_node->depth > max_depth)
			max_depth = current_q_node->depth;

		edge = current_q_node->vertex->edges;
		while (edge != NULL)
		{
			if (edge->dest != NULL && visited[edge->dest->index] == 0)
			{
				if (!enqueue(&head, &tail, edge->dest, current_q_node->depth + 1))
				{
					/* Handle allocation failure for enqueue:
					 * Free remaining queue nodes and visited array.
					 */
					while (head != NULL)
					{
						current_q_node = dequeue(&head, &tail);
						free(current_q_node);
					}
					free(visited);
					free(current_q_node); /* Free the current node as well */
					return (0);
				}
				visited[edge->dest->index] = 1;
			}
			edge = edge->next;
		}
		free(current_q_node);
	}

	free(visited);
	return (max_depth);
}