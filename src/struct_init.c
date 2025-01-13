/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** struct_init
*/
#include "my_top.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

system_t *init_system(void)
{
    system_t *system = malloc(sizeof(system_t));

    system->f_line = init_f_line();
    system->tasks = init_tasks();
    system->cpu = init_cpu();
    system->inf_mem = init_inf_mem();
    system->inf_swap = init_inf_swap();
    if (system->f_line == NULL || system->tasks == NULL ||
        system->cpu == NULL || system->inf_mem == NULL ||
        system->inf_swap == NULL)
        return NULL;
    return system;
}

top_t *struct_init(void)
{
    top_t *top = malloc(sizeof(top_t));

    if (top == NULL)
        return NULL;
    top->system = init_system();
    if (top->system == NULL)
        return NULL;
    top->list_process = list_create();
    if (top->list_process == NULL)
        return NULL;
    return top;
}
