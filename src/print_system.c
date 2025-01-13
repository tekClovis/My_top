/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** print_system
*/
#include "my.h"
#include "my_top.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>

void print_firstline(f_line_t *f_line)
{
    char *to_print = NULL;

    asprintf(&to_print, "top - %s up %s %2d users,  load average: %s\n",
        f_line->hour, f_line->uptime,
        f_line->nb_user, f_line->load_avg);
    if (stdscr->_cury < LINES - 1 && to_print != NULL)
        mvprintw(0, 0, "%s", to_print);
    free(to_print);
}

void print_tasks(tasks_t *tasks)
{
    char *to_print = NULL;

    asprintf(&to_print, "Tasks: %3d total, %3d running, %3d sleeping, "
        "%3d stopped, %3d zombie\n",
        tasks->total, tasks->running,
        tasks->sleeping, tasks->stopped, tasks->zombie);
    if (stdscr->_cury < LINES - 1 && to_print != NULL)
        printw("%s", to_print);
    free(to_print);
}

void print_cpu(m_cpu_t *cpu)
{
    char *to_print = NULL;

    asprintf(&to_print, "%%Cpu(s): %4.1f us, %4.1f sy, %4.1f ni, %4.1f id,"
        " %4.1f wa, %4.1f hi, %4.1f si, %4.1f st\n",
        cpu->inf_cpu->user, cpu->inf_cpu->system, cpu->inf_cpu->nice,
        cpu->inf_cpu->idle, cpu->inf_cpu->iowait, cpu->inf_cpu->irq,
        cpu->inf_cpu->sofirq, cpu->inf_cpu->steal);
    if (stdscr->_cury < LINES - 1 && to_print != NULL)
        printw("%s", to_print);
    free(to_print);
}

void print_mem(inf_mem_t *mem)
{
    char *to_print = NULL;

    asprintf(&to_print, "%ciB Mem : %8.1f total, %8.1f free, %8.1f used,"
        "%8.1f buff/cache\n",
        mem->IB, mem->total, mem->free, mem->used, mem->buffcach);
    if (stdscr->_cury < LINES - 1 && to_print != NULL)
        printw("%s", to_print);
    free(to_print);
}

void print_swap(inf_swap_t *swap)
{
    char *to_print = NULL;

    asprintf(&to_print, "%ciB Swap: %8.1f total, %8.1f free, %8.1f used."
        "%8.1f avail Mem\n",
        swap->IB, swap->total, swap->free, swap->used, swap->available);
    if (stdscr->_cury < LINES - 1 && to_print != NULL)
        printw("%s", to_print);
    free(to_print);
}
