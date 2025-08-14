#include "pathfinding.h"
#include <string.h>

/**
 * create_point - Allocates and initializes a point structure
 * @x: X coordinate
 * @y: Y coordinate
 * Return: A pointer to the created point, or NULL on failure
 */
static point_t *create_point(int x, int y)
{
	point_t *p = malloc(sizeof(*p));

	if (!p)
		return (NULL);
	p->x = x;
	p->y = y;
	return (p);
}

/**
 * backtrack_recursive - Recursive helper to find a path in a 2D array
 * @map: Pointer to the map
 * @rows: Number of rows in the map
 * @cols: Number of columns in the map
 * @curr: Current coordinates
 * @target: Target coordinates
 * @visited: 2D array marking visited cells
 * @path: Queue to store the path
 * Return: 1 if a path is found, otherwise 0
 */
static int backtrack_recursive(char **map, int rows, int cols,
							   point_t const *curr, point_t const *target, char **visited, queue_t *path)
{
	int move_x[] = {1, 0, -1, 0}; /* R, B, L, T */
	int move_y[] = {0, 1, 0, -1};
	int i;
	point_t next;

	if (curr->x < 0 || curr->x >= cols || curr->y < 0 || curr->y >= rows ||
		map[curr->y][curr->x] == '1' || visited[curr->y][curr->x] == 1)
		return (0);

	printf("Checking coordinates [%d, %d]\n", curr->x, curr->y);
	visited[curr->y][curr->x] = 1;

	if (curr->x == target->x && curr->y == target->y)
	{
		queue_push_back(path, create_point(curr->x, curr->y));
		return (1);
	}

	for (i = 0; i < 4; i++)
	{
		next.x = curr->x + move_x[i];
		next.y = curr->y + move_y[i];
		if (backtrack_recursive(map, rows, cols, &next, target, visited, path))
		{
			queue_push_front(path, create_point(curr->x, curr->y));
			return (1);
		}
	}
	return (0);
}

/**
 * backtracking_array - Searches for the first path from a start to a target
 * point within a two-dimensional array.
 * @map: Pointer to a read-only two-dimensional array
 * @rows: Number of rows of map
 * @cols: Number of columns of map
 * @start: Coordinates of the starting point
 * @target: Coordinates of the target point
 * Return: A queue of points from start to target, or NULL on failure
 */
queue_t *backtracking_array(char **map, int rows, int cols,
							point_t const *start, point_t const *target)
{
	queue_t *path;
	char **visited;
	int i;

	if (!map || !start || !target)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);

	visited = malloc(rows * sizeof(char *));
	if (!visited)
	{
		free(path);
		return (NULL);
	}
	for (i = 0; i < rows; i++)
	{
		visited[i] = calloc(cols, sizeof(char));
		if (!visited[i])
		{
			while (i-- > 0)
				free(visited[i]);
			free(visited);
			free(path);
			return (NULL);
		}
	}

	if (!backtrack_recursive(map, rows, cols, start, target, visited, path))
	{
		queue_delete(path);
		path = NULL;
	}

	for (i = 0; i < rows; i++)
		free(visited[i]);
	free(visited);

	return (path);
}
