#include "heap.h"

/**
 * heapify_down - Restores the min-heap property from the root down
 * @heap: Pointer to the heap
 */
static void heapify_down(heap_t *heap)
{
	binary_tree_node_t *current = heap->root, *child;
	void *temp;

	while (current->left)
	{
		child = current->left;
		if (current->right && heap->data_cmp(current->right->data, child->data) < 0)
			child = current->right;

		if (heap->data_cmp(current->data, child->data) < 0)
			break;

		temp = current->data;
		current->data = child->data;
		child->data = temp;
		current = child;
	}
}

/**
 * heap_extract - Extracts the root value of a Min Binary Heap
 * @heap: Pointer to the heap from which to extract the value
 *
 * Return: Pointer to the data from the root node, or NULL on failure
 */
void *heap_extract(heap_t *heap)
{
	void *data;
	binary_tree_node_t *last_node, *temp_node;
	size_t mask;

	if (!heap || heap->size == 0)
		return (NULL);
	data = heap->root->data;
	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size--;
		return (data);
	}
	mask = 1;
	while ((mask << 1) <= heap->size)
		mask <<= 1;
	temp_node = heap->root;
	while (mask > 1)
	{
		mask >>= 1;
		if (heap->size & mask)
			temp_node = temp_node->right;
		else
			temp_node = temp_node->left;
	}
		last_node = temp_node;
		heap->root->data = last_node->data;
		if (last_node->parent->left == last_node)
			last_node->parent->left = NULL;
		else
			last_node->parent->right = NULL;
			heap->size--;
		free(last_node);
		heapify_down(heap);
		return (data);
	}
