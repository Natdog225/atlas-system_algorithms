#include "nary_trees.h"

/**
 * nary_tree_delete - Deallocates an entire N-ary tree.
 * @tree: Pointer to the root of the tree to delete.
 */
void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *child, *next_child;

	if (!tree)
		return;

	child = tree->children;
	while (child)
	{
		next_child = child->next;
		nary_tree_delete(child);
		child = next_child;
	}

	free(tree->content);
	free(tree);
}