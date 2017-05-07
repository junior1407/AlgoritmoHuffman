#include "../inc/redblack.h"

struct Redblack {

    int value;
    char color; // r = Red, b = Black
    struct Redblack * father;
    struct Redblack * right;
    struct Redblack * left;
};

struct Root {
    Redblack * root;
};