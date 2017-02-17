#include "lib/simpletest.h"
#include "heap/heap.h"

#define MAX 128


void test_create(){
	DESCRIBE("CRIA HEAP");
	WHEN("Eu crio uma HEAP");


	IF("Sem parâmetros");
	THEN("Resultado deve ser ponteiro");
	struct heap * p = heap_create(MAX);
	isNotNull(p);

	THEN("Deve ser vazia");
	isEqual(heap_isempty(p),1);

	heap_destroy(p);
}

void test_insert(){
	int i;
	struct heap * p = heap_create(MAX);

	DESCRIBE("INSERE ELEMENTOS");
	WHEN("Eu insiro elementos");
	IF("Insiro um número razoável MAX");
	THEN("Deve inserir todos");
	for(i=1; i<=MAX; i++){
		isEqual(heap_insert(p,i), 1);
	}
	THEN("Deve não estar vazia");
	isEqual(heap_isempty(p),0);

	THEN("Primeiro elemento deve ser 1");
	isEqual(heap_minimum(p),1);

	heap_destroy(p);
}

void test_heapify(){

	int i, val;
	struct heap * p = create(MAX);


	DESCRIBE("HEAPIFY");
	WHEN("Eu insiro elementos e chamo heapify");
	int valores[]={10,9,8,7,6,5,4,3,2,1};

	for(i=1; i<=10; i++){
		heap_insert(p,i);
		heap_heapify(p,heap_parent(i))
	}
	for(i=1 i<=10; i++){
		THEN("Deve ter cabeça igual a i");
		isEqual(heap_minimum_delete(p),i);
	}

	THEN("Deve ser vazia");
	isEqual(heap_isempty(p),1);
	destroy(p);
}




int main () {
	test_create();
	test_insert();
	test_heapify();
}
