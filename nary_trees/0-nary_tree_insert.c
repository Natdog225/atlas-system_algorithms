#include "nary_trees.h"

/**
 * nary_tree_insert - Inserts a node in a N-ary tree.
 * @parent: Pointer to the parent node.
 * @str: The string to be stored in the created node.
 *
 * Return: A pointer to the created node, or NULL on failure.
 */
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *new_node;

	new_node = malloc(sizeof(nary_tree_t));
	if (!new_node)
		return (NULL);

	new_node->content = strdup(str);
	if (!new_node->content)
	{
		free(new_node);
		return (NULL);
	}

	new_node->parent = parent;
	new_node->nb_children = 0;
	new_node->children = NULL;
	new_node->next = NULL;

	if (parent)
	{
		new_node->next = parent->children;
		parent->children = new_node;
		parent->nb_children++;
	}

	return (new_node);
}