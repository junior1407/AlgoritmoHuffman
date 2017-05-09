#include "../inc/redblack.h"
#include <stdlib.h>
#include <stdio.h>

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

RedBlack * GrandParent(RedBlack * rb) {
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

RedBlack * NewRedBlack(int value) {
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

void AddRedBlackTree(Root * root, int value) {
    RedBlack * newRedBlack = NewRedBlack(value);
    if (root->root == NULL) {
        root->root = newRedBlack;
    } else {
        RedBlack * rb = root->root;
        while (1) {
            if (value == rb->value) {
                free (newRedBlack);
                return;
            } else if (value < rb->value) {
                if (rb->left == NULL) {
                    rb->left = newRedBlack;
                    break;
                } else {
                    rb = rb->left;
                }
            } else {
                if (rb->right == NULL) {
                    rb->right = newRedBlack;
                    break;
                } else {
                    rb = rb->right;
                }
            }
        }
        newRedBlack->parent = rb;
    }
    AddCase1(root, newRedBlack);
}

void AddCase1(Root * root, RedBlack * rb) { // Caso raiz
    if (rb->parent == NULL) {
        rb->color = 'b';
    } else {
        AddCase2(root, rb);
    }
}

void AddCase2(Root * root, RedBlack * rb) {
    if (rb->parent->color == 'b') {
        return;
    } else { // Vermelho Vermelho
        AddCase3(root, rb);
    }
}

void AddCase3(Root * root, RedBlack * rb) {
    if(Color(Uncle(rb)) == 'b') {
        AddCase4(root, rb);  // Caso Rotacao
    } else {  // Caso Recolorir
        rb->parent->color = 'b';
        Uncle(rb)->color = 'b';
        GrandParent(rb)->color = 'r';
        AddCase1(root, GrandParent(rb));
    }
}

void AddCase4(Root * root, RedBlack * rb) {
    if (rb == rb->parent->right && rb->parent == GrandParent(rb)->left) { // ED
        RotateLeft(root, rb->parent);
        rb = rb->left;
    } else if (rb == rb->parent->left && rb->parent == GrandParent(rb)->right) {
        RotateRight(root, rb->parent);
        rb = rb->right;
    }
    AddCase5(root, rb);
}

void AddCase5(Root * root, RedBlack * rb) {
    rb->parent->color = 'b';
    GrandParent(rb)->color = 'r';
    if (rb == rb->parent->left && rb->parent == GrandParent(rb)->left) {
        RotateRight(root, GrandParent(rb));
    } else {
        RotateLeft(root, GrandParent(rb));
    }
}

void PrintPreorder(RedBlack * root) {
    if(root != NULL) {
        printf("[%d, %c]", root->value, root->color);
        PrintPreorder(root->left);
        PrintPreorder(root->right);
    }
}

RedBlack * RootNode(Root * root) {
    return root->root;
}

RedBlack * MaxNode(RedBlack * rb) {
    while (rb->right != NULL) {
        rb = rb->right;
    }
    return rb;
}

RedBlack * SearchNode(Root * root, int value) {
    RedBlack * rb = root->root;
    while (rb != NULL) {
        if (value == rb->value) {
            return rb;
        } else if (value < rb->value) {
            rb = rb->left;
        } else {
            rb = rb->right;
        }
    }
    return rb;
}

char Color(RedBlack * rb) {
    if(rb == NULL) {
        return 'b';
    } else {
        return rb->color;
    }
}

void DeleteRedBlack(Root * root, int value) {
    RedBlack * child;
    RedBlack * rb = SearchNode(root, value);
    if (rb == NULL) return;
    if (rb->left != NULL && rb->right != NULL) {
        RedBlack * max = MaxNode(rb->left);
        rb->value = max->value;
        rb = max;
    }
    child = rb->right == NULL ? rb->left  : rb->right;
    if (rb->color == 'b') {
        rb->color = Color(child);
        DeleteCase1(root, rb);
    }
    ReplaceNode(root, rb, child);
    if (rb->parent == NULL && child != NULL)
        child->color = 'b';
    free(rb);
}

void DeleteCase1(Root * root, RedBlack * rb) {
    if (rb->parent == NULL)
        return;
    else
        DeleteCase2(root, rb);
}

void DeleteCase2(Root * root, RedBlack * rb) {
    if (Brother(rb)->color == 'r') {
        rb->parent->color = 'r';
        Brother(rb)->color = 'b';
        if (rb == rb->parent->left) {
            RotateLeft(root, rb->parent);
        } else {
            RotateRight(root, rb->parent);
        }
    }
    DeleteCase3(root, rb);
}

void DeleteCase3(Root * root, RedBlack * rb) {
    if (Color(rb->parent) == 'b' && Color(Brother(rb)) == 'b' && Color(Brother(rb)->left) == 'b' && Color(Brother(rb)->right) == 'b') {
        Brother(rb)->color = 'r';
        DeleteCase1(root, rb->parent);
    } else {
        DeleteCase4(root, rb);
    }
}

void DeleteCase4(Root * root, RedBlack * rb) {
    if (Color(rb->parent) == 'r' && Color(Brother(rb)) == 'b' && Color(Brother(rb)->left) == 'b' && Color(Brother(rb)->right) == 'b') {
        Brother(rb)->color = 'r';
        rb->parent->color = 'b';
    }
    else
        DeleteCase5(root, rb);
}

void DeleteCase5(Root * root, RedBlack * rb) {
    if (rb == rb->parent->left && Color(Brother(rb)) == 'b' && Color(Brother(rb)->left) == 'r' && Color(Brother(rb)->right) == 'b') {
        Brother(rb)->color = 'r';
        Brother(rb)->left->color = 'b';
        RotateRight(root, Brother(rb));
    }
    else if (rb == rb->parent->right && Color(Brother(rb)) == 'b' && Color(Brother(rb)->right) == 'r' && Color(Brother(rb)->left) == 'b') {
        Brother(rb)->color = 'r';
        Brother(rb)->right->color = 'b';
        RotateLeft(root, Brother(rb));
    }
    DeleteCase6(root, rb);
}

void DeleteCase6(Root * root, RedBlack * rb) {
    Brother(rb)->color = Color(rb->parent);
    rb->parent->color = 'b';
    if (rb == rb->parent->left) {
        Brother(rb)->right->color = 'b';
        RotateLeft(root, rb->parent);
    } else {
        Brother(rb)->left->color = 'b';
        RotateRight(root, rb->parent);
    }
}



























