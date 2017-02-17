#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "heap.h"

int heap_parent(struct heap * p, int i) {
    if (p == NULL) return 0;
    if (p->heap == NULL) return 0;
    if (i < 1 || i > p->length) return 0;

    return (int) floor(i / 2);
};

int heap_left(struct heap * p, int i) {
    if (p == NULL) return EXIT_FAILURE;
    if (i < 1 || i > p->length) return EXIT_FAILURE;
    if (p->heap == NULL) return EXIT_FAILURE;
    
    int leftChildIndex = i*2;
    return (leftChildIndex <= p->length) ? leftChildIndex : 0;
};

int heap_right(struct heap * p, int i) {
    if (p == NULL) return EXIT_FAILURE;
    if (i < 1 || i > p->length) return EXIT_FAILURE;
    if (p->heap == NULL) return EXIT_FAILURE;

    int rightChildIndex = i*2 + 1;
    return (rightChildIndex <= p->length) ? rightChildIndex : 0;
};

int heap_max(struct heap * p);

struct heap * heap_create(int max) {
    if (max < 1) return NULL;

    struct heap * newHeap = (struct heap*) malloc(sizeof(struct heap));
    if (newHeap == NULL) return NULL;

    newHeap->heap = (int *) calloc((size_t) max, sizeof(int));
    if (newHeap->heap == NULL) return NULL;

    newHeap->size = max;
    newHeap->length = 0;

    return newHeap;
};

int heap_insert(struct heap * p, int val) {
    if (p == NULL) return EXIT_FAILURE;
    if (p->heap == NULL) return EXIT_FAILURE;

    if (p->size == p->length) {
        if (heap_add_level(p, 1) == EXIT_FAILURE)
            return EXIT_FAILURE;
        else
            p->heap[p->length] = val;
    } else {
        p->heap[p->length] = val;
    }

    p->length++;

    heap_heapify(p, heap_parent(p, p->length));

    return EXIT_SUCCESS;
};

int heap_minimum(struct heap *p);

int heap_minimum_delete(struct heap * p);

int heap_delete(struct heap * p, int val);

int heap_heapify(struct heap * p, int i) {
    return EXIT_SUCCESS;
};

int heap_isempty(struct heap *p) {
    return p->length == 0;
};

void heap_destroy(struct heap * p) {
    if (p == NULL) return;
    
    if (p->heap != NULL)
        free(p->heap);
    
    free(p);
};

int heap_resize(struct heap * h, int newSize) {
    if (h == NULL) return EXIT_FAILURE;
    if (newSize < 1 || h->size == newSize) return EXIT_FAILURE;

    h->heap = realloc(h->heap, ( sizeof(int) * newSize ));

    h->size = newSize;
    if (h->length > newSize)
        h->length = newSize;

    return EXIT_SUCCESS;
}

int heap_height(struct heap * h) {
    return (int) ceil(log2(h->length+1));
}

int heap_add_level(struct heap * h, int amount) {
    if (h == NULL) return EXIT_FAILURE;

    int currentAmount = heap_height(h);
    int newSize = (int) pow(2, (currentAmount + amount)) - 1;
    
    return heap_resize(h, newSize);
}
