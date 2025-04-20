/*
 * Copyright (C) 2025 pdnguyen of HCMC University of Technology VNU-HCM
 */

/* Sierra release
 * Source Code License Grant: The authors hereby grant to Licensee
 * personal permission to use and modify the Licensed Source Code
 * for the sole purpose of studying while attending the course CO2018.
 */

#include "common.h"
#include "syscall.h"
#include "stdio.h"
#include "libmem.h"


//Added previously
#include "queue.h"
#include <stdlib.h>
#include <string.h>

int __sys_killall(struct pcb_t *caller, struct sc_regs* regs)
{
    char proc_name[100];
    uint32_t data;

    //hardcode for demo only
    uint32_t memrg = regs->a1;
    
    /* TODO: Get name of the target proc */
    //proc_name = libread..
    int i = 0;
    data = 0;
    while(data != -1){
        libread(caller, memrg, i, &data);
        proc_name[i]= data;
        if(data == -1) proc_name[i]='\0';
        i++;
    }
    printf("The procname retrieved from memregionid %d is \"%s\"\n", memrg, proc_name);

    /* TODO: Traverse proclist to terminate the proc
     *       stcmp to check the process match proc_name
     */
    //caller->running_list
    //caller->mlq_ready_queu
    
    struct pcb_t * proc_del;
    struct queue_t * run_list = caller->running_list;
    struct queue_t * red_que = caller->mlq_ready_queue;

    for(int i = 0; i < run_list->size; i++)
    {
        if(strcmp(run_list->proc[i]->path,proc_name) == 0)
        {
            proc_del = run_list->proc[i];
            for (int j = i; j < run_list-> size - 1; j++)
            {
                run_list->proc[j] = run_list->proc[j + 1];
            }
            run_list->size--;
            i--;
            free(proc_del);
        }
    }
    
    for(int i = 0; i < red_que->size; i++)
    {
        if(strcmp(red_que->proc[i]->path,proc_name) == 0)
        {
            proc_del = red_que->proc[i];
            for (int j = i; j < red_que-> size - 1; j++)
            {
                red_que->proc[j] = red_que->proc[j + 1];
            }
            red_que->size--;
            i--;
            free(proc_del);
        }
    }
    /* TODO Maching and terminating 
     *       all processes with given
     *        name in var proc_name
     */

    return 0; 
}
