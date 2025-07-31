#include "huffman.h"

/**
 * huffman_extract_and_insert - Extracts two nodes from the priority queue,
 * combines them, and inserts the new node back into the queue.
 * @priority_queue: A pointer to the priority queue
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *node1, *node2, *new_parent;
	symbol_t *sym1, *sym2, *new_symbol;
	size_t freq_sum;

	if (!priority_queue || priority_queue->size < 2)
		return (0);

	node1 = heap_extract(priority_queue);
	node2 = heap_extract(priority_queue);
	if (!node1 || !node2)
		return (0);

	sym1 = (symbol_t *)node1->data;
	sym2 = (symbol_t *)node2->data;
	freq_sum = sym1->freq + sym2->freq;

	new_symbol = symbol_create(-1, freq_sum);
	new_parent = binary_tree_node(NULL, new_symbol);
	if (!new_symbol || !new_parent)
		return (0);

	new_parent->left = node1;
	new_parent->right = node2;
	node1->parent = new_parent;
	node2->parent = new_parent;

	if (!heap_insert(priority_queue, new_parent))
		return (0);

	return (1);
}
