#include "huffman.h"
#include <stdio.h>

/**
 * delete_huffman_tree - Frees a Huffman tree recursively
 * @node: The root of the tree to free
 */
void delete_huffman_tree(binary_tree_node_t *node)
{
	if (!node)
		return;
	delete_huffman_tree(node->left);
	delete_huffman_tree(node->right);
	free(node->data); /* Free the symbol_t struct */
	free(node);
}

/**
 * print_codes_recursive - Traverses the Huffman tree to print codes
 * @node: The current node in the tree
 * @buffer: A buffer to store the binary code string
 * @depth: The current depth in the tree, which is the code length
 */
void print_codes_recursive(binary_tree_node_t *node, char *buffer, int depth)
{
	symbol_t *symbol;

	if (!node)
		return;

	symbol = (symbol_t *)node->data;
	if (!node->left && !node->right)
	{
		if (symbol->data != -1)
		{
			buffer[depth] = '\0';
			printf("%c: %s\n", symbol->data, buffer);
		}
		return;
	}

	buffer[depth] = '0';
	print_codes_recursive(node->left, buffer, depth + 1);

	buffer[depth] = '1';
	print_codes_recursive(node->right, buffer, depth + 1);
}

/**
 * huffman_codes - Builds the Huffman tree and prints the resulting codes
 * @data: An array of characters
 * @freq: An array of associated frequencies
 * @size: The size of the arrays
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	char *buffer;

	if (!data || !freq || size == 0)
		return (0);

	root = huffman_tree(data, freq, size);
	if (!root)
		return (0);

	buffer = malloc(sizeof(char) * size);
	if (!buffer)
	{
		delete_huffman_tree(root);
		return (0);
	}

	print_codes_recursive(root, buffer, 0);

	free(buffer);
	delete_huffman_tree(root);

	return (1);
}