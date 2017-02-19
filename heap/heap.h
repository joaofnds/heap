
/** Descritor da heap
  */
struct heap {
    int * heap;
    int size;
    int length;
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

/**
 * Retorna o index de parâmetro val na heap
 *
 * @param h descritor da heap
 * @param val value de pesquisa
 * @return index do valor se OK, 0 se não encontrar, EXIT_FAILURE se erro
 */
int heap_get(struct heap * h, int val);

int heap_get_from(struct heap * h, int index);

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

/**
 * Troca o tamanho do bloco de memória apontado por h->heap
 *
 * @param h descritor de heap
 * @param newSize nova quantidade de nodos da lista
 * @return EXIT_SUCCESS se OK, EXIT_FAILURE se erro;
 */
int heap_resize(struct heap * h, int newSize);

/**
 * Calcula a altura da heap
 *
 * @param h descritor de heap
 * @return altura da heap
 */
int heap_height(struct heap * h);

/**
 * Adiciona um nível ao heap
 *
 * @param h descritor de heap
 * @param amount quantidade de níveis a adicionar
 * @return EXIT_SUCCESS se OK, EXIT_FAILURE se erro;
 */
int heap_add_level(struct heap * h, int amount);

int swap(struct heap * h, int index_one, int index_two);

int heap_child_count(struct heap * h, int index);