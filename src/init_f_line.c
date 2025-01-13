/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** init_f_line
*/
#include "my_top.h"
#include "my.h"
#include <string.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>

static char *hour_init(void)
{
    char *hour_str = NULL;
    char *file = my_catchar("/proc/driver/rtc");
    int hour_hiv = 1;
    int minutes = 0;
    int seconds = 0;

    if (file == NULL)
        return NULL;
    strtok(file, " :");
    hour_hiv += atoi(strtok(NULL, " :\n"));
    minutes = atoi(strtok(NULL, " :\n"));
    seconds = atoi(strtok(NULL, " :\n"));
    if (hour_hiv == 24)
        hour_hiv = 0;
    asprintf(&hour_str, "%02d:%02d:%02d", hour_hiv, minutes, seconds);
    free(file);
    return hour_str;
}

static char *up_time_init(void)
{
    char *up_time_sec_c;
    char *file = my_catchar("/proc/uptime");
    int up_time_sec_i;

    if (file == NULL)
        return NULL;
    up_time_sec_c = strtok(file, " .");
    up_time_sec_i = atoi(up_time_sec_c);
    free(file);
    return format_up_time(up_time_sec_i);
}

static char *load_avg_init(void)
{
    char *load_avg = NULL;
    char *file = my_catchar("/proc/loadavg");
    char *tmp1;
    char *tmp2;
    char *tmp3;

    if (file == NULL)
        return NULL;
    tmp1 = strtok(file, " ");
    tmp2 = strtok(NULL, " ");
    tmp3 = strtok(NULL, " ");
    asprintf(&load_avg, "%s %s %s", tmp1, tmp2, tmp3);
    if (load_avg == NULL)
        return NULL;
    free(file);
    return load_avg;
}

int update_nb_user(void)
{
    int fd = open(_PATH_UTMP, O_RDONLY);
    struct utmp log;
    int nb_user = 0;

    if (fd == -1)
        return 0;
    while (read(fd, &log, sizeof(log)) == sizeof(log))
        if (log.ut_type == USER_PROCESS)
            nb_user++;
    return nb_user;
}

f_line_t *init_f_line(void)
{
    f_line_t *f_line = malloc(sizeof(f_line_t));

    if (f_line == NULL)
        return NULL;
    f_line->hour = hour_init();
    f_line->uptime = up_time_init();
    f_line->nb_user = 0;
    f_line->load_avg = load_avg_init();
    if (f_line->load_avg == NULL)
        return NULL;
    return f_line;
}

void update_f_line(f_line_t **f_line)
{
    free((*f_line)->hour);
    free((*f_line)->uptime);
    free((*f_line)->load_avg);
    (*f_line)->hour = hour_init();
    (*f_line)->uptime = up_time_init();
    (*f_line)->nb_user = update_nb_user();
    (*f_line)->load_avg = load_avg_init();
}
