#ifndef REDBLACK_H
#define REDBLACK_H

/*
 * Data Structure for the Redblack Tree.
 */
typedef struct Redblack Redblack;

/*
 * Data Structure for the Redblack Tree Root.
 */
typedef struct Root Root;

/*
 * Creates a New Redblack Tree Root.
 */
Root * CreateRoot();

/*
 * Return Grandparent's Node.
 */
Redblack * Grandparent(Redblack * rb);

/*
 * Return Brother's Node.
 */
Redblack * Brother(Redblack * rb);

/*
 * Return Uncle's Node.
 */
Redblack * Uncle(Redblack * rb);
#endif
