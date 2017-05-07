#include "../inc/redblack.h"
#include <stdlib.h>

struct Redblack {

    int value;
    char color; // r = Red, b = Black
    struct Redblack * parent;
    struct Redblack * right;
    struct Redblack * left;
};

struct Root {
    Redblack * root;
};

Root * CreateRoot() {
    Root * root = malloc(sizeof(Root));
    root->root = NULL;
    return root;
}

Redblack * Grandparent(Redblack * rb) {
    return rb->parent->parent;
}

Redblack * Brother(Redblack * rb) {
    if(rb == rb->parent->left) {
        return rb->parent->right;
    } else {
        return rb->parent->left;
    }
}

Redblack * Uncle(Redblack * rb) {
    return Brother(rb->parent);
}