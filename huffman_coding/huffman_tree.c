#include "huffman.h"

/**
 * huffman_tree - Builds the Huffman tree
 * @data: An array of characters
 * @freq: An array of associated frequencies
 * @size: The size of the arrays
 *
 * Return: A pointer to the root node of the Huffman tree, or NULL on failure
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *pq;
	binary_tree_node_t *huffman_root = NULL;

	if (!data || !freq || size == 0)
		return (NULL);

	pq = huffman_priority_queue(data, freq, size);
	if (!pq)
		return (NULL);

	while (pq->size > 1)
	{
		if (!huffman_extract_and_insert(pq))
		{
			/* On failure, a full cleanup would be needed */
			heap_delete(pq, NULL); /* Simplistic cleanup */
			return (NULL);
		}
	}

	if (pq->size == 1)
		huffman_root = heap_extract(pq);

	free(pq);

	return (huffman_root);
}
