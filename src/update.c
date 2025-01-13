/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** update
*/
#include "my_top.h"

void update(top_t *top)
{
    update_f_line(&top->system->f_line);
    cpu_update(top->system->cpu);
    update_inf_mem(top->system->inf_mem);
    update_inf_swap(top->system->inf_swap);
    reinit_tasks(top->system->tasks);
    update_list(top->list_process, top->system);
    if (top->list_process != NULL){
        update_in_statm(top->list_process);
        update_user(top->list_process);
    }
}
