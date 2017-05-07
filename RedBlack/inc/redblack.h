#ifndef REDBLACK_H
#define REDBLACK_H

/*
 * Data Structure for the RedBlack Tree.
 */
typedef struct RedBlack RedBlack;

/*
 * Data Structure for the RedBlack Tree Root.
 */
typedef struct Root Root;

/*
 * Creates a New RedBlack Tree Root.
 */
Root * CreateRoot();

/*
 * Return Grandparent's Node.
 */
RedBlack * Grandparent(RedBlack * rb);

/*
 * Return Brother's Node.
 */
RedBlack * Brother(RedBlack * rb);

/*
 * Return Uncle's Node.
 */
RedBlack * Uncle(RedBlack * rb);

/*
 * Creates a New RedBlack Tree Node.
 */
RedBlack * NewRedblack(int value);
#endif
