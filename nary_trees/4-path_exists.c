#include "nary_trees.h"

/**
 * path_exists - Checks if a path exists in an N-ary tree.
 * @root: Pointer to the root node of the tree.
 * @path: A NULL terminated array of strings representing the path.
 *
 * Return: 1 if the path exists, 0 otherwise.
 */
int path_exists(nary_tree_t const *root, char const *const *path)
{
	nary_tree_t const *current_node = root;
	nary_tree_t const *child;
	size_t i = 1;

	if (!root || !path || !*path)
		return (0);

	if (strcmp(root->content, path[0]) != 0)
		return (0);

	while (path[i])
	{
		child = current_node->children;
		current_node = NULL; /* Reset for current level search */

		while (child)
		{
			if (strcmp(child->content, path[i]) == 0)
			{
				current_node = child;
				break;
			}
			child = child->next;
		}

		if (!current_node)
			return (0); /* Path segment not found */
		i++;
	}

	return (1);
}
