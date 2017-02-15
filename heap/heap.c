#include "heap.h"

int heap_parent(struct heap * p, int i);

int heap_left(struct heap * p, int i);

int heap_right(struct heap * p, int i);

int heap_max(struct heap * p);

struct heap * heap_create(int max);

int heap_insert(struct heap * p, int val);

int heap_minimum(struct heap *p);

int heap_minimum_delete(struct heap * p);

int heap_delete(struct heap * p, int val);

int heap_heapify(struct heap * p, int i);

int heap_isempty(struct heap *p);

void heap_destroy(struct heap * p);