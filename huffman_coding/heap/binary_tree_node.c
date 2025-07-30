#include "heap.h"

/**
 * binary_tree_node - Creates a generic Binary Tree node
 * @parent: A pointer to the parent node of the node to create
 * @data: The data to store in the new node
 *
 * Return: A pointer to the created node, or NULL on failure
 */
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *new_node;

	new_node = malloc(sizeof(binary_tree_node_t));
	if (!new_node)
		return (NULL);

	new_node->data = data;
	new_node->parent = parent;
	new_node->left = NULL;
	new_node->right = NULL;

	return (new_node);
}
