/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** mem_info
*/
#include "my.h"
#include "my_top.h"
#include <stdlib.h>
#include <string.h>

static void parsing_info_mem(inf_mem_t *inf_mem, char *search, char *prev)
{
    if (strcmp(prev, "MemTotal:") == 0)
        inf_mem->total = (atof(search) * (1000.0 / 1024.0) / 1000.0);
    if (strcmp(prev, "MemFree:") == 0)
        inf_mem->free = (atof(search) * (1000.0 / 1024.0) / 1000.0);
    if (strcmp(prev, "MemAvailable:") == 0)
        inf_mem->available = (atof(search) * (1000.0 / 1024.0) / 1000.0);
}

static void parsing_info_swap(inf_swap_t *inf_swap, char *search, char *prev)
{
    if (strcmp(prev, "SwapTotal:") == 0)
        inf_swap->total = (atof(search) * (1000.0 / 1024.0) / 1000.0);
    if (strcmp(prev, "SwapFree:") == 0)
        inf_swap->free = (atof(search) * (1000.0 / 1024.0) / 1000.0);
    if (strcmp(prev, "MemAvailable:") == 0)
        inf_swap->available = (atof(search) * (1000.0 / 1024.0) / 1000.0);
}

inf_swap_t *init_inf_swap(void)
{
    inf_swap_t *inf_swap = malloc(sizeof(inf_swap_t));
    char *search;
    char *prev;
    char *file = my_catchar("/proc/meminfo");

    if (inf_swap == NULL || file == NULL)
        return NULL;
    search = strtok(file, " \n");
    while (search != NULL){
        prev = my_strdup(search);
        search = strtok(NULL, " \n");
        parsing_info_swap(inf_swap, search, prev);
    }
    inf_swap->IB = 'M';
    inf_swap->used = inf_swap->total - inf_swap->available;
    free(file);
    return inf_swap;
}

inf_mem_t *init_inf_mem(void)
{
    inf_mem_t *inf_mem = malloc(sizeof(inf_mem_t));
    char *search;
    char *prev;
    char *file = my_catchar("/proc/meminfo");

    if (inf_mem == NULL || file == NULL)
        return NULL;
    search = strtok(file, " \n");
    while (search != NULL){
        prev = my_strdup(search);
        search = strtok(NULL, " \n");
        parsing_info_mem(inf_mem, search, prev);
    }
    inf_mem->IB = 'M';
    inf_mem->used = inf_mem->total - inf_mem->free;
    inf_mem->buffcach = 0.0;
    free(file);
    return inf_mem;
}

void update_inf_mem(inf_mem_t *inf_mem)
{
    char *search;
    char *prev;
    char *file = my_catchar("/proc/meminfo");

    if (file == NULL)
        return;
    search = strtok(file, " \n");
    while (search != NULL){
        prev = my_strdup(search);
        search = strtok(NULL, " \n");
        parsing_info_mem(inf_mem, search, prev);
    }
    inf_mem->used = inf_mem->total - inf_mem->available;
    inf_mem->buffcach = 0.0;
    free(file);
}

void update_inf_swap(inf_swap_t *inf_swap)
{
    char *search;
    char *prev;
    char *file = my_catchar("/proc/meminfo");

    if (file == NULL)
        return;
    search = strtok(file, " \n");
    while (search != NULL){
        prev = my_strdup(search);
        search = strtok(NULL, " \n");
        parsing_info_swap(inf_swap, search, prev);
    }
    inf_swap->used = inf_swap->total - inf_swap->free;
    free(file);
}
