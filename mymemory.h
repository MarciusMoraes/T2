#ifndef MYMEMORY_H
#define MYMEMORY_H

#include <stddef.h>


//data structures
typedef struct allocation {
    void *start;
    size_t size;
    struct allocation *next;
} allocation_t;

typedef struct {
    void *pool; // ponteiro para o bloco de memória real
    size_t total_size;
    allocation_t *head;
} mymemory_t;

mymemory_t* mymemory_init(size_t size){
    mymemory_t *memory=(mymemory_t) malloc(sizeof(mymemory_t));
    if(!memory){
        return NULL;
    } 

    memory->pool=malloc(size);
    if(!memory->pool){
        free(memory);
        return NULL;
    }

    memory->total_size= size;
    memory->head= NULL;
    return memory;
}

//Não esta terminado
void* mymemory_alloc(mymemory_t *memory, size_t size){
    if(!memory || size <= 0) {
        return NULL;
    }

    allocation_t *actual= memory -> head;
    allocation_t *old= NULL;
    
}

void mymemory_free(mymemory_t *memory, void *ptr){

}


void mymemory_display(mymemory_t *memory){
    if(!memory){
        return NULL;
    } 


    allocation_t *actual= memory->head;
    printf("Alocações ativas:\n");
    while(actual){
        printf("Inicio: %p, Tamanho: %zu bytes\n", actual->start, actual->size);
        actual=actual->next;
    }
}

void mymemory_stats(mymemory_t *memory){

}

void mymemory_cleanup(mymemory_t *memory){
    if(!memory) return

    allocation_t *actual= memory->head;
    while(actual){
        allocation_t *temp= actual;
        actual=actual->next;
        free(temp);
    }
    free(memory->pool);
    free(memory);
}

#endif /* MYMEMORY_H */