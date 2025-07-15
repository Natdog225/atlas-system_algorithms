#include "rb_trees.h"

/* Forward declarations for static helper functions */
static int is_bst_util(const rb_tree_t *tree, int min_val, int max_val);
static int check_color_properties(const rb_tree_t *node);
static int get_black_height(const rb_tree_t *node, int *black_count);

/**
 * is_bst_util - Helper function to check if a binary tree is a valid BST
 * @tree: Pointer to the current node
 * @min_val: Minimum allowed value for nodes in this subtree
 * @max_val: Maximum allowed value for nodes in this subtree
 *
 * Return: 1 if the subtree is a valid BST, 0 otherwise
 */
static int is_bst_util(const rb_tree_t *tree, int min_val, int max_val)
{
	if (tree == NULL)
		return (1); // An empty tree is a valid BST

	if (tree->n < min_val || tree->n > max_val)
		return (0);

	return (is_bst_util(tree->left, min_val, tree->n - 1) &&
			is_bst_util(tree->right, tree->n + 1, max_val));
}

/**
 * check_color_properties - Helper to check Red-Black color rules
 * (No adjacent reds, valid colors)
 * @node: Pointer to the current node
 *
 * Return: 1 if color properties are valid for the subtree, 0 otherwise
 */
static int check_color_properties(const rb_tree_t *node)
{
	if (node == NULL)
		return (1); // Base case: NULL node is valid

	// Check for RED parent with RED child (no adjacent reds)
	if (node->color == RED && node->parent != NULL && node->parent->color == RED)
		return (0);

	// Ensure colors are only RED or BLACK (DOUBLE_BLACK is for deletion and shouldn't be permanent)
	if (node->color != RED && node->color != BLACK)
		return (0);

	// Recursively check children
	return (check_color_properties(node->left) &&
			check_color_properties(node->right));
}

/**
 * get_black_height - Helper to calculate black height and check consistency
 * @node: Pointer to the current node
 * @black_count: Pointer to an int to store black node count for current path
 *
 * Return: 1 if black height is consistent for paths in this subtree, 0 otherwise
 * Updates black_count with the number of black nodes on path to this node.
 */
static int get_black_height(const rb_tree_t *node, int *black_count)
{
	int left_bh = 0;
	int right_bh = 0;
	int left_result;
	int right_result;

	if (node == NULL)
	{
		*black_count = 1; // Path to NULL node (leaf) counts as 1 black node
		return (1);
	}

	left_result = get_black_height(node->left, &left_bh);
	right_result = get_black_height(node->right, &right_bh);

	if (!left_result || !right_result || left_bh != right_bh)
		return (0); // Inconsistent black height or invalid subtree

	*black_count = left_bh; // Black height from this node down
	if (node->color == BLACK)
		(*black_count)++; // Increment if current node is black

	return (1);
}

/**
 * rb_tree_is_valid - Checks if a binary tree is a valid Red-Black Tree
 * @tree: Pointer to the root node of the tree to check
 *
 * Return: 1 if tree is a valid Red-Black Tree, and 0 otherwise.
 * 0 if tree is NULL.
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
	int black_height_check = 0;

	if (tree == NULL)
		return (0);

	// Property 2: Root of tree is always black.
	if (tree->color != BLACK)
		return (0);

	// Property 1: A Red-Black Tree is a BST
	if (!is_bst_util(tree, -2147483648, 2147483647)) // Min/Max int values
		return (0);

	// Property 3: No two adjacent red nodes (A red node cannot have a red parent or red child).
	// Property: Every node has a color either red or black.
	if (!check_color_properties(tree))
		return (0);

	// Property 4: Every path from root to a NULL node has same number of black nodes.
	return (get_black_height(tree, &black_height_check));
}
