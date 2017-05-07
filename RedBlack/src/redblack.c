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