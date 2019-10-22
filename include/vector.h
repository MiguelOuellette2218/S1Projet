#include <stdlib.h>

typedef signed long int sl;
typedef unsigned long int ul;

// Tableau dynamique signed long int
typedef struct vector
{
    sl* data;

    ul size;
    ul allocsize;
} vector;

void vector_clean(void* p);
sl vector_reserve(vector* p, ul allocsize);
sl vector_resize(vector* p, ul size);
void vector_init(vector* p);
sl vector_push(vector* p, sl x);