#include "nary_trees.h"

/**
 * max - Returns the maximum of two size_t values
 * @a: First value
 * @b: Second value
 * @return: The larger of a or b
 */
static size_t max(size_t a, size_t b)
{
	return ((a > b) ? a : b);
}

/**
 * diameter_helper - Recursively calculates height and updates diameter
 * @node: Current node in the tree
 * @diameter: Pointer to the diameter variable to update
 *
 * Return: The height of the subtree rooted at @node
 */
static size_t diameter_helper(nary_tree_t const *node, size_t *diameter)
{
	size_t deepest = 0, second_deepest = 0, height;
	nary_tree_t const *child;

	if (!node)
		return (0);

	for (child = node->children; child; child = child->next)
	{
		height = diameter_helper(child, diameter);
		if (height > deepest)
		{
			second_deepest = deepest;
			deepest = height;
		}
		else if (height > second_deepest)
		{
			second_deepest = height;
		}
	}

	*diameter = max(*diameter, deepest + second_deepest + 1);
	return (deepest + 1);
}

/**
 * nary_tree_diameter - Computes the diameter of an N-ary tree.
 * @root: Pointer to the root node of the tree.
 *
 * Return: The diameter of the tree.
 */
size_t nary_tree_diameter(nary_tree_t const *root)
{
	size_t diameter = 0;

	if (!root)
		return (0);

	diameter_helper(root, &diameter);
	return (diameter);
}