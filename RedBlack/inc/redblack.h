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
RedBlack * GrandParent(RedBlack * rb);

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
RedBlack * NewRedBlack(int value);

/*
 * Rotate left a RedBlack Tree Node.
 */
void RotateLeft(Root * root, RedBlack * rb);

/*
 * Rotate right a RedBlack Tree Node.
 */
void RotateRight(Root * root, RedBlack * rb);

/*
 * Replace an old Node for a new Node.
 */
void ReplaceNode(Root * root, RedBlack * oldRb, RedBlack * newRb);


/*
 * Add a new Node in RedBlack Tree.
 */
void AddRedBlackTree(Root * root, int value);

/*
 * Try every possible case in the Add function.
 */
void AddCase1(Root * root, RedBlack * rb);
void AddCase2(Root * root, RedBlack * rb);
void AddCase3(Root * root, RedBlack * rb);
void AddCase4(Root * root, RedBlack * rb);
void AddCase5(Root * root, RedBlack * rb);

/*
 * Print all the tree in pre-order.
 */
void PrintPreorder(RedBlack * root);

/*
 * Return the Root Node.
 */
RedBlack * RootNode(Root * root);
#endif
