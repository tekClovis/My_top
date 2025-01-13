/*
** EPITECH PROJECT, 2024
** Semester_1
** File description:
** my_top
*/
#include "my.h"
#include "my_top.h"
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <curses.h>
#include <time.h>

static void free_system(system_t *system)
{
    free(system->f_line->hour);
    free(system->f_line->uptime);
    free(system->f_line->load_avg);
    free(system->f_line);
    free(system->tasks);
    free(system->cpu->delta);
    free(system->cpu->t1);
    free(system->cpu->t2);
    free(system->cpu->inf_cpu);
    free(system->cpu);
    free(system->inf_mem);
    free(system->inf_swap);
}

static void free_all_top(top_t *top)
{
    node_t *next = top->list_process->head;
    node_t *current = top->list_process->head;

    free_system(top->system);
    while (current != NULL){
        next = current->next;
        free_list_all(((process_t **)&current->data));
        destroy_nodes(top->list_process, current);
        current = next;
    }
}

void print_all(top_t *top, flag_t *flag)
{
    erase();
    print_firstline(top->system->f_line);
    print_tasks(top->system->tasks);
    print_cpu(top->system->cpu);
    print_mem(top->system->inf_mem);
    print_swap(top->system->inf_swap);
    attron(A_STANDOUT);
    if (stdscr->_cury < LINES - 1)
        printw("\n%7s %-8s %3s %3s %7s %6s %6s %c %5s %5s %8s %s", "PID"
        , "USER", "PR", "NI", "VIRT", "RES", "SHR", 'S', "%CPU", "%MEM",
     
   "TIME+", "COMMAND");
    attroff(A_STANDOUT);
    print_list(top->list_process, flag);
}

static void handle_key_input(top_t *top, flag_t *flag, int total, int ch)
{
    if (ch == KEY_UP && flag->parcours > 0){
        flag->parcours--;
        update(top);
        print_all(top, flag);
        return;
    }
    if (ch == KEY_DOWN && flag->parcours < total - 1){
        flag->parcours++;
        update(top);
        print_all(top, flag);
        return;
    }
}

void while_open(top_t *top, flag_t *flag)
{
    double start = time(NULL);
    double c_time = start;
    int ch = 0;

    update(top);
    print_all(top, flag);
    for (int i = 0; (flag->frame == 0 || i < flag->frame - 1) && ch != 'q';){
        c_time = time(NULL);
        if (difftime(c_time, start) >= flag->delay){
            update(top);
            print_all(top, flag);
            start = c_time;
            i++;
            refresh();
        }
        ch = getch();
        handle_key_input(top, flag, top->system->tasks->total, ch);
    }
}

int main(int ac, char **av)
{
    flag_t *flag = malloc(sizeof(flag_t));
    top_t *top = malloc(sizeof(top_t));

    *flag = (flag_t){NULL, 3.0, 0, 0};
    top = struct_init();
    if ((parsing(ac, av, flag) == 84 && ac > 1) || top == NULL)
        return 84;
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    while_open(top, flag);
    refresh();
    endwin();
    free_all_top(top);
    return 0;
}
