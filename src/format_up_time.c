/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** format_up_time
*/
#include <stdlib.h>
#include <stdio.h>

static char *with_day(int day, int hour, int minutes)
{
    char *tmp = NULL;

    minutes %= 60;
    hour %= 24;
    if (day > 1 && hour >= 1)
        asprintf(&tmp, "%d days, %2d:%02d,", day, hour, minutes);
    if (day == 1 && hour >= 1)
        asprintf(&tmp, "%d day, %2d:%02d,", day, hour, minutes);
    if (day == 1 && hour < 1)
        asprintf(&tmp, "%d day, %dmin,", day, minutes);
    if (day > 1 && hour < 1)
        asprintf(&tmp, "%d days, %dmin,", day, minutes);
    return tmp;
}

char *format_up_time(int up_time_in_sec)
{
    int minutes = up_time_in_sec / 60;
    int hour = minutes / 60;
    int day = hour / 24;
    char *up_time = NULL;

    if (day >= 1)
        up_time = with_day(day, hour, minutes);
    if (hour < 1)
        asprintf(&up_time, "%dmin,", minutes % 60);
    if (day < 1 && hour >= 1)
        asprintf(&up_time, "%2d:%02d,", hour % 24, minutes % 60);
    return up_time;
}
