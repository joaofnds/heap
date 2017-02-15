
/** Descritor da heap
  */
struct heap {
    struct heap * left;
    struct heap * right;
    int value;
};

/** Retorna a posição do pai
 * @param p ponteiro para descritor de heap
 * @param i índice do nodo 
 * @return índice do pai ou 0 se erro
 */
int heap_parent(struct heap * p, int i);

/** Retorna a posição do filho à esquerda
 * @param p ponteiro para descritor de heap
 * @param i índice do nodo 
 * @return índice do filho ou 0 se maior que máximo
 */
int heap_left(struct heap * p, int i);

/** Retorna a posição do filho à direita
 * @param p ponteiro para descritor de heap
 * @param i índice do nodo 
 * @return índice do filho ou 0 se maior que máximo
 */
int heap_right(struct heap * p, int i);

/** Retorna o máximo de elementos que a heap comporta
 * @param p ponteiro para descritor de heap
 * @return índice do filho ou 0 se maior que máximo
 */
int heap_max(struct heap * p);
/** Cria uma heap
 * @param max número máximo de elementos
 * @return  um descritor ou NULL
 */
struct heap * heap_create(int max);

/* Insere um elemento no fim da heap
 * @param p descritor de heap
 * @param val elemento a ser inserido
 * @return 1 se OK, 0 se erro
 */
int heap_insert(struct heap * p, int val);

/* Retorna o mínimo de um heap
 * @param p descritor de heap
 * @return valor mínimo, ou zero se heap vazio
 */
int heap_minimum(struct heap *p);

/* Retorna e remove o primeiro elemento  da heap
 * @param p descritor da heap
 * @return o elemento ou 0
 */
int heap_minimum_delete(struct heap * p);

/* Remove um elemento da heap
 * @param p descritor da heap
 * @param val o valor do elemento a ser removido
 * @return 1 se OK ou 0 se erro
 */
int heap_delete(struct heap * p, int val);

/* Corrige uma subárvore
 * @param p descritor da heap
 * @param i a posição da árvore
 * @return 1 se OK ou 0 se erro
 */
int heap_heapify(struct heap * p, int i);

/* Retorna se a heap está vazia ou não
 * @param p descritor de heap
 * @return 1 se vazia, 0 se não
 */
 int heap_isempty(struct heap *p);

/** Desaloca toda a heap
  * @param p descritor da heap
  */
void heap_destroy(struct heap * p);
