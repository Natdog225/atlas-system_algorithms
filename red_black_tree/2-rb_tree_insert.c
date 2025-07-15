#include "rb_trees.h"

static rb_tree_t *bst_insert(rb_tree_t **root_ptr, rb_tree_t *parent, int value);
static void left_rotate(rb_tree_t **root_ptr, rb_tree_t *node);
static void right_rotate(rb_tree_t **root_ptr, rb_tree_t *node);
static void fix_insert_violations(rb_tree_t **root_ptr, rb_tree_t *new_node);
static rb_tree_t *get_grandparent(rb_tree_t *node);
static rb_tree_t *get_uncle(rb_tree_t *node);

/**
 * bst_insert - Helper function for standard BST insertion
 * @root_ptr: Double pointer to the root of the tree
 * @parent: The current parent node in the recursion (NULL for initial call)
 * @value: The value to insert
 *
 * Return: Pointer to the newly created node, or NULL on failure/duplicate.
 */
static rb_tree_t *bst_insert(rb_tree_t **root_ptr, rb_tree_t *parent, int value)
{
	rb_tree_t *new_node = NULL;
	rb_tree_t *current = *root_ptr;

	if (current == NULL)
	{
		// Found insertion point, create node
		new_node = rb_tree_node(parent, value, RED); // New nodes are always RED
		if (parent == NULL)
			*root_ptr = new_node; // If it's the first node, it's the root
		return (new_node);
	}

	if (value < current->n)
	{
		if (current->left == NULL)
		{
			new_node = rb_tree_node(current, value, RED);
			current->left = new_node;
			return (new_node);
		}
		return (bst_insert(&(current->left), current, value));
	}
	else if (value > current->n)
	{
		if (current->right == NULL)
		{
			new_node = rb_tree_node(current, value, RED);
			current->right = new_node;
			return (new_node);
		}
		return (bst_insert(&(current->right), current, value));
	}
	return (NULL); // Value already exists, ignore
}

/**
 * left_rotate - Performs a left rotation on a Red-Black Tree node
 * @root_ptr: Double pointer to the root of the tree
 * @node: The node to rotate around (pivot)
 */
static void left_rotate(rb_tree_t **root_ptr, rb_tree_t *node)
{
	rb_tree_t *right_child = node->right;

	node->right = right_child->left;
	if (right_child->left != NULL)
		right_child->left->parent = node;

	right_child->parent = node->parent;
	if (node->parent == NULL)
		*root_ptr = right_child;
	else if (node == node->parent->left)
		node->parent->left = right_child;
	else
		node->parent->right = right_child;

	right_child->left = node;
	node->parent = right_child;
}

/**
 * right_rotate - Performs a right rotation on a Red-Black Tree node
 * @root_ptr: Double pointer to the root of the tree
 * @node: The node to rotate around (pivot)
 */
static void right_rotate(rb_tree_t **root_ptr, rb_tree_t *node)
{
	rb_tree_t *left_child = node->left;

	node->left = left_child->right;
	if (left_child->right != NULL)
		left_child->right->parent = node;

	left_child->parent = node->parent;
	if (node->parent == NULL)
		*root_ptr = left_child;
	else if (node == node->parent->right)
		node->parent->right = left_child;
	else
		node->parent->left = left_child;

	left_child->right = node;
	node->parent = left_child;
}

/**
 * get_grandparent - Gets the grandparent of a node
 * @node: Pointer to the node
 * Return: Pointer to the grandparent, or NULL if not exists
 */
static rb_tree_t *get_grandparent(rb_tree_t *node)
{
	if (node && node->parent)
		return (node->parent->parent);
	return (NULL);
}

/**
 * get_uncle - Gets the uncle of a node
 * @node: Pointer to the node
 * Return: Pointer to the uncle, or NULL if not exists
 */
static rb_tree_t *get_uncle(rb_tree_t *node)
{
	rb_tree_t *grandparent = get_grandparent(node);

	if (grandparent == NULL)
		return (NULL);

	if (node->parent == grandparent->left)
		return (grandparent->right);
	else
		return (grandparent->left);
}

/**
 * fix_insert_violations - Fixes Red-Black Tree properties after insertion
 * @root_ptr: Double pointer to the root of the tree
 * @new_node: The newly inserted node (which is RED)
 */
static void fix_insert_violations(rb_tree_t **root_ptr, rb_tree_t *new_node)
{
	rb_tree_t *parent = NULL;
	rb_tree_t *grandparent = NULL;
	rb_tree_t *uncle = NULL;

	// Loop while new_node is not root and its parent is RED
	while (new_node != *root_ptr && new_node->parent->color == RED)
	{
		parent = new_node->parent;
		grandparent = get_grandparent(new_node);

		if (grandparent == NULL) // Should not happen if parent is RED and not root
			break;

		// Case A: Parent is left child of grandparent
		if (parent == grandparent->left)
		{
			uncle = grandparent->right;

			// Case 1: Uncle is RED (recoloring)
			if (uncle != NULL && uncle->color == RED)
			{
				parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				new_node = grandparent; // Move up the tree to check grandparent
			}
			// Case 2 & 3: Uncle is BLACK (racist much?) or NULL (rotations and recoloring)
			else
			{
				// Case 2: new_node is right child (Left-Right case)
				if (new_node == parent->right)
				{
					left_rotate(root_ptr, parent);
					new_node = parent;		   // new_node becomes parent after rotation
					parent = new_node->parent; // parent also updates
				}
				// Case 3: new_node is left child (Left-Left case)
				right_rotate(root_ptr, grandparent);
				parent->color = BLACK;
				grandparent->color = RED;
			}
		}
		// Case B: Parent is right child of grandparent (symmetric to Case A)
		else
		{
			uncle = grandparent->left;

			// Case 1: Uncle is RED (recoloring)
			if (uncle != NULL && uncle->color == RED)
			{
				parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				new_node = grandparent;
			}
			// Case 2 & 3: Uncle is BLACK or NULL (rotations and recoloring)
			else
			{
				// Case 2: new_node is left child (Right-Left case)
				if (new_node == parent->left)
				{
					right_rotate(root_ptr, parent);
					new_node = parent;
					parent = new_node->parent;
				}
				// Case 3: new_node is right child (Right-Right case)
				left_rotate(root_ptr, grandparent);
				parent->color = BLACK;
				grandparent->color = RED;
			}
		}
	}
	(*root_ptr)->color = BLACK; // Root must always be BLACK
}

/**
 * rb_tree_insert - Inserts a value in a Red-Black Tree
 * @tree: Double pointer to the root node of the Red-Black tree to insert the value in
 * @value: The value to store in the node to be inserted
 *
 * Return: A pointer to the created node, or NULL on failure.
 * If value is already present, returns NULL.
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *new_node;

	if (tree == NULL)
		return (NULL);

	new_node = bst_insert(tree, NULL, value); // Insert as BST node (initial color RED)
	if (new_node == NULL)
		return (NULL); // Value already exists or malloc failed

	fix_insert_violations(tree, new_node); // Fix Red-Black properties

	return (new_node);
}