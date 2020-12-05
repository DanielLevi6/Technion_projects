#include "priority_queue.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define SIZE_ERROR -1

typedef struct node {
    PQElement element;
    PQElementPriority priority;
    struct node* next;
} *Node;

struct PriorityQueue_t {
    Node list;     //linked list
    int iterator;

    CopyPQElement copy_element;
    FreePQElement free_element;
    EqualPQElements equal_elements;
    CopyPQElementPriority copy_priority;
    FreePQElementPriority free_priority;
    ComparePQElementPriorities compare_priorities;
};

PriorityQueue pqCreate(CopyPQElement copy_element,
                       FreePQElement free_element,
                       EqualPQElements equal_elements,
                       CopyPQElementPriority copy_priority,
                       FreePQElementPriority free_priority,
                       ComparePQElementPriorities compare_priorities) 
{
    assert(!copy_element || !free_element || !equal_elements || !copy_priority || !free_priority || !compare_priorities);

    PriorityQueue queue = malloc(sizeof(*queue));
    if (queue == NULL) {
        return NULL;
    }

    queue->list = malloc(sizeof(Node));
    if (queue->list == NULL) {
        pqDestroy(queue);
        return NULL;
    }
    
    queue->list->next = NULL;
    queue->iterator = 0;

    queue->copy_element = copy_element;
    queue->free_element = free_element;
    queue->equal_elements = equal_elements;
    queue->copy_priority = copy_priority;
    queue->free_priority = free_priority;
    queue->compare_priorities = compare_priorities;

    return queue;
}

void pqDestroy(PriorityQueue queue) {
    if (queue == NULL) {
        return;
    }
    while (queue->list) {
        queue->free_element(queue->list->element);
        queue->free_priority(queue->list->priority);
        Node toDelete = queue->list;
        queue->list = queue->list->next;
        free(toDelete);
    }
    free(queue);
}

PriorityQueue pqCopy(PriorityQueue queue) {
    if (queue == NULL) {
        return NULL;
    }
    PriorityQueue newQueue = pqCreate(queue->copy_element, queue->free_element,
     queue->equal_elements, queue->copy_priority, queue->free_priority, queue->compare_priorities);

    if (newQueue == NULL) {
        return NULL;
    }

    if (addAll(newQueue, queue) != PQ_SUCCESS) {
        pqDestroy(newQueue);
        return NULL;
    }
    newQueue->iterator = queue->iterator;
    return newQueue;
}

/*static area*/
static PriorityQueueResult addAll(PriorityQueue newQueue, PriorityQueue queue) {
    assert(queue == NULL || newQueue == NULL);
    while (queue->list) {
        newQueue->list->element = newQueue->copy_element(queue->list->element);
        newQueue->list->priority = newQueue->copy_priority(queue->list->priority);

        queue->list = queue->list->next;
        if (queue->list == NULL) {
            break;
        }

        newQueue->list->next = malloc(sizeof(Node));
        if (newQueue->list->next == NULL) {
            pqDestroy(newQueue);
            return PQ_OUT_OF_MEMORY;
        }

        newQueue->list = newQueue->list->next;
    }
    return PQ_SUCCESS;
}
/**/

int pqGetSize(PriorityQueue queue) {
    int size = 0;
    if (queue == NULL) {
        return SIZE_ERROR;
    }
    while (queue->list) {
        size += size + 1;
        queue->list = queue->list->next;
    }
    return size;
}