/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** print_process
*/
#include "my_top.h"
#include "my.h"
#include <curses.h>
#include <stdlib.h>

void free_list_all(process_t **data)
{
    if ((*data)->in_stat->PID == 0)
        return;
    free((*data)->in_stat->time_up.time_u);
    free((*data)->in_stat->PR);
    free((*data)->in_stat->VIRT);
    free((*data)->in_stat->command);
    free((*data)->modulo);
    free((*data)->in_statm->RES);
    free((*data)->in_statm->SHR);
    free((*data)->in_statm);
    free((*data)->in_stat->USER);
    free((*data)->in_stat);
}

void print_process(process_t *data)
{
    if (data->in_stat->PR == 0)
        return;
    printw("\n%7ld", data->in_stat->PID);
    printw(" %-8s", data->in_stat->USER);
    printw(" %3s", data->in_stat->PR);
    printw(" %3d", data->in_stat->NI);
    printw(" %7s", data->in_stat->VIRT);
    printw(" %6s", data->in_statm->RES);
    printw(" %6s", data->in_statm->SHR);
    printw(" %c", data->in_stat->state);
    if (data->modulo != NULL)
        printw(" %5.1f", data->modulo->mod_cpu);
    printw(" %5.1f", data->in_statm->mem);
    printw(" %8s", data->in_stat->time_up.time_u);
    printw(" %s", data->in_stat->command);
}

void print_list(list_t *process, flag_t *flag)
{
    node_t *current = process->head;
    node_t *tmp = NULL;

    for (int i = 0; current != NULL; i++){
        tmp = current->next;
        if (stdscr->_cury < LINES - 1 && i >= flag->parcours &&
            (process_t *)current->data != NULL){
            print_process((process_t *)current->data);
        }
        free_list_all(((process_t **)&current->data));
        destroy_nodes(process, current);
        current = tmp;
    }
}
