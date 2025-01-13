/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** tasks
*/
#include "my.h"
#include "my_top.h"
#include <stdlib.h>

tasks_t *init_tasks(void)
{
    tasks_t *tasks = malloc(sizeof(tasks_t));

    tasks->total = 0;
    tasks->running = 0;
    tasks->sleeping = 0;
    tasks->stopped = 0;
    tasks->zombie = 0;
    if (tasks == NULL)
        return NULL;
    return tasks;
}

void reinit_tasks(tasks_t *tasks)
{
    tasks->total = 0;
    tasks->running = 0;
    tasks->sleeping = 0;
    tasks->stopped = 0;
    tasks->zombie = 0;
}

void parsing_tasks(tasks_t *tasks, char c)
{
    tasks->total += 1;
    if (c == 'R')
        tasks->running += 1;
    if (c == 'T')
        tasks->stopped += 1;
    if (c == 'Z')
        tasks->zombie += 1;
    if (c != 'Z' && c != 'R' && c != 'T')
        tasks->sleeping += 1;
}
