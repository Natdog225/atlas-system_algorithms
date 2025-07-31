#include "heap.h"

/**
 * delete_tree_recursive - Deletes a binary tree recursively
 * @node: The current node to process
 * @free_data: Function to free the data in a node
 */
void delete_tree_recursive(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (!node)
		return;

	delete_tree_recursive(node->left, free_data);
	delete_tree_recursive(node->right, free_data);

	if (free_data)
		free_data(node->data);

	free(node);
}

/**
 * heap_delete - Deallocates a heap
 * @heap: Pointer to the heap to delete
 * @free_data: Pointer to a function to free the node content
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (!heap)
		return;

	delete_tree_recursive(heap->root, free_data);
	free(heap);
}