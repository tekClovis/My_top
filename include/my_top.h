/*
** EPITECH PROJECT, 2024
** Semester_1
** File description:
** my_top
*/
#include "my.h"

#ifndef INCLUDED_MY_TOP_H
    #define INCLUDED_MY_TOP_H

typedef struct flag_s {
    char *User;
    float delay;
    int frame;
    int parcours;
} flag_t;

typedef struct f_line_s {
    char *hour;
    char *uptime;
    int nb_user;
    char *load_avg;
} f_line_t;

typedef struct tasks_s {
    int total;
    int running;
    int sleeping;
    int stopped;
    int zombie;
} tasks_t;

typedef struct t1_s {
    unsigned long long int user;
    unsigned long long int nice;
    unsigned long long int system;
    unsigned long long int idle;
    unsigned long long int iowait;
    unsigned long long int irq;
    unsigned long long int sofirq;
    unsigned long long int steal;
    unsigned long long int total;
} t1_t;

typedef struct t2_s {
    unsigned long long int user;
    unsigned long long int nice;
    unsigned long long int system;
    unsigned long long int idle;
    unsigned long long int iowait;
    unsigned long long int irq;
    unsigned long long int sofirq;
    unsigned long long int steal;
    unsigned long long int total;
} t2_t;

typedef struct delta_s {
    unsigned long long int user;
    unsigned long long int nice;
    unsigned long long int system;
    unsigned long long int idle;
    unsigned long long int iowait;
    unsigned long long int irq;
    unsigned long long int sofirq;
    unsigned long long int steal;
} delta_t;

typedef struct info_cpu_s {
    double user;
    double system;
    double nice;
    double idle;
    double iowait;
    double irq;
    double sofirq;
    double steal;
} info_cpu_t;

typedef struct m_cpu_s {
    info_cpu_t *inf_cpu;
    t1_t *t1;
    t2_t *t2;
    delta_t *delta;
    unsigned long long total_diff;
} m_cpu_t;

typedef struct inf_mem_s {
    char IB;
    double total;
    double free;
    double used;
    double buffcach;
    double available;
} inf_mem_t;

typedef struct inf_swap_s {
    char IB;
    double total;
    double free;
    double used;
    double available;
} inf_swap_t;

typedef struct system_s {
    f_line_t *f_line;
    tasks_t *tasks;
    m_cpu_t *cpu;
    inf_mem_t *inf_mem;
    inf_swap_t *inf_swap;
} system_t;

typedef struct modulo_cpu_s {
    unsigned long utime;
    unsigned long ctime;
    unsigned long long starttime;
    float mod_cpu;
} modulo_cpu_t;

typedef struct time_up_s {
    unsigned long utime;
    unsigned long ctime;
    char *time_u;
} time_up_t;

typedef struct in_stat_s {
    long int PID;
    char *USER;
    char *PR;
    int NI;
    char *VIRT;
    char state;
    time_up_t time_up;
    char *command;
} in_stat_t;

typedef struct in_statm {
    char *RES;
    char *SHR;
    float mem;
} in_statm_t;

typedef struct process_s {
    modulo_cpu_t *modulo;
    in_stat_t *in_stat;
    in_statm_t *in_statm;
} process_t;

typedef struct top_s {
    system_t *system;
    list_t *list_process;
} top_t;

int parsing(int ac, char **av, flag_t *flag);
f_line_t *init_f_line(void);
top_t *struct_init(void);
char *format_up_time(int up_time_in_sec);
m_cpu_t *init_cpu(void);
tasks_t *init_tasks(void);
inf_mem_t *init_inf_mem(void);
inf_swap_t *init_inf_swap(void);
void parsing_tasks(tasks_t *tasks, char c);
void update_list(list_t *list_process, system_t *system);
void print_firstline(f_line_t *f_line);
void print_tasks(tasks_t *tasks);
void print_cpu(m_cpu_t *cpu);
void print_mem(inf_mem_t *mem);
void print_swap(inf_swap_t *swap);
void cpu_update(m_cpu_t *cpu);
void print_list(list_t *process, flag_t *flag);
void update_f_line(f_line_t **f_line);
void update(top_t *top);
void reinit_tasks(tasks_t *tasks);
void update_inf_mem(inf_mem_t *inf_mem);
void update_in_statm(list_t *process);
void update_inf_swap(inf_swap_t *inf_swap);
void update_user(list_t *process);
void free_list_all(process_t **data);

#endif
