#include "huffman.h"

/**
 * symbol_cmp - Compares two symbols based on frequency for the min heap.
 * @p1: Pointer to the first node's data (a nested binary_tree_node_t)
 * @p2: Pointer to the second node's data (a nested binary_tree_node_t)
 *
 * Return: The difference in frequencies of the two symbols
 */
int symbol_cmp(void *p1, void *p2)
{
	binary_tree_node_t *node1 = (binary_tree_node_t *)p1;
	binary_tree_node_t *node2 = (binary_tree_node_t *)p2;
	symbol_t *sym1 = (symbol_t *)node1->data;
	symbol_t *sym2 = (symbol_t *)node2->data;

	return (sym1->freq - sym2->freq);
}

/**
 * huffman_priority_queue - Creates a priority queue for Huffman coding
 * @data: An array of characters
 * @freq: An array of associated frequencies
 * @size: The size of the arrays
 *
 * Return: A pointer to the created min heap, or NULL on failure
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *pq;
	size_t i;
	symbol_t *symbol;
	binary_tree_node_t *node;

	if (!data || !freq || size == 0)
		return (NULL);

	pq = heap_create(symbol_cmp);
	if (!pq)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		node = binary_tree_node(NULL, symbol);
		if (!symbol || !node || !heap_insert(pq, node))
		{
			/* Simple cleanup, assuming full cleanup handled by caller, ideally */
			return (NULL);
		}
	}
	return (pq);
}
