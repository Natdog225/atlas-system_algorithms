# Graphs

This project implements a graph data structure in C, utilizing an adjacency list representation. It includes functionalities for creating a graph, adding vertices and edges, deleting the entire graph, and traversing the graph using both Depth-First Search (DFS) and Breadth-First Search (BFS algorithms.)

## Table of Contents

- [General](#general)
- [Data Structures](#data-structures)
- [Compilation](#compilation)
- [Tasks](#tasks)
  - [0. Create graph](#0-create-graph)
  - [1. Add a vertex](#1-add-a-vertex)
  - [2. Add an edge](#2-add-an-edge)
  - [3. Delete graph](#3-delete-graph)
  - [4. Depth-first traversal](#4-depth-first-traversal)
  - [5. Breadth-first traversal](#5-breadth-first-traversal)
- [Author](#author)

## General

- Allowed editors: `vi`, `vim`, `emacs`
- All files will be compiled on Ubuntu 20.04 LTS.
- C programs and functions will be compiled with `gcc 9.4.0` using the flags `-Wall -Werror -Wextra -pedantic`.
- All files should end with a new line.
- The code adheres to the Betty style.
- No global variables are allowed.
- No more than 5 functions per file.
- The standard library is allowed.
- Prototypes of all functions are included in the `graphs.h` header file.
- All header files are include guarded.

## Data Structures

The following structures are used to represent the graph:

```c
/**
 * enum edge_type_e - Enumerates the different types of
 * connection between two vertices
 *
 * @UNIDIRECTIONAL: The connection is made only in one way
 * @BIDIRECTIONAL: The connection is made in two ways
 */
typedef enum edge_type_e
{
    UNIDIRECTIONAL = 0,
    BIDIRECTIONAL
} edge_type_t;

/* Define the structure temporarily for usage in the edge_t */
typedef struct vertex_s vertex_t;

/**
 * struct edge_s - Node in the linked list of edges for a given vertex
 * A single vertex can have many edges
 *
 * @dest: Pointer to the connected vertex
 * @next: Pointer to the next edge
 */
typedef struct edge_s
{
    vertex_t    *dest;
    struct edge_s   *next;
} edge_t;


/**
 * struct vertex_s - Node in the linked list of vertices in the adjacency list
 *
 * @index: Index of the vertex in the adjacency list.
 * @content: Custom data stored in the vertex (here, a string)
 * @nb_edges: Number of conenctions with other vertices in the graph
 * @edges: Pointer to the head node of the linked list of edges
 * @next: Pointer to the next vertex in the adjacency linked list
 * This pointer points to another vertex in the graph, but it
 * doesn't stand for an edge between the two vertices
 */
struct vertex_s
{
    size_t      index;
    char        *content;
    size_t      nb_edges;
    edge_t      *edges;
    struct vertex_s *next;
};

/**
 * struct graph_s - Representation of a graph
 * We use an adjacency linked list to represent our graph
 *
 * @nb_vertices: Number of vertices in our graph
 * @vertices: Pointer to the head node of our adjacency linked list
 */
typedef struct graph_s
{
    size_t      nb_vertices;
    vertex_t    *vertices;
} graph_t;