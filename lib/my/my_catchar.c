/*
** EPITECH PROJECT, 2024
** my_top
** File description:
** my_catchar
*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "my.h"

char *my_catchar(char *file)
{
    int fd = 0;
    char buffer[30000];
    char *str;
    int size = 0;

    fd = open(file, O_RDONLY);
    if (fd == -1) {
        return NULL;
    }
    size = read(fd, buffer, 29999);
    buffer[size] = '\0';
    str = my_strdup(buffer);
    close(fd);
    return str;
}
