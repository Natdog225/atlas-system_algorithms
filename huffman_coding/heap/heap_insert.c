#include "heap.h"

/**
 * find_parent_node - Finds the parent for the next node to be inserted
 * @root: The root of the heap
 * @new_node_idx: The 1-based index of the new node to be inserted
 * Return: The parent node for new node
 */
static binary_tree_node_t *find_parent_node(binary_tree_node_t *root,
											size_t new_node_idx)
{
	size_t parent_idx = new_node_idx / 2;
	size_t mask = 1;

	if (parent_idx == 0)
		return (NULL);
	if (parent_idx == 1)
		return (root);

	while ((mask << 1) <= parent_idx)
		mask <<= 1;
	mask >>= 1;

	while (mask > 0)
	{
		if (parent_idx & mask)
			root = root->right;
		else
			root = root->left;
		mask >>= 1;
	}
	return (root);
}

/**
 * heap_insert - Inserts a value in a Min Binary Heap
 * @heap: Pointer to the heap in which to insert the node
 * @data: Pointer containing the data to store in the new node
 *
 * Return: Pointer to the created node containing data, or NULL on failure
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new_node, *parent;
	void *temp;

	if (!heap || !data)
		return (NULL);

	if (heap->root == NULL)
	{
		heap->root = binary_tree_node(NULL, data);
		heap->size++;
		return (heap->root);
	}
	parent = find_parent_node(heap->root, heap->size + 1);
	new_node = binary_tree_node(parent, data);
	if (!new_node)
		return (NULL);
	if ((heap->size + 1) % 2 == 0)
		parent->left = new_node;
	else
		parent->right = new_node;
	heap->size++;

	/* Heapify up (suit up ) */
	while (new_node->parent &&
		   heap->data_cmp(new_node->data, new_node->parent->data) < 0)
	{
		temp = new_node->data;
		new_node->data = new_node->parent->data;
		new_node->parent->data = temp;
		new_node = new_node->parent;
	}
	return (new_node);
}
