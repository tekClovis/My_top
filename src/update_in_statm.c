/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** update_in_statm
*/
#include "my_top.h"
#include "my.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void get_res(process_t *data)
{
    char *path = NULL;
    char *file = NULL;
    char *search = NULL;
    unsigned long res = 0;

    asprintf(&path, "/proc/%ld/statm", data->in_stat->PID);
    file = my_catchar(path);
    if (file == NULL)
        return;
    strtok(file, " ");
    search = strtok(NULL, " ");
    res = strtoul(search, NULL, 10) * getpagesize() / 1024;
    if (res < 999999)
        asprintf(&data->in_statm->RES, "%lu", res);
    else
        asprintf(&data->in_statm->RES, "%.1fg", (double)res / 1024.0 / 1024.0);
    free(path);
    free(file);
}

static void get_shr(process_t *data)
{
    char *path = NULL;
    char *file = NULL;
    char *search = NULL;
    unsigned long shr = 0;

    asprintf(&path, "/proc/%ld/statm", data->in_stat->PID);
    file = my_catchar(path);
    if (file == NULL)
        return;
    strtok(file, " ");
    strtok(NULL, " ");
    search = strtok(NULL, " ");
    shr = strtoul(search, NULL, 10) * getpagesize() / 1024;
    if (shr < 999999)
        asprintf(&data->in_statm->SHR, "%lu", shr);
    else
        asprintf(&data->in_statm->SHR, "%.1fg", (double)shr / 1024.0 / 1024.0);
    free(path);
    free(file);
}

static void update_mem(in_statm_t *in_statm, unsigned long tot_mem)
{
    if (in_statm->RES == NULL)
        return;
    in_statm->mem = atof(in_statm->RES) / (double)tot_mem * 100.0;
}

in_statm_t *init_stat_m(void)
{
    in_statm_t *in_statm = malloc(sizeof(in_statm_t));

    if (in_statm == NULL)
        return NULL;
    in_statm->RES = NULL;
    in_statm->SHR = NULL;
    return in_statm;
}

void update_in_statm(list_t *process)
{
    node_t *current = process->head;
    char *file = my_catchar("/proc/meminfo");
    unsigned long tot_mem;

    if (file == NULL)
        return;
    strtok(file, " ");
    tot_mem = strtoul(strtok(NULL, " "), NULL, 10);
    while (current != NULL){
        ((process_t *)current->data)->in_statm = init_stat_m();
        if (((process_t *)current->data)->in_statm != NULL){
            get_res(((process_t *)current->data));
            get_shr(((process_t *)current->data));
            update_mem(((process_t *)current->data)->in_statm, tot_mem);
        }
        current = current->next;
    }
    free(file);
}
