#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include "heap.h"

int heap_parent(struct heap * p, int i) {
    if (p == NULL) return 0;
    if (p->heap == NULL) return 0;
    if (i <= 1 || i > p->length) return 0;

    return (int) floor(i / 2);
};

int heap_left(struct heap * p, int i) {
    if (p == NULL) return 0;
    if (i < 1 || i > p->length) return 0;
    if (p->heap == NULL) return 0;
    
    int leftChildIndex = i*2;
    return (leftChildIndex <= p->length) ? leftChildIndex : 0;
};

int heap_right(struct heap * p, int i) {
    if (p == NULL) return 0;
    if (i < 1 || i > p->length) return 0;
    if (p->heap == NULL) return 0;

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
    if (p == NULL) return 0;
    if (p->heap == NULL) return 0;

    if (heap_get(p, val)) return 0;

    if (p->size == p->length) // If heap is full
        if (!heap_add_level(p, 1)) // Try add another level
            return 0; // Return if it fails

	p->heap[p->length] = val;

    p->length++;

    heap_heapify(p, p->length);

    return 1;
};

int heap_minimum(struct heap *p) {
    if (p == NULL) return 0;
    if (p->heap == NULL) return 0;

    if (p->length == 0) return 0;

    return (p->heap[0]);
};

int heap_minimum_delete(struct heap * p) {
    return heap_delete(p, p->heap[0]);
};

int heap_delete(struct heap * p, int val) {
    if (p == NULL) return 0;
    if (p->heap == NULL) return 0;
    if (p->length == 0) return 0;

    int index = heap_get(p, val);
    int targetValue = heap_get_from(p, index);

    swap(p, index, p->length);
    p->length--;

    int changed = 1;
    int minChild;
    int lchild;
    int rchild;


    while(changed) {
        changed = 0;
        lchild = heap_left(p, index);
        rchild = heap_right(p, index);

        if (!lchild) // If there's no left child
            if (!rchild) // If there's no childs at all
                break;
            else // Set minChild to right child because it's the only one
                minChild = rchild;
        else if (!rchild) // If there's no right child to left child because it's the only one
            minChild = lchild;
        else // set minChild to the smaller child
            minChild = (heap_get_from(p, lchild) < heap_get_from(p, rchild)) ? lchild : rchild;

        if (heap_get_from(p, minChild) < heap_get_from(p, index)) {
            swap(p, index, minChild);
            index = minChild;
            changed = 1;
        }
    }

    return targetValue;

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
    if (h == NULL) return 0;
    if (h->heap == NULL) return 0;
    if (h->length == 0) return 0;
    if (index < 1 || index > h->length) return 0;

    if (heap_get(h, value) == 1) return 0;

    h->heap[index-1] = value;

    return 1;

}

int heap_heapify(struct heap * p, int i) {
    if (p == NULL) return 0;
    if (p->heap == NULL) return 0;

    if (p->length == 1) return 1;

    int parent = heap_parent(p, i);

    while( (parent > 1) &&
           ( heap_get_from(p, parent) > heap_get_from(p, i) )) {
        swap(p, parent, i);
        i = parent;
        parent = heap_parent(p, parent);
    }

    return 1;
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
    if (h == NULL) return 0;
    if (newSize < 1 || h->size == newSize) return 0;

    h->heap = (int *) realloc(h->heap, ( sizeof(int) * newSize ));

    h->size = newSize;
    if (h->length > newSize)
        h->length = newSize;

    return 1;
}

int heap_height(struct heap * h) {
    return (int) ceil(log2(h->length+1));
}

int heap_add_level(struct heap * h, int amount) {
    if (h == NULL) return 0;

    int currentAmount = heap_height(h);
    int newSize = (int) pow(2, (currentAmount + amount)) - 1;
    
    return heap_resize(h, newSize);
}

int swap(struct heap * h, int index_one, int index_two) {
    if (h == NULL) return 0;
    if (h->heap == NULL) return 0;
    if (h->length < 2) return 0;

    int temp = h->heap[index_one-1];

    h->heap[index_one-1] = h->heap[index_two-1];
    h->heap[index_two-1] = temp;

    return 1;
}

int heap_child_count(struct heap * h, int index) {
    if (h == NULL) return 0;
    if (h->heap == NULL) return 0;
    if (index < 1 || index > h->length) return 0;

    if (h->length == 0) return 0;

    int childs = 0;
    int leftChild = heap_left(h, index);
    int rightChild = heap_right(h, index);

    if (leftChild)
        childs += heap_child_count(h, leftChild);

    if (rightChild)
        childs += heap_child_count(h, rightChild);

    return childs;
}
