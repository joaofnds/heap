#include <stdlib.h>
#include <string.h>
#include <limits.h>
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

int heap_max(struct heap * p) {
    return p->size;
};

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

    if (heap_get(p, val)) return EXIT_FAILURE;

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

int heap_minimum(struct heap *p) {
    if (p == NULL) return EXIT_FAILURE;
    if (p->heap == NULL) return EXIT_FAILURE;

    if (p->length == 0) return 0;

    return (p->heap[0]);
};

int heap_minimum_delete(struct heap * p) {
    return heap_delete(p, p->heap[0]);
};

int heap_delete(struct heap * p, int val) {
    if (p == NULL) return EXIT_FAILURE;
    if (p->heap == NULL) return EXIT_FAILURE;
    if (p->length == 0) return EXIT_FAILURE;

    int delIndex = heap_get(p, val);

    if (delIndex == 0) return EXIT_FAILURE;

    swap(p, delIndex, p->length);

    p->length--;

    return heap_heapify(p, delIndex);
};

int heap_get(struct heap * h, int val) {
    if (h == NULL) return 0;
    if (h->heap == NULL) return 0;
    if (h->length == 0) return 0;

    for (int i = 0; i < h->length; i++) {
        if (h->heap[i] == val) return i+1;
    }

    return 0;
}

int heap_get_from(struct heap * h, int index) {
    if (h == NULL) return 0;
    if (h->heap == NULL) return 0;
    if (h->length == 0) return 0;
    if (index < 1 || index > h->length) return 0;

    return h->heap[index-1];

}

int heap_set_value(struct heap * h, int index, int value) {
    if (h == NULL) return EXIT_FAILURE;
    if (h->heap == NULL) return EXIT_FAILURE;
    if (h->length == 0) return EXIT_FAILURE;
    if (index < 1 || index > h->length) return EXIT_FAILURE;

    if (heap_get(h, value) == EXIT_SUCCESS) return EXIT_FAILURE;

    h->heap[index-1] = value;

    return EXIT_SUCCESS;

}

int heap_heapify(struct heap * p, int i) {
    if (p == NULL) return EXIT_FAILURE;
    if (p->heap == NULL) return EXIT_FAILURE;

    if (p->length == 1) return EXIT_SUCCESS;

    int swapped = 0;

    int selfVal = (heap_get_from(p, i));

    int leftVal = heap_get_from(p, heap_left(p, i));
    leftVal = leftVal ? leftVal : INT_MAX;

    int rightVal = heap_get_from(p, heap_right(p, i));
    rightVal = rightVal ? rightVal : INT_MAX;

    if (leftVal < selfVal) {
        swap(p, i, heap_left(p, i));
        swapped = 1;
    } else if (rightVal < selfVal) {
        swap(p, i, heap_right(p, i));
        swapped = 1;
    }

    if (swapped)
        heap_heapify(p, heap_parent(p, i));

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

int swap(struct heap * h, int index_one, int index_two) {
    if (h == NULL) return EXIT_FAILURE;
    if (h->heap == NULL) return EXIT_FAILURE;
    if (h->length < 2) return EXIT_FAILURE;

    int temp = h->heap[index_one-1];

    h->heap[index_one-1] = h->heap[index_two-1];
    h->heap[index_two-1] = temp;

    return EXIT_SUCCESS;
}
