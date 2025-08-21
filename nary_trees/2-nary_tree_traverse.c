#include "nary_trees.h"

/**
 * traverse_and_get_depth - Recursively traverses tree and finds max depth.
 * @node: Pointer to the current node.
 * @depth: The depth of the current node.
 * @action: Pointer to a function to execute for each node.
 *
 * Return: The maximum depth of the subtree starting at @node.
 */
static size_t traverse_and_get_depth(nary_tree_t const *node, size_t depth,
									 void (*action)(nary_tree_t const *node, size_t depth))
{
	nary_tree_t const *child;
	size_t max_depth = 0, child_depth;

	if (!node)
		return (depth - 1);

	action(node, depth);
	max_depth = depth;

	for (child = node->children; child; child = child->next)
	{
		child_depth = traverse_and_get_depth(child, depth + 1, action);
		if (child_depth > max_depth)
			max_depth = child_depth;
	}

	return (max_depth);
}

/**
 * nary_tree_traverse - Goes through an N-ary tree, node by node.
 * @root: Pointer to the root node of the tree to traverse.
 * @action: Pointer to a function to execute for each node.
 *
 * Return: The biggest depth of the tree.
 */
size_t nary_tree_traverse(nary_tree_t const *root,
						  void (*action)(nary_tree_t const *node, size_t depth))
{
	if (!root)
		return (0);

	return (traverse_and_get_depth(root, 0, action));
}
