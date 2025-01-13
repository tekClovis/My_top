/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** process_init
*/
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include "my.h"
#include "my_top.h"

static void format_time(time_up_t *time)
{
    long int hz = sysconf(_SC_CLK_TCK);
    long int centième = (time->ctime + time->utime);
    int seconds = centième / hz;
    int minutes = seconds / 60;

    centième %= 100;
    seconds %= 60;
    minutes %= 60;
    time->time_u = NULL;
    asprintf(&time->time_u, "%d:%02d.%02ld", minutes, seconds, centième);
}

static void handle_pr(in_stat_t *stat, char *search, char *next)
{
    int rt_check = -100;

    stat->NI = 0;
    if (atoi(search) == rt_check){
        asprintf(&stat->PR, "rt");
        return;
    }
    stat->NI = atoi(next);
    asprintf(&stat->PR, "%d", atoi(search));
}

static void format_virt(char **virt, char *search)
{
    unsigned long kib = (atoi(search) / 1024);
    float gib = (atof(search) / 1024.0 / 1024.0 / 1024.0);

    if (kib > 9999999){
        asprintf(virt, "%.1fg", gib);
        return;
    }
    asprintf(virt, "%lu", kib);
}

static void pars_stat(int i, char *search, in_stat_t *stat, system_t *system)
{
    if (i == 1){
        asprintf(&stat->command, "%s", &search[1]);
        stat->command[my_strlen(stat->command) - 1] = '\0';
    }
    if (i == 2){
        stat->state = search[0];
        parsing_tasks(system->tasks, search[0]);
    }
    if (i == 22)
        format_virt(&stat->VIRT, search);
    if (i == 13)
        stat->time_up.utime = atoi(search);
    if (i == 14){
        stat->time_up.ctime = atoi(search);
        format_time(&stat->time_up);
    }
}

static void free_tmp(char *path, char *file)
{
    if (path != NULL)
        free(path);
    if (file != NULL)
        free(file);
}

void update_in_stat(in_stat_t *stat, system_t *system, char *d_name)
{
    char *path = NULL;
    char *file;
    char *search;
    char *next;

    asprintf(&path, "/proc/%s/stat", d_name);
    file = my_catchar(path);
    if (file == NULL)
        return;
    stat->PID = atoi(d_name);
    next = strtok(file, " ");
    for (int i = 0; next != NULL; i++){
        search = my_strdup(next);
        next = strtok(NULL, " ");
        if (i == 17)
            handle_pr(stat, search, next);
        pars_stat(i, search, stat, system);
    }
    free_tmp(path, file);
}

void pars_mod_cpu(modulo_cpu_t *modulo, char *d_name)
{
    char *path = NULL;
    char *file;
    char *search;

    asprintf(&path, "/proc/%s/stat", d_name);
    file = my_catchar(path);
    if (file == NULL)
        return;
    search = strtok(file, " ");
    for (int i = 0; search != NULL; i++){
        if (i == 13)
            modulo->utime = strtoul(search, NULL, 10);
        if (i == 14)
            modulo->ctime = strtoul(search, NULL, 10);
        if (i == 21)
            modulo->starttime = strtoull(search, NULL, 10);
        search = strtok(NULL, " ");
    }
    free_tmp(path, file);
}

modulo_cpu_t *init_modulo(char *d_name)
{
    modulo_cpu_t *modulo = malloc(sizeof(modulo_cpu_t));
    char *file = my_catchar("/proc/uptime");
    char *search = strtok(file, " ");
    int hz = sysconf(_SC_CLK_TCK);

    if (file == NULL || modulo == NULL)
        return NULL;
    modulo->mod_cpu = 0.0;
    modulo->ctime = 0;
    modulo->utime = 0;
    modulo->starttime = 0;
    pars_mod_cpu(modulo, d_name);
    modulo->mod_cpu = (((modulo->utime + modulo->ctime) / hz) /
        (atof(search) - (modulo->starttime / hz))) * 100.0;
    free(file);
    return modulo;
}

void update_list(list_t *list_process, system_t *system)
{
    DIR *dir;
    struct dirent *ent;
    process_t *process;

    if (opendir("/proc") == NULL)
        return;
    dir = opendir("/proc");
    ent = readdir(dir);
    for (; ent != NULL; ent = readdir(dir)){
        if (my_getnbr(ent->d_name) != 0){
            process = malloc(sizeof(process_t));
            process->in_stat = malloc(sizeof(in_stat_t));
            process->in_stat->PID = 0;
            process->modulo = init_modulo(ent->d_name);
            update_in_stat(process->in_stat, system, ent->d_name);
            push_back(list_process, (process_t *)process);
        }
    }
    closedir(dir);
}
