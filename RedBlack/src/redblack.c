#include "../inc/redblack.h"
#include <stdlib.h>

struct RedBlack {

    int value;
    char color; // r = Red, b = Black
    struct RedBlack* parent;
    struct RedBlack * right;
    struct RedBlack * left;
};

struct Root {
    RedBlack * root;
};

Root * CreateRoot() {
    Root * root = malloc(sizeof(Root));
    root->root = NULL;
    return root;
}

RedBlack * Grandparent(RedBlack * rb) {
    return rb->parent->parent;
}

RedBlack * Brother(RedBlack * rb) {
    if(rb == rb->parent->left) {
        return rb->parent->right;
    } else {
        return rb->parent->left;
    }
}

RedBlack * Uncle(RedBlack * rb) {
    return Brother(rb->parent);
}

RedBlack * NewRedblack(int value) {
    RedBlack * newRedBlack = malloc(sizeof(RedBlack));
    newRedBlack->value = value;
    newRedBlack->color = 'r';
    newRedBlack->left = NULL;
    newRedBlack->right = NULL;
    newRedBlack->parent = NULL;
    return newRedBlack;
}

void RotateLeft(Root * root, RedBlack * rb) {
    RedBlack * r = rb->right;
    ReplaceNode(root, rb, r);
    rb->right = r->left;
    if (r->left != NULL) {
        r->left->parent = rb;
    }
    r->left = rb;
    rb->parent = r;
}

void RotateRight(Root * root, RedBlack * rb) {
    RedBlack * l = rb->left;
    ReplaceNode(root, rb, l);
    rb->left = l->right;
    if (l->right != NULL) {
        l->right->parent = rb;
    }
    l->right = rb;
    rb->parent = l;
}

void ReplaceNode(Root * root, RedBlack * oldRb, RedBlack * newRb) {
    if (oldRb->parent == NULL) {
        root->root = newRb;
    } else {
        if (oldRb == oldRb->parent->left)
            oldRb->parent->left = newRb;
        else
            oldRb->parent->right = newRb;
    }
    if (newRb != NULL) {
        newRb->parent = oldRb->parent;
    }
}