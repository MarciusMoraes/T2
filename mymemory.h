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

    void *allocation->start= memory->pool;

    while(actual){
        
        if ((uintptr_t)actual->start - (uintptr_t)allocation_start >= size) { 

            break; 

        } 

        allocation_start = (void*)((uintptr_t)actual->start + actual->size); // Ajusta o próximo início 

        old = actual; 

        actual = actual->next;
    }

    if((uintptr_t)memory->pool + memory->total_size - (uintptr_t)allocation_start < size) { 
        return NULL;
    }

    allocation_t *new_allocation = (allocation_t*) malloc(sizeof(allocation_t)); 

    new_allocation->start = allocation_start; // Define o início da alocação 

    new_allocation->size = size;              // Define o tamanho da alocação 

    new_allocation->next = actual;           // Define o próximo elemento na lista 

 

    if (old) old->next = new_allocation; // Insere após o anterior, se houver 

    else memory->head = new_allocation;            // Caso contrário, é o primeiro da lista 

 

    return allocation_start; // Retorna o ponteiro para o início do bloco alocado 


    
}

void mymemory_free(mymemory_t *memory, void *ptr){
    if(!memory || !ptr){
        return;
    }

    allocation_t *actual= memory->head;
    allocation_t *old= NULL;

    while(actual){
        if (actual->start==ptr){
            if(old){
                old->next= actual->next;
            }
            else{
                memory->head = actual->next;
            }

            free(actual);

            return;
        }

        old=actual;

        actual=actual->next;
    }
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
    if(!memory){
        return;
    }

    size_t total_allocated=0;
    largest_free_block=0;
    int allocation_count=0;
    allocation_t *actual=memory->head;
    void *last=memory->pool;

    while(actual){
        total_allocated= total_allocated + actual->size;

        allocation_count++;

        size_t free_space = (uintptr_t)actual->start - (uintptr_t)last_end;

        if (free_space > largest_free_block){
            largest_free_block = free_space; // Atualiza o maior bloco livre 
        }

        last_end = (void*)((uintptr_t)actual->start + actual->size); // Define o fim do bloco atual 

        actual = actual->next;
    }
    size_t final_free_space = (uintptr_t)memory->pool + memory->total_size - (uintptr_t)last_end; 

    if (final_free_space > largest_free_block) {
        largest_free_block = final_free_space; 
    }

    printf("Total de alocações: %d\n", allocation_count); 

    printf("Memória total alocada: %zu bytes\n", total_allocated); 

    printf("Maior bloco contíguo de memória livre: %zu bytes\n", largest_free_block); 

}

void mymemory_cleanup(mymemory_t *memory){
    if(!memory) {
        return
    }
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