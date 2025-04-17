#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t *q)
{
        if (q == NULL)
                return 1;
        return (q->size == 0);
}

void enqueue(struct queue_t *q, struct pcb_t *proc)
{
        /* TODO: put a new process to queue [q] */
        if (q == NULL)
        {
                perror("Queue is NULL !\n");
                exit(1);
        }
        if (q->size == MAX_QUEUE_SIZE)
        {
                perror("Queue is full !\n");
                exit(1);
        }
        q->proc[q->size] = proc;
        q->size++;
}

struct pcb_t *dequeue(struct queue_t *q)
{
        /* TODO: return a pcb whose prioprity is the highest
         * in the queue [q] and remember to remove it from q
         * */
        if (empty(q))
        {
                return NULL; // Queue is empty
        }

        int highest_priority_index = 0;
        for (int i = 1; i < q->size; i++)
        {
                if (q->proc[i]->priority > q->proc[highest_priority_index]->priority)
                {
                        highest_priority_index = i;
                }
        }

        struct pcb_t *highest_priority_proc = q->proc[highest_priority_index];

        // Shift remaining processes to fill the gap
        for (int i = highest_priority_index; i < q->size - 1; i++)
        {
                q->proc[i] = q->proc[i + 1];
        }

        q->size--; // Decrement the size of the queue
        return highest_priority_proc;
}
