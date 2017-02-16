#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "heap.h"

int heap_parent(struct heap * p, int i) {
    if (p == NULL) return 0;
    if (p->heap == NULL) return 0;
    if (i < 1 || i > p->length) return 0;

    return floor(i/2);
};

int heap_left(struct heap * p, int i) {
    if (p == NULL) return EXIT_FAILURE;
    if (i < 1 || i > p->length) return EXIT_FAILURE;
    if (p->heap == NULL) return EXIT_FAILURE;
    
    int leftChildIndex = i*2;
    return (leftChildIndex < p->length) ? leftChildIndex : 0;
};

int heap_right(struct heap * p, int i) {
    if (p == NULL) return EXIT_FAILURE;
    if (i < 1 || i > p->length) return EXIT_FAILURE;
    if (p->heap == NULL) return EXIT_FAILURE;

    int rightChildIndex = i*2 + 1;
    return (rightChildIndex < p->length) ? rightChildIndex : 0;
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

    int insertIndex = p->length + 1;

    if (p->size == p->length) {
        if (heap_add_level(p, 1) == EXIT_FAILURE)
            return EXIT_FAILURE;
        else
            p->heap[insertIndex] = val;
    } else {
        p->heap[insertIndex] = val;
    }

    p->length++;

    heap_heapify(p, heap_parent(p->length));

    return EXIT_SUCCESS;
};

int heap_minimum(struct heap *p);

int heap_minimum_delete(struct heap * p);

int heap_delete(struct heap * p, int val);

int heap_heapify(struct heap * p, int i);

int heap_isempty(struct heap *p) {
    return (heap_left(p) == EXIT_FAILURE) && (heap_right(p) == EXIT_FAILURE);
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

    int * newHeap = (int *) calloc((size_t) newSize, sizeof(int));
    if (newHeap == NULL) return EXIT_FAILURE;

    if (h->heap == NULL) {
        h->heap = newHeap;
        h->length = 0;
        h->size = newSize;
        return EXIT_SUCCESS;
    }

    int i;
    for (i = 0; i < h->length && i < newSize; i++) {
        newHeap[i] = h->heap[i];
    }

    free(h->heap);

    h->heap = newHeap;
    h->size = newSize;
    h->length = i;

    return EXIT_SUCCESS;
}

int heap_height(struct heap * h) {
    return ceil(log2(h->length+1));
}

int heap_add_level(struct heap * h, int amount) {
    if (h == NULL) return EXIT_FAILURE;

    int currentAmount = heap_height(h);
    int newSize = pow((currentAmount + amount), 2);

    heap_resize(h, newSize);
    
    return (h == NULL) ? EXIT_FAILURE : EXIT_SUCCESS;
}
