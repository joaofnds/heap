#include <stdio.h>
#include <stdlib.h>

#include "heap/heap.h"

int main() {

    struct heap * h = heap_create(3);

    heap_insert(h,5);
    heap_insert(h,6);
    heap_insert(h,7);

    printf("Heap size before: %d\n", h->size);
    printf("Heap length before: %d\n", h->length);

    printf("Tentando inserir mais do que a capacidade, resultado: %s\n", ((heap_insert(h, 8) == EXIT_SUCCESS) ? "success" : "failure") );

    printf("Heap size after: %d\n", h->size);
    printf("Heap length after: %d\n", h->length);

    printf("Heap resize back to 3 nodes: %s\n", (( heap_resize(h, 3) == EXIT_SUCCESS ) ? "success" : "failure" ));

    printf("Heap size after: %d\n", h->size);
    printf("Heap length after: %d\n", h->length);

    for (int i = 0; i < h->length; ++i) {
        printf("heap->first(): %d\n", h->heap[i]);
    }

    heap_destroy(h);

    return 0;
}